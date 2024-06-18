#include "SnakeDrawing.h"
#include "header.h"
#include <SFML/Graphics.hpp>

void recToVecs(sf::Vertex* triangles, unsigned int gap, unsigned int size, int x, int y, int START_X, int START_Y) { 
    //funkcja zamieniaja kwadrat w danym miejscu na 2 trojkaty
    triangles[0].position = sf::Vector2f(START_X + x * size + gap, START_Y + y * size + gap);
    triangles[1].position = sf::Vector2f(START_X + (x + 1) * size - gap, START_Y + y * size + gap);
    triangles[2].position = sf::Vector2f(START_X + x * size + gap, START_Y + (y + 1) * size - gap);
    triangles[3].position = sf::Vector2f(START_X + x * size + gap, START_Y + (y + 1) * size - gap);
    triangles[4].position = sf::Vector2f(START_X + (x + 1) * size - gap, START_Y + y * size + gap);
    triangles[5].position = sf::Vector2f(START_X + (x + 1) * size - gap, START_Y + (y + 1) * size - gap);
}

void SnakeDrawing::create(unsigned int bodyGap, unsigned int headGap, unsigned int size, Snake snake, sf::Color headColor, sf::Color bodyColor)
//funkcja rysujaca weza, dziala za kazdym "tickiem", bo waz sie ciagle zmienia
{
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(snake.x.size() * 6);

    sf::Vertex* triangles = &m_vertices[0];
    recToVecs(triangles, headGap, size, snake.x[0], snake.y[0], START_X, START_Y); //zamieniamy kwadraty glowy na trojkaty

    for (int k = 0; k < 6; k++) { //nadajemy glowie weza odpowiedni kolor
        triangles[k].color = headColor;
    }
    for (int i = 1; i < snake.x.size(); i++) { //zmieniamy cialo weza na trojkaty i nadajemy odpowiedni kolor
        sf::Vertex* triangles = &m_vertices[i * 6];

        recToVecs(triangles, bodyGap, size, snake.x[i], snake.y[i], START_X, START_Y);

        for (int k = 0; k < 6; k++) {
            triangles[k].color = bodyColor;
        }
    }

}

void SnakeDrawing::draw(sf::RenderTarget& target, sf::RenderStates states) const //rysowanie weza
{
    states.transform *= getTransform();

    target.draw(m_vertices, states);
}
