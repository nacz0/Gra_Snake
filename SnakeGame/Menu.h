#pragma once
#include "header.h"
#include <SFML/Graphics.hpp>
#include "DText.h"
#include <iostream>

//klasa odpowiedzialna za faze 0, menu
class Menu
{
private:
    DText dtext;
    sf::Clock clock;
    bool blink;
    std::string  difficulties[3] = { "Easy","Normal","Hard" };
    std::string  mapSizes[3] = { "Small","Medium","Big" };
    std::string  modes[2] = { "Normal","Checkered" };
    std::string colors[2] = { "Orange", "Violet" };
    
    int state; //(0 diff, 1 map size, 2 mode, color)
    gameOptions gameOpts;
    
public:
    Menu();
    void load();
    void keyPressed(sf::Keyboard::Key k);
    void display(sf::RenderTarget& target);
    gameOptions getGameOptions();
};

