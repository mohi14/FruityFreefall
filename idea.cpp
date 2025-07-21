#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream> // For std::ostringstream

// --- Game Configuration ---
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 300.0f; // Pixels per second
const float FALLING_OBJECT_INITIAL_SPEED = 150.0f; // Pixels per second
const float FALLING_OBJECT_MAX_SPEED = 600.0f;
const float DIFFICULTY_INCREASE_RATE = 0.05f; // How much speed increases per second
const int FRUIT_POINTS = 10;
const int BOMB_PENALTY_POINTS = -5;
const int BOMB_PENALTY_TIME = -3; // Seconds
const int GAME_DURATION_SECONDS = 60;
const int OBJECT_POOL_SIZE = 20; // Max number of fruits/bombs active at once
const float SPAWN_INTERVAL = 1.0f; // Initial interval between spawns in seconds
const float MIN_SPAWN_INTERVAL = 0.2f; // Minimum spawn interval
const float SPAWN_INTERVAL_DECREASE_RATE = 0.02f; // How much spawn interval decreases per second

// --- Game States ---
enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

// --- Forward Declarations ---
class FallingObject; // Declare FallingObject before ObjectPool to avoid circular dependency

// --- Object Pooling for Falling Objects ---
class ObjectPool {
public:
    std::vector<std::unique_ptr<FallingObject>> pool; // Use unique_ptr for automatic memory management
    std::vector<FallingObject*> activeObjects;

    ObjectPool(int size); // Constructor to initialize the pool

    FallingObject* getObject(bool isBomb); // Get an object from the pool (true for bomb, false for fruit)
    void returnObject(FallingObject* obj); // Return an object to the pool
};

// --- Base Class for Falling Objects (Fruit and Bomb) ---
class FallingObject {
public:
    sf::RectangleShape shape;
    bool isActive;
    float speed;
    bool isBomb; // True if bomb, false if fruit

    FallingObject(float radius, bool bomb = false) : isActive(false), speed(0.0f), isBomb(bomb) {
        // Set up shape properties (placeholder visuals)
        shape.setSize(sf::Vector2f(40, 40)); // Default size
        shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2); // Center origin
        if (isBomb) {
            shape.setFillColor(sf::Color::Red); // Bomb color
        } else {
            shape.setFillColor(sf::Color::Green); // Fruit color
        }
    }

    // Update position
    void update(float deltaTime) {
        if (isActive) {
            shape.move(0, speed * deltaTime);
        }
    }

    // Reset object for reuse
    void reset(sf::Vector2f position, float newSpeed, bool bomb) {
        shape.setPosition(position);
        speed = newSpeed;
        isActive = true;
        isBomb = bomb;
        if (isBomb) {
            shape.setFillColor(sf::Color::Red); // Bomb color
        } else {
            shape.setFillColor(sf::Color::Green); // Fruit color
        }
    }

    // Draw the object
    void draw(sf::RenderWindow& window) {
        if (isActive) {
            window.draw(shape);
        }
    }
};

// --- ObjectPool Implementation ---
ObjectPool::ObjectPool(int size) {
    pool.reserve(size);
    for (int i = 0; i < size; ++i) {
        // Create a mix of fruits and bombs initially, but `getObject` will determine type on activation
        pool.push_back(std::make_unique<FallingObject>(20.0f, i % 3 == 0)); // Approx 1/3 bombs initially
    }
}

FallingObject* ObjectPool::getObject(bool isBomb) {
    for (auto& obj_ptr : pool) {
        if (!obj_ptr->isActive) {
            obj_ptr->isBomb = isBomb; // Set the type explicitly when getting
            obj_ptr->isActive = true;
            activeObjects.push_back(obj_ptr.get()); // Add to active list
            return obj_ptr.get();
        }
    }
    // If no inactive object found, potentially expand pool or return nullptr
    // For this game, we'll assume pool size is sufficient or objects will be returned quickly
    std::cerr << "Warning: Object pool exhausted!" << std::endl;
    return nullptr;
}

void ObjectPool::returnObject(FallingObject* obj) {
    if (obj) {
        obj->isActive = false;
        // Remove from activeObjects list
        activeObjects.erase(std::remove(activeObjects.begin(), activeObjects.end(), obj), activeObjects.end());
    }
}

// --- Player Class ---
class Player {
public:
    sf::RectangleShape sprite;
    float speed;

