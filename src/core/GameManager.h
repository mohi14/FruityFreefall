#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "utils/config.h"
#include "GameState.h"

class GameManager
{
private:
    // Variables
    sf::RenderWindow *window;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    // Initializations
    void initWindow();
    void initStates();

public:
    GameManager();
    virtual ~GameManager();

    // Functions
    void updateDt();
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};