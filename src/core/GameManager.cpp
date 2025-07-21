#include "GameManager.h"
#include "utils/config.h"

// static functions

// Initializer functions
void GameManager::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Fruity Freefall");
}

// Constructors/Destructors
GameManager::GameManager()
{
    this->initWindow();
}
GameManager::~GameManager()
{
    delete this->window;
}

// Functions
void GameManager::updateSFMLEvents()
{
    
    while (const std::optional event = this->window->pollEvent())
    {
        if(event->is<sf::Event::Closed>()){
            this->window->close();
        }
    }

}
void GameManager::update()
{
    this->updateSFMLEvents();
}
void GameManager::render()
{
    this->window->clear();

    //Render items

    this->window->display();
}
void GameManager::run(){
while (this->window->isOpen())
{
    this->update();
    this->render();
}

}