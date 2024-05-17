#include <bits/stdc++.h>
#include "game.h"


// Main window parameters
int windowX = 600;
int windowY = 1000;
std::string fontStyle = "./sources/LuckiestGuy-Regular.ttf";
std::string MusicSrc = "./sources/letsgetloud.ogg";
// Background parameters
std::string roadIndex = "./sources/road.png";
float roadScaleFactor = 1.0f;
sf::Vector2f roadSpriteSize(windowX * roadScaleFactor, windowY * roadScaleFactor);

// Main car parameters
std::string carIndex = "./sources/car1.png";
float carScaleFactor = 0.15f;
sf::Vector2f carSpriteSize(windowX * carScaleFactor, windowY * carScaleFactor);
int carStep = 20;

// other cars parameters
//std::string enemyIndex = "./sources/enemy.png";
std::vector<std::string> enemiesIndex = {"./sources/enemy.png","./sources/enemy1.png","./sources/enemy2.png","./sources/enemy3.png","./sources/enemy4.png"};
// 75 , 187 , 309
std::vector<int> enemiesPostions = {75 , 187 , 309, 430};
int numberOfPositions = enemiesPostions.size();
