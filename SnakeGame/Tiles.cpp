#include <SFML/Graphics.hpp>
#include <vector>
#include "Tiles.h"
#include "header.h"
bool Tiles::load(sf::Vector2u tileSize, int width, int height, sf::Color tileColor, sf::Color secTileColor) 
//zgranie wszystkich tile, poniewa¿ nie zmieniaja sie w trakcie rozgrywki
{
    m_vertices.setPrimitiveType(sf::Triangles); //jako ze jeden tile to kwadrat, to dzielimy to na 2 trojkaty, kazdy ma 3 wierzcholki
    m_vertices.resize(width * height * 6);

    for (int i = 0; i < width; ++i) //odpowiednie ustawiamy pozycje wszystkich wierzcholkow i nadajemy im odpowiedni kolor
        for (int j = 0; j < height; ++j) 
        {
            sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

            triangles[0].position = sf::Vector2f(START_X + i * tileSize.x, START_Y + j * tileSize.y);
            triangles[1].position = sf::Vector2f(START_X + (i + 1) * tileSize.x, START_Y + j * tileSize.y);
            triangles[2].position = sf::Vector2f(START_X + i * tileSize.x, START_Y + (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(START_X + i * tileSize.x, START_Y + (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f(START_X + (i + 1) * tileSize.x, START_Y + j * tileSize.y);
            triangles[5].position = sf::Vector2f(START_X + (i + 1) * tileSize.x, START_Y + (j + 1) * tileSize.y);

            for (int k = 0; k < 6; k++) {
                if ((i + j) % 2 == 0) {
                    triangles[k].color = tileColor;
                }
                else {
                    triangles[k].color = secTileColor;
                }
            }
        }
    return true;
}


void Tiles::draw(sf::RenderTarget& target, sf::RenderStates states) const //rysujemy gotowy juz "obraz" tile'i
{
    states.transform *= getTransform();
    target.draw(m_vertices, states);
}

