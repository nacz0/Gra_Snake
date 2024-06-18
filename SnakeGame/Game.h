#pragma once
#include <SFML/Graphics.hpp>
#include "SnakeEntity.h"
#include "Tiles.h"
#include "Menu.h"
#include "GameOver.h"
//glowna klasa odpowiedzialna za rozgrywke
class Game
{
private:
	Tiles tiles;
	SnakeEntity snake;
	Menu menu;
	GameOver gameOver;
	void loadTiles(int choosedMapSize, int choosedColor);
	int mapSize[3] = { 5,9,15 }; //rozmiary mapy
	int tileSize[3] = { 162,100,62 }; //rozmiary pojedynczego tile'a
	int speed[3] = { 400,300,200 }; //szybkosc tj. czas w ms pomiedzy kazdym poruszeniem weza
	sf::Color bodyColors[2] = { sf::Color(255, 0, 0),sf::Color(123, 18, 227) }; //kolory ciala weza
	sf::Color headColors[2] = { sf::Color(255, 102, 0),sf::Color(161, 18, 227) }; //kolory glowy weza
	sf::Color tileColors[2] = { sf::Color(101, 240, 31), sf::Color(154, 156, 166) }; //kolory tile
	sf::Color secTileColors[2] = { sf::Color(102, 199, 28), sf::Color(102, 103, 110) }; //kolory tile co dwa
public: 
	void play(sf::RenderTarget& target);
	void load();
	void keyPressed(sf::Keyboard::Key k);
};

