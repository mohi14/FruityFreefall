#include "GameManager.h"
#include "utils/config.h"

// static functions

// Initializer functions
void GameManager::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Fruity Freefall", sf::Style::Titlebar | sf::Style::Close);
}
void GameManager::initStates()
{
    this->states.push(new GameState(this->window));
}

// Constructors/Destructors
GameManager::GameManager()
{
    this->initWindow();
    this->initStates();
}
GameManager::~GameManager()
{
    delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

// Functions
void GameManager::updateSFMLEvents()
{

    while (const std::optional event = this->window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            this->window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            std::cout << "left key pressed\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            std::cout << "Right key pressed\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            std::cout << "Right key pressed\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            std::cout << "Right key pressed\n";
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            std::cout << "Mouse left button pressed\n";
        }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        // {
        //     this->window->close();
        // }
    }
}

void GameManager::endApplication(){
    std::cout<< "Ending application.."<< "\n";
}

void GameManager::updateDt()
{
    /*Updates the dt variable with the time it takes to update and render one frame. */
    this->dt = this->dtClock.restart().asSeconds();
}
void GameManager::update()
{
    this->updateSFMLEvents();
    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
         if (this->states.top()->getQuit())
    {
        this->states.top()->endState();
        delete this->states.top();
        this->states.pop();
    }
    }
    //Application end
    else{
        this->endApplication();
        this->window->close();
    }
   
}
void GameManager::render()
{
    this->window->clear();

    // Render items
    if (!this->states.empty())
    {
        this->states.top()->render();
    }
    this->window->display();
}
void GameManager::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
