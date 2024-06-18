#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//klasa pomocnicza do generowania tekstu
class DText
{
private:
    sf::Text text;
    sf::Font font;
public:
    void load();
    void draw(sf::RenderTarget& target, std::string string, int charSize, int x, int y, sf::Color color);
};