    Player() : speed(PLAYER_SPEED) {
        sprite.setSize(sf::Vector2f(100, 20)); // Basket size
        sprite.setFillColor(sf::Color::Blue); // Basket color
        sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2); // Center origin
        sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50); // Initial position
        // TODO: Load player texture here instead of rectangle
        // if (!texture.loadFromFile("assets/player_basket.png")) { /* Error handling */ }
        // sprite.setTexture(&texture);
    }

    void update(float deltaTime) {
        // Keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite.move(-speed * deltaTime, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(speed * deltaTime, 0);
        }

        // Mouse input (optional, uncomment to enable)
        /*
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Pass window reference
        sprite.setPosition(static_cast<float>(mousePos.x), sprite.getPosition().y);
        */

        // Keep player within bounds
        if (sprite.getPosition().x - sprite.getSize().x / 2 < 0) {
            sprite.setPosition(sprite.getSize().x / 2, sprite.getPosition().y);
        }
        if (sprite.getPosition().x + sprite.getSize().x / 2 > WINDOW_WIDTH) {
            sprite.setPosition(WINDOW_WIDTH - sprite.getSize().x / 2, sprite.getPosition().y);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

// --- Game Manager Class ---
class GameManager {
public:
    sf::RenderWindow window;
    GameState currentState;

    Player player;
    ObjectPool objectPool;
    std::vector<FallingObject*> activeFallingObjects; // Pointers to active objects from the pool

    sf::Font font;
    sf::Text scoreText;
    sf::Text timerText;
    sf::Text messageText; // For menu and game over messages

    int score;
    float gameTimeRemaining;
    float totalGameTimeElapsed; // To track difficulty progression
    float timeSinceLastSpawn;
    float currentSpawnInterval;
    float currentFallingSpeed;

    std::mt19937 randomEngine; // Mersenne Twister engine
    std::uniform_real_distribution<float> spawnXDistribution;
    std::uniform_int_distribution<int> objectTypeDistribution; // 0-99 for 70/30 split

    // Audio
    sf::Music backgroundMusic;
    sf::SoundBuffer fruitCollectBuffer;
    sf::Sound fruitCollectSound;
    sf::SoundBuffer bombExplosionBuffer;
    sf::Sound bombExplosionSound;
    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverSound;

    GameManager() :
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Magical Fruit Tree Defender"),
        currentState(MENU),
        objectPool(OBJECT_POOL_SIZE),
        score(0),
        gameTimeRemaining(GAME_DURATION_SECONDS),
        totalGameTimeElapsed(0.0f),
        timeSinceLastSpawn(0.0f),
        currentSpawnInterval(SPAWN_INTERVAL),
        currentFallingSpeed(FALLING_OBJECT_INITIAL_SPEED),
        randomEngine(std::chrono::high_resolution_clock::now().time_since_epoch().count()), // Seed random engine
        spawnXDistribution(50.0f, WINDOW_WIDTH - 50.0f), // X position for spawning
        objectTypeDistribution(0, 99) // 0-69 for fruit (70%), 70-99 for bomb (30%)
    {
        window.setFramerateLimit(60);

        // Load font
        if (!font.loadFromFile("assets/arial.ttf")) { // You might need to provide a path to a .ttf file
            std::cerr << "Error loading font! Make sure 'arial.ttf' is in 'assets/' folder." << std::endl;
            // Fallback to default font or handle error
        }

        // Setup UI texts
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);

        timerText.setFont(font);
        timerText.setCharacterSize(24);
        timerText.setFillColor(sf::Color::White);
        timerText.setPosition(WINDOW_WIDTH - timerText.getGlobalBounds().width - 100, 10); // Adjust position

        messageText.setFont(font);
        messageText.setCharacterSize(48);
        messageText.setFillColor(sf::Color::Yellow);
        messageText.setOrigin(messageText.getLocalBounds().width / 2, messageText.getLocalBounds().height / 2);
        messageText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        // Load Audio
        // TODO: Replace with your actual audio files
        if (!backgroundMusic.openFromFile("assets/background_music.ogg")) {
            std::cerr << "Error loading background music!" << std::endl;
        }
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50); // 50% volume

        if (!fruitCollectBuffer.loadFromFile("assets/collect.wav")) {
            std::cerr << "Error loading fruit collect sound!" << std::endl;
        }
        fruitCollectSound.setBuffer(fruitCollectBuffer);

        if (!bombExplosionBuffer.loadFromFile("assets/explosion.wav")) {
            std::cerr << "Error loading bomb explosion sound!" << std::endl;
        }
        bombExplosionSound.setBuffer(bombExplosionBuffer);

        if (!gameOverBuffer.loadFromFile("assets/game_over.wav")) {
            std::cerr << "Error loading game over sound!" << std::endl;
        }
        gameOverSound.setBuffer(gameOverBuffer);
    }

    void run() {
        sf::Clock clock;
        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            handleEvents();
            update(deltaTime);
            render();
        }
    }

