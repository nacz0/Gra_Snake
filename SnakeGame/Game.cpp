#include "Game.h"
#include "header.h"

void Game::play(sf::RenderTarget& target)
//gra
{
	if (gameState == 0) { //jesli jestesmy w fazie menu, wyswietlamy menu
		snake.resetGame();
		menu.display(target);
   }
	if (gameState == 1 || gameState == 2) { //jesli jestemy w fazie rozgrywki lub umierania, przekazujemy klasie odpowiedzialnej 
		//za rozgrywke odpowienie ustawienia wziete od klasy menu i rysujemy plansze
		gameOptions gameOpts = menu.getGameOptions();
		snake.setGameOpts(gameOpts.choosedMode, speed[gameOpts.choosedDiff], tileSize[gameOpts.choosedMapSize], mapSize[gameOpts.choosedMapSize], bodyColors[gameOpts.choosedColor], headColors[gameOpts.choosedColor]);
		loadTiles(gameOpts.choosedMapSize, gameOpts.choosedColor);
		target.draw(tiles);
		snake.play(target);
		
	}
	if (gameState == 3) { //jesli umarlismy wyswietlamy plansze koncowa
		gameOver.display(target, snake.getScore());
	}
}

void Game::load() //load
{
	menu.load();
	snake.load();
	gameOver.load();
	
}

void Game::loadTiles(int choosedMapSize, int choosedColor)
//zaladowanie planszy w zaleznosci od rozmaiaru mapy i koloru
{
	if (choosedMapSize == 0) tiles.load(sf::Vector2u(162, 162), 6, 6, tileColors[choosedColor], secTileColors[choosedColor]);
	if (choosedMapSize == 1) tiles.load(sf::Vector2u(100, 100), 10, 10, tileColors[choosedColor], secTileColors[choosedColor]);
	if (choosedMapSize == 2) tiles.load(sf::Vector2u(62, 62), 16, 16, tileColors[choosedColor], secTileColors[choosedColor]);
}

void Game::keyPressed(sf::Keyboard::Key k)
//przekazanie kliknietego przycisku fazom tekstowym
{
	if (gameState == 0)
		menu.keyPressed(k);
	if (gameState==3)
		gameOver.keyPressed(k);
	
}

