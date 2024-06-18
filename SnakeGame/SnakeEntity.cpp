#include "SnakeEntity.h"
#include "header.h"
SnakeEntity::SnakeEntity() //ustawienie zmiennych poczatkowych
{
    r.x = 5;
    r.y = 5;
    helperTime = 0;
    choosedMode = 0;
    speed = 150;
    mapSize = 1;
    tileSize = 1;
    helperTime = 0;
    move = 0;
    toGet = 0;
}

void SnakeEntity::load() //wolamy potrzebne funkcje i ustawiamy poczatkowe dane weza w zaleznosci od wybranego trybu
{
    dtext.load();
    createReward();
    toGet = 0;
    move = 0;
    if (choosedMode == 1) {
    snake.x = { 2,0 };
    snake.y = { 2,2 };
    snake.head[0] = 2;
    snake.head[1] = 2;
    }
    if (choosedMode == 0) {
        snake.x = { 1,0 };
        snake.y = { 0,0 };
        snake.head[0] = 1;
        snake.head[1] = 0;
    }
};
void SnakeEntity::checkIfDead() //sprawdzamy czy nie umarlismy, czyli czy aby przypadkiem glowa naszego weza nie pokrywa sie z sciana lub komorka ciala weza
{
    if (snake.head[0] > mapSize || snake.head[0] < 0 || snake.head[1] > mapSize || snake.head[1] < 0)
        gameState = 2;
    for (int i = 1; i < snake.x.size(); i++) {
        if (snake.head[0] == snake.x[i] && snake.head[1] == snake.y[i])
            gameState = 2;
    }
}

int SnakeEntity::getScore() //zwraca wynik gry
{
    return snake.x.size() - 1;
}

void SnakeEntity::play(sf::RenderTarget& target) //funkcja odpowiedzialna za rozgrywke
{
    

    
    sf::Time time1 = clock.getElapsedTime();
    
    if (gameState == 1 || gameState == 2) {


        //rysowanie napisow
        dtext.draw(target, "SNAKE", 140, 50, 50, sf::Color(0, 255, 0));

        dtext.draw(target, "Score:" + std::to_string(snake.x.size() - 1), 100, 1500, 50, sf::Color(204, 209, 217));

        //rysowanie nagrody
        sf::RectangleShape reward(sf::Vector2f(tileSize*0.6, tileSize*0.6));
        reward.setOutlineThickness(20);
        reward.setOutlineColor(sf::Color(255, 255, 255, 0));
        reward.setFillColor(sf::Color(0, 0, 255));
        reward.setPosition(START_X + (r.x * tileSize) + tileSize * 0.2, START_Y + (r.y * tileSize) + tileSize * 0.2);
        reward.setPosition(START_X + (r.x * tileSize) + tileSize * 0.2, START_Y + (r.y * tileSize) + tileSize * 0.2);
        target.draw(reward);

        //rysowanie weza
        snakeDrawing.create(tileSize*0.13, tileSize*0.08, tileSize, snake, blink ? sf::Color(255, 255, 255) : headColor, bodyColor);
        target.draw(snakeDrawing);

        if (gameState == 1) {
            //co okreslona liczbe czasu poruszamy weza w kierunku ktory zostal ostatnio klikniety
            if (time1.asMilliseconds() > speed) {
                clock.restart();
                switch (pressed) {
                case sf::Keyboard::W:
                    if (prevPressed == sf::Keyboard::S) {
                        pressed = sf::Keyboard::S;
                        snake.head[1]++;
                    }
                    else {
                        snake.head[1]--;
                    }
                    break;
                case sf::Keyboard::S:
                    if (prevPressed == sf::Keyboard::W) {
                        pressed = sf::Keyboard::W;
                        snake.head[1]--;
                    }
                    else {
                        snake.head[1]++;
                    }
                    break;
                case sf::Keyboard::A:
                    if (prevPressed == sf::Keyboard::D) {
                        pressed = sf::Keyboard::D;
                        snake.head[0]++;
                    }
                    else {
                        snake.head[0]--;
                    }
                    break;
                case sf::Keyboard::D:
                    if (prevPressed == sf::Keyboard::A) {
                        pressed = sf::Keyboard::A;
                        snake.head[0]--;
                    }
                    else {
                        snake.head[0]++;
                    }
                    break;
                }
                //sprawdzamy czy aby przypadkiem nie umarlismy
                checkIfDead();
                if (gameState == 1) {
                    
                    prevPressed = pressed;
                    snake.x.insert(snake.x.begin(), snake.head[0]);
                    snake.y.insert(snake.y.begin(), snake.head[1]);
                    if (choosedMode == 1) { //jesli gramy w tryb w kratke
                    move = !move; //poruszamy sie co dwa "ticki" wiec zmieniamy zmienna boolowa
                    if (!move ) { //jesli akurat sie nie poruszamy cialem, to kasujemy komorke cialo zaraz przy glowie
                        snake.x.erase(snake.x.begin() + 1);
                        snake.y.erase(snake.y.begin() + 1);
                    }
                    }
                    checkIfReward(); //sprawdzamy czy nie zjedlismy nagrody
                }
            }

        }
        if (gameState == 2) { //jesli wlasnie umieramy
            sf::Time timeToSnakeBlink = clock.getElapsedTime();
            if (timeToSnakeBlink.asMilliseconds() > 200) { //blyskanie weza
                helperTime += 200;
                if (helperTime > 1500) { // po uplywie 1,5s przechodzimy do planszy koncowej
                    helperTime = 0;
                    gameState = 3;
                }
                clock.restart();
                blink = !blink;
                timeToSnakeBlink = sf::milliseconds(0);
                
            }
        }
    }
}

