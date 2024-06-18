#include "DText.h"

void DText::load()
{
    if (!font.loadFromFile("fixedsys.ttf"))
        //ladujemy czcionke
    {
        std::cout << std::endl << "ERROR " << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(140);
}

void DText::draw(sf::RenderTarget& target, std::string string, int charSize, int x, int y, sf::Color color)
{
    //ustawiamy odpowiednie ustawienia danego tekstu
    text.setString(string);
    text.setCharacterSize(charSize);
    text.setPosition(x, y);
    text.setFillColor(color);
    target.draw(text);
}
