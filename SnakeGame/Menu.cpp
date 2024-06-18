#include "Menu.h"

Menu::Menu()
//ustawienia poczatkowe
{
    state = 0;
    blink = false;
    gameOpts.choosedDiff = 0;
    gameOpts.choosedMapSize = 0;
    gameOpts.choosedMode = 0;
    gameOpts.choosedColor = 0;
}

void Menu::load() //load
{
    dtext.load();
    
}

void Menu::keyPressed(sf::Keyboard::Key k) //reagowanie na klikniecia klawiszy
{
    std::cout << k << std::endl;
    if (k == sf::Keyboard::W) //zmieniamy ustawienie w gore
    {
        if (state == 0)
        {
            if (gameOpts.choosedDiff != 0)
            {
                gameOpts.choosedDiff--;
            }
        } 
        else if (state == 1)
        {
            if (gameOpts.choosedMapSize != 0)
            {
                gameOpts.choosedMapSize--;
            }
        }
        else if (state == 2)
        {
            if (gameOpts.choosedMode != 0) {
                gameOpts.choosedMode--;
            }
        }
        else if (state == 3)
        {
            if (gameOpts.choosedColor != 0) {
                gameOpts.choosedColor--;
            }
        }
            
    }
        
    if (k == sf::Keyboard::S) //zmieniamy ustawienie w dol
    {
        if (state == 0)
        {
            if (gameOpts.choosedDiff != 2) {
                gameOpts.choosedDiff++;
            }
        }  
        else if (state == 1)
        {
            if (gameOpts.choosedMapSize != 2)
            {
                gameOpts.choosedMapSize++;
            }
        }
        else if (state == 2)
        {
            if (gameOpts.choosedMode != 1) {
                gameOpts.choosedMode++;
            }
        }
        else if (state == 3)
        {
            if (gameOpts.choosedColor != 1) {
                gameOpts.choosedColor++;
            }
        }
            
    }
        
    if (k == sf::Keyboard::Enter) //przechodzimy dalej
    {
        blink = false;

        pressed = sf::Keyboard::D;
        if (state == 1)
            state = 2;
        else if (state==0)
            state = 1;
        else if (state == 2) {
            state = 3;
        }
        else if (state == 3) { //a w ostatnim ustawieniu zmieniamy stan gry na rozgrywke
            gameState = 1;
            state = 0;
        }
    }
}

void Menu::display(sf::RenderTarget& target)
//rysujemy na planszy odpowiedni tekst do ustawien
{
    sf::Time time1 = clock.getElapsedTime();
    if (gameState == 0) {
       
        sf::Color color = blink ? sf::Color(255, 255, 255) : sf::Color(250, 145, 60); //jesli miga biale, jesli nie pomaranczowe
        dtext.draw(target, "SNAKE", 200, START_X + 300, START_Y, sf::Color(0, 255, 0));

        if (state == 0) {
            for (int i = 0; i < 3; i++) {
                dtext.draw(target, difficulties[i], 140, START_X + 300, START_Y + (i * 150) + 200,
                    i == gameOpts.choosedDiff ? (color) : sf::Color(204, 209, 217));
            }
        }
        if (state == 1) {
            for (int i = 0; i < 3; i++) {
                dtext.draw(target, mapSizes[i], 140, START_X + 300, START_Y + (i * 150) + 200,
                    i == gameOpts.choosedMapSize ? (color) : sf::Color(204, 209, 217));
            }
        }
        if (state == 2) {
            for (int i = 0; i < 2; i++) {
                dtext.draw(target, modes[i], 140, START_X + 300, START_Y + (i * 150) + 200,
                    i == gameOpts.choosedMode ? (color) : sf::Color(204, 209, 217));
            }
        }
        if (state == 3) {
            for (int i = 0; i < 2; i++) {
                dtext.draw(target, colors[i], 140, START_X + 300, START_Y + (i * 150) + 200,
                    i == gameOpts.choosedColor ? (color) : sf::Color(204, 209, 217));
            }
        }

        if (time1.asMilliseconds() > (blink ? 150 : 850)) {
            blink = !blink;
            clock.restart();
        }

    }
}

gameOptions Menu::getGameOptions()
//zwracamy klasie Game ustawienia
{
    return gameOpts;
}
