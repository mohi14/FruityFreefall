#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "utils/config.h"

class GameManager
{
private:
    // Variables
    sf::RenderWindow *window;

    // Initializations
    void initWindow();

public:
    GameManager();
    virtual ~GameManager();

    // Functions
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};