#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
//zmienne globalne
extern int START_X;
extern int START_Y;
extern int gameState;
extern char pressed;
extern char prevPressed;

//structy
struct Snake {
    std::vector <int> x;
    std::vector <int> y;
    int head[2];
};

struct gameOptions {
    int choosedDiff; //0 - easy, 1 - normal, 2 - hard
    int choosedMapSize; //0 - small, 1 - medium, 2 - big
    int choosedMode; //0 - normal, 1 - checkered
    int choosedColor; //0 - orange, 1 - violet
};