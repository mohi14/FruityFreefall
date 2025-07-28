#include "GameState.h"


GameState::GameState(sf::RenderWindow* window):State(window)
{
}

GameState::~GameState()
{
}

//Functions
void GameState::update(const float& dt){
    this->updateKeybinds(dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        std::cout<<"A"<<"\n";
    }
}
void GameState::render(sf::RenderTarget* targer){

}
void GameState::updateKeybinds(const float &dt){
this->checkForQuit();
}
void GameState::endState(){
std::cout << "Ending gamestate"<< "\n";
}
