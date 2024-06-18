#pragma once
#include <SFML/Graphics.hpp>
#include "header.h"
//klasa odpowiedzialna za rysowanie weza
class SnakeDrawing : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray m_vertices;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void create(unsigned int bodyGap, unsigned int headGap, unsigned int size, Snake snake, sf::Color headColor, sf::Color bodyColor);
    
    
};

