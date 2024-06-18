#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "header.h"
#include "Game.h"
int START_X = 460; //1920-1000=920 920/2
int START_Y = 40; //1080-1000=80 80/2;
int gameState = 0; //0 - menu, 1 - playing, 2 - dying, 3 - gameOver, globalne

char pressed = sf::Keyboard::D; //wcisniety klawisz, globalne
char prevPressed = sf::Keyboard::P; //wczesniej wcisniety klawisz, globalne
sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "Snake"); //okienko 
int main()
{
    Game game;
    game.load();
    while (window.isOpen())
    {
        
        sf::Event event;

        while (window.pollEvent(event)) //reagowanie na wcisniecie klawiszy
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            if (event.type == sf::Event::KeyPressed && //jesli wcisniety klawisz to WASD lub Enter to przekazujemy ten wcisniety obecnie klawisz klasie game
                (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S
                    || event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D))
            { 
                pressed = event.key.code; //jesli to WASD to przekazujemy, ze pressed to wcisniety teraz klawisz
                game.keyPressed(event.key.code);
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter )
            {
                game.keyPressed(event.key.code);
            }
     
        }
        window.clear(sf::Color(206, 240, 245)); //czyszczenie okna
        game.play(window); //wyswietlanie gry
        window.display();
    }

}
