#include "State.h"

State::State(sf::RenderWindow* window){
this->window = window;
}
State::~State(){

}

//Functions
void State::checkForQuit(){
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
    this->quit = true;
}
}
const bool & State::getQuit() const {
return this->quit;
}