private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (currentState == MENU && event.key.code == sf::Keyboard::Enter) {
                    startGame();
                } else if (currentState == GAME_OVER && event.key.code == sf::Keyboard::Enter) {
                    resetGame();
                    startGame();
                }
            }
        }
    }

    void update(float deltaTime) {
        switch (currentState) {
            case MENU:
                messageText.setString("Magical Fruit Tree Defender\n\nPress Enter to Start");
                messageText.setOrigin(messageText.getLocalBounds().width / 2, messageText.getLocalBounds().height / 2); // Recenter
                break;
            case PLAYING:
                updatePlayingState(deltaTime);
                break;
            case GAME_OVER:
                messageText.setString("Game Over!\nFinal Score: " + std::to_string(score) + "\n\nPress Enter to Restart");
                messageText.setOrigin(messageText.getLocalBounds().width / 2, messageText.getLocalBounds().height / 2); // Recenter
                break;
        }
    }

    void updatePlayingState(float deltaTime) {
        player.update(deltaTime);

        // Update total game time elapsed for difficulty
        totalGameTimeElapsed += deltaTime;

        // Increase falling speed and decrease spawn interval over time
        currentFallingSpeed = std::min(FALLING_OBJECT_INITIAL_SPEED + (totalGameTimeElapsed * DIFFICULTY_INCREASE_RATE * 10), FALLING_OBJECT_MAX_SPEED);
        currentSpawnInterval = std::max(MIN_SPAWN_INTERVAL, SPAWN_INTERVAL - (totalGameTimeElapsed * SPAWN_INTERVAL_DECREASE_RATE));

        // Spawn new objects
        timeSinceLastSpawn += deltaTime;
        if (timeSinceLastSpawn >= currentSpawnInterval) {
            spawnObject();
            timeSinceLastSpawn = 0.0f;
        }

        // Update and check falling objects
        for (auto it = activeFallingObjects.begin(); it != activeFallingObjects.end(); ) {
            FallingObject* obj = *it;
            obj->update(deltaTime);

            // Collision detection
            if (player.sprite.getGlobalBounds().intersects(obj->shape.getGlobalBounds())) {
                if (obj->isBomb) {
                    score += BOMB_PENALTY_POINTS;
                    gameTimeRemaining += BOMB_PENALTY_TIME;
                    bombExplosionSound.play();
                } else {
                    score += FRUIT_POINTS;
                    fruitCollectSound.play();
                }
                objectPool.returnObject(obj); // Return to pool
                it = activeFallingObjects.erase(it); // Remove from active list
            }
            // Object went off screen
            else if (obj->shape.getPosition().y - obj->shape.getSize().y / 2 > WINDOW_HEIGHT) {
                objectPool.returnObject(obj); // Return to pool
                it = activeFallingObjects.erase(it); // Remove from active list
            } else {
                ++it;
            }
        }

        // Update game timer
        gameTimeRemaining -= deltaTime;
        if (gameTimeRemaining <= 0 || score < 0) { // Game over condition
            gameTimeRemaining = 0; // Cap at 0
            currentState = GAME_OVER;
            backgroundMusic.stop();
            gameOverSound.play();
        }

        // Update UI texts
        scoreText.setString("Score: " + std::to_string(score));
        std::ostringstream timerStream;
        timerStream.precision(0); // No decimal places
        timerStream << std::fixed << "Time: " << gameTimeRemaining;
        timerText.setString(timerStream.str());
    }

    void render() {
        window.clear(sf::Color(100, 149, 237)); // Sky blue background
        // TODO: Draw magical tree/night sky background sprite here
        // sf::Sprite backgroundSprite;
        // backgroundSprite.setTexture(backgroundTexture);
        // window.draw(backgroundSprite);

        if (currentState == MENU || currentState == GAME_OVER) {
            window.draw(messageText);
        } else if (currentState == PLAYING) {
            player.draw(window);
            for (FallingObject* obj : activeFallingObjects) {
                obj->draw(window);
            }
            window.draw(scoreText);
            window.draw(timerText);
        }
        window.display();
    }

    void spawnObject() {
        bool isBomb = (objectTypeDistribution(randomEngine) < 30); // 30% chance for bomb
        FallingObject* newObj = objectPool.getObject(isBomb);
        if (newObj) {
            float spawnX = spawnXDistribution(randomEngine);
            newObj->reset(sf::Vector2f(spawnX, -50.0f), currentFallingSpeed, isBomb); // Spawn above screen
            activeFallingObjects.push_back(newObj);
        }
    }

    void startGame() {
        currentState = PLAYING;
        backgroundMusic.play();
        resetGame(); // Ensure game state is clean on start
    }

    void resetGame() {
        score = 0;
        gameTimeRemaining = GAME_DURATION_SECONDS;
        totalGameTimeElapsed = 0.0f;
        timeSinceLastSpawn = 0.0f;
        currentSpawnInterval = SPAWN_INTERVAL;
        currentFallingSpeed = FALLING_OBJECT_INITIAL_SPEED;

        // Return all active objects to the pool
        for (FallingObject* obj : activeFallingObjects) {
            objectPool.returnObject(obj);
        }
        activeFallingObjects.clear(); // Clear the active list
        player.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50); // Reset player position
    }
};

// --- Main Function ---
int main() {
    GameManager game;
    game.run();
    return 0;
}
