#pragma once
#include <vector>
#include "DText.h"
#include "header.h"
#include "SnakeDrawing.h"
#include <random>
#include <iostream>

struct Reward {
    int x;
    int y;
};

//klasa odpowiedzialna za faze 1 rozgrywki, czyli sama gre, kiedy kontrolujemy weza 
class SnakeEntity
{
private:
    bool move;
    int toGet;
    bool blink = false;
    sf::Clock clock;
    int helperTime;
    DText dtext;
    Reward r;
    Snake snake;
    void checkIfReward();
    void checkIfDead();
    SnakeDrawing snakeDrawing;
    void createReward();
    int choosedMode;
    int tileSize;
    int mapSize;
    int speed;
    sf::Color bodyColor;
    sf::Color headColor;

public:
    SnakeEntity();
    void resetGame();
    void load();
    int getScore();
    void play(sf::RenderTarget& target);
    void setGameOpts(int choosedMode, int speed, int tileSize, int mapSize, sf::Color bodyColor, sf::Color headColor);
};