void SnakeEntity::setGameOpts(int cM, int s, int tS, int mS, sf::Color bC, sf::Color hC) //zwracamy klasie Game wybrane opcje rozgrywki
{
    choosedMode = cM;
    speed = s;
    tileSize = tS;
    mapSize = mS;
    bodyColor = bC;
    headColor = hC;
}


void SnakeEntity::checkIfReward() //sprawdzamy czy glowa weza spotkala sie z nagroda, jesli tak, to nie usuwamy ostatniej czesci ciala 
                                  //(lub "pamietamy" o tym dzieki zmiennej w trybie w kratke
{
    if ((r.x == snake.head[0] && r.y == snake.head[1])) { //jesli zjedlismy, to po prostu generujemy nowa nagrode
        createReward();
        if (choosedMode ==1 )
            toGet += 1; //w trybie w kratke nagrode "zapisujemy" poprzez zmienna, jako ze cialo znajduje sie co dwie kratki, nie zawsze chcemy zostawic w tym momencie ostatnia komorke ciala
    }
    else { //jesli nie
        if (choosedMode == 1) { 
            if (toGet > 0) //jesli mamy zapisana komorke do dodania, to nie kasujemy ostaniej komorki; zmienna nie jest boolowska, bo mo¿e zdarzyæ, ¿e dwa razy z rzêdu zjemy nagrodê
                toGet -= 1;
            else if (move) {
                snake.y.pop_back();
                snake.x.pop_back();
            }
        }
        if (choosedMode == 0) { //w trybie zwyklym po prostu kasujemy ostatnia komorke ciala
             snake.y.pop_back();
             snake.x.pop_back();
        }
        
        
    }
}


void SnakeEntity::resetGame() //funkcja resetuje grê, a wiêc przywraca do ustawieñ pocz¹tkowych
{
    move = 0;
    toGet = 0;
    if (choosedMode == 1) {
        snake.x = { 2,0 };
        snake.y = { 2,2 };
        snake.head[0] = 2;
        snake.head[1] = 2;
    }
    if (choosedMode == 0) {
        snake.x = { 1,0 };
        snake.y = { 0,0 };
        snake.head[0] = 1;
        snake.head[1] = 0;
    }

    pressed = sf::Keyboard::D;
    prevPressed = sf::Keyboard::P;

    createReward();
}

struct c {
    int x;
    int y;
};
void SnakeEntity::createReward() // funkcja tworzy "nagrodê" na losowym miejscu na planszy
{
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::vector <int> possibleRX;
    std::vector <int> possibleRY;
    std::vector<c> possibleR;

    //najpierw tworzymy vector z wszystkimi mo¿liwymi miejscami w których mog³aby powstaæ nagroda
    for (int i = 0; i < (mapSize + 1); i++) {
        possibleRX.push_back(i);
    }
    for (int i = 0; i < (mapSize + 1); i++) {
        possibleRY.push_back(i);
    }

    //sk³adamy w jeden
    for (int i = 0; i < (mapSize + 1); i++) {
        for (int j = 0; j < (mapSize + 1); j++) {
            c d;
            d.x = i;
            d.y = j;
            possibleR.push_back(d);
        }
    }
    //losowa liczba od 0 do ilosci mozliwych miejsc na nagrode - 1
    std::uniform_int_distribution<> randomNum(0, ((mapSize + 1) * (mapSize + 1)) - 1 - snake.x.size());

    //wykluczamy z mozliwych miejsc, te ktore pokrywaja sie z wezem
    for (int i = 0; i < snake.x.size(); i++) {
        for (int j = 0; j < possibleR.size(); j++) {
            if (possibleR[j].x == snake.x[i] && possibleR[j].y == snake.y[i]) {
                possibleR.erase(possibleR.begin() + j);
            }
        }
    }
    //bierzemy losowe miejsce sposrod tych ktore nie nakladaja sie na weza
    int rand = randomNum(gen);
    r.x = possibleR[rand].x;
    r.y = possibleR[rand].y;

}
