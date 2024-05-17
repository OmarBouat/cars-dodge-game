#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib> // For random number generation
#include <ctime>

#pragma once

class Game
{
private:
    struct triple{
        sf::Sprite sprite;
        sf::Texture texture;
        bool av;
    };
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event ev;
    sf::Clock clock;
    long long timer;
    sf::Texture roadTexture;
    sf::Sprite roadSprite;
    sf::Font font;
    sf::Text scoreText;
    long long score;
    sf::Texture carTexture;
    sf::Sprite carSprite;
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
    sf::Clock enemyClock, levelClock;
    sf::Music music;
    int nbEnemies;
    int nbAv,timeToRespown;
    double pas;
    std::map<int, triple> Enemies;
    void initVariables();
    void initWindow();
    void initElements();
    void eventLoop();
    void updateEnemies();
    bool checkLose();
public:
    Game();
    ~Game();
    void update();
    void render();
    bool getWindowIsOpen();
    void lunchGame();
};

