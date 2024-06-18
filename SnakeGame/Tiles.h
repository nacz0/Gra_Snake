#pragma once
#include <SFML/Graphics.hpp>
//klasa odpowiedzialna za rysowanie planszy
class Tiles : public sf::Drawable, public sf::Transformable
{
public:
    bool load(sf::Vector2u tileSize, int width, int height,sf::Color tileColor, sf::Color secTileColor);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
};

