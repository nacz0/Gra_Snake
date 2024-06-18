#include "GameOver.h"

void GameOver::keyPressed(sf::Keyboard::Key k)
//jesli klikniemy enter przechodzimy dalej
{{
        if (k == sf::Keyboard::Enter)
        {
            if (canRestart) { //jesli minal juz odpowiedni czas, mozemy przejsc z powrotem do menu 
                helperTime = 0;
                canRestart = false;
                pressed = sf::Keyboard::P;
                gameState = 0;
            }
        }
    }
}

GameOver::GameOver() //inicjalizacja zmiennych
{
    blink = false;
    helperTime = 0;
    canRestart = false;
}

void GameOver::load() //load
{ 
        dtext.load();
}

void GameOver::display(sf::RenderTarget& target, int score)
//rysowanie planszy koncowej
{
        sf::Time time1 = clock.getElapsedTime();
        dtext.draw(target, "GAME OVER", 100, START_X + 270, START_Y + 350, sf::Color(0, 0, 0));
        dtext.draw(target, "Score:" + std::to_string(score), 100, START_X + 330, START_Y + 500, sf::Color(0, 0, 0));


        if (canRestart) { //jesli minal odpowiedni czas wyswietlamy tekst restart
            dtext.draw(target, "Restart", 100, START_X + 320, START_Y + 700, blink ? sf::Color(255, 255, 255) : sf::Color(250, 145, 60));
        }

        if (time1.asMilliseconds() > (blink ? 150 : 850)) {
            helperTime += (blink ? 150 : 850);
            if (helperTime > 1900) {
                canRestart = true;
            }
            blink = !blink;
            clock.restart();
        }

        
    
}

