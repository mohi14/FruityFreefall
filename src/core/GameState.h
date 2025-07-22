#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <stack>
#include <map>

#include "State.h"

class GameState : public State
{
private:
public:
    GameState(sf::RenderWindow *window);
    virtual ~GameState();

    // Functions
    void endState();
    void update(const float &dt);
    void render(sf::RenderTarget *targer = nullptr);
};
