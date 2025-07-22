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

class State
{
private:
    // variables
    sf::RenderWindow *window;
    std::vector<sf::Texture> textures;

public:
    State(sf::RenderWindow *window);
    virtual ~State();

    // Fuctions
    virtual void endState() = 0;

    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *targer = nullptr) = 0;
};
