#pragma once
#include "header.h"
#include <SFML/Graphics.hpp>
#include "DText.h"
//klasa odpowiedzialna za faze 3 gry, czyli jej zakonczenie
class GameOver
{
private:
    bool canRestart;
    DText dtext;
    int helperTime;
    sf::Clock clock;
    bool blink;
    
public:
    GameOver();
    void keyPressed(sf::Keyboard::Key k);
    void load();
    void display(sf::RenderTarget& target, int score);
};

