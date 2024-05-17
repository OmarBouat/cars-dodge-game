#include "game.h"
#include "sources.h"


void Game::initVariables(){
    this->timer = 0;
    this->score = 0;
    this->nbEnemies = 0;
    this->nbAv = 0;
    this -> pas = 2;
    this->timeToRespown = 2000;
}

void Game::initWindow(){
    this->videoMode.width = windowX;
    this->videoMode.height = windowY;
    this->window = new sf::RenderWindow(this->videoMode,"Cars game", sf::Style::Close);
    this->window->setFramerateLimit(144);
    if (!font.loadFromFile(fontStyle)) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    
    this->window->setMouseCursorVisible(false);

}

void Game::initElements(){
    // Background setting

    if (!music.openFromFile(MusicSrc)){
        std::cerr << "Error loading background music file" << std::endl;
    }
    music.setLoop(true);

    // Play the music
    music.play();

    if (!roadTexture.loadFromFile(roadIndex)) {
        std::cout << roadIndex << "failed to load\n";
    }
    roadSprite.setTexture(roadTexture);
    roadSprite.setScale(roadSpriteSize.x / roadTexture.getSize().x, roadSpriteSize.y / roadTexture.getSize().y);
    
    // Score text setting

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowX / 2 - 50, 10.f);
    scoreText.setOutlineColor(sf::Color::Black); // Outline color
    scoreText.setOutlineThickness(2);

    // Main car setting

    if (!carTexture.loadFromFile(carIndex)) {
        std::cout << carIndex << "failed to load\n";
    }
    carSprite.setTexture(carTexture);
    carSprite.setScale(carSpriteSize.x / carTexture.getSize().x, carSpriteSize.y / carTexture.getSize().y);
    carSprite.setPosition(window->getSize().x/2, window->getSize().y- carSpriteSize.y);
    

}
// Function to start the game
void Game:: lunchGame(){
    initWindow();
    initElements();
}

// Constructors
Game::Game(){
    initVariables();
    
}
// Destructors
Game::~Game(){
    delete this->window;
}
// Main event loop
void Game::eventLoop() {
    float velocity = 0.0f; // Initial velocity
    const float acceleration = 20.f; // Adjust as needed for desired responsiveness
    const float maxVelocity = 40.0f; // Adjust as needed for maximum speed

    while (this->window->pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::Closed :
                this->window->close();
                break;
            case sf::Event::MouseMoved :
                // Get the current mouse position relative to the window
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
                // Update the car's y position to match the mouse's y position
                this->carSprite.setPosition(std::min(std::max(static_cast<float>(mousePosition.x), 75.0f), windowX - 160.f),this->carSprite.getPosition().y);
                break;
        }
    }

    // Apply friction or deceleration to slow down the car
    if (velocity > 0) {
        velocity -= acceleration / 2; // Apply deceleration
        velocity = std::max(velocity, 0.0f); // Ensure velocity doesn't go negative
    } else if (velocity < 0) {
        velocity += acceleration / 2; // Apply deceleration
        velocity = std::min(velocity, 0.0f); // Ensure velocity doesn't go positive
    }

    // Optionally, limit the maximum velocity
    velocity = std::min(velocity, maxVelocity);
}

void Game::updateEnemies(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    sf::Time enemyTimer = enemyClock.getElapsedTime(), levelTimer = levelClock.getElapsedTime();
    if(levelTimer.asSeconds() >= 5) {
        levelClock.restart();
        pas += 0.2;
        timeToRespown = std::max(500 , timeToRespown - 100);
        
    }
    // respawn car
    
    if(enemyTimer.asMilliseconds() >= timeToRespown){
        enemyClock.restart();
        
        if(nbAv > 0){
            // Reallocation for an enemy car
            nbAv--;
            for(auto& i : Enemies){
                if(i.second.av == true){
                    i.second.texture.loadFromFile(enemiesIndex[std::rand() % enemiesIndex.size()]);
                    i.second.sprite.setTexture(i.second.texture);
                    i.second.sprite.setPosition(enemiesPostions[std::rand() % numberOfPositions], -300);
                    i.second.sprite.setScale(carSprite.getScale());
                    i.second.av = false;
                    break;
                }
            }
        }
        else{
            // create new enemy car
            Enemies[nbEnemies].sprite = sf::Sprite();
            Enemies[nbEnemies].texture = sf::Texture();
            Enemies[nbEnemies].texture.loadFromFile(enemiesIndex[static_cast<float>(std::rand() % enemiesIndex.size())]);
            Enemies[nbEnemies].sprite.setTexture(Enemies[nbEnemies].texture);
            Enemies[nbEnemies].sprite.setPosition(enemiesPostions[std::rand() % numberOfPositions], -300);
            Enemies[nbEnemies].sprite.setScale(carSprite.getScale());
            Enemies[nbEnemies].av = false;
            nbEnemies++;
        }
    }
    for(auto& pair : Enemies){
        auto& enemy = pair.second;

        if(enemy.sprite.getPosition().y >= windowY && enemy.av == false){ 
        enemy.av = true;
        nbAv++;
        }
        else{
            enemy.sprite.move(0, pas);
        }
}

}

bool Game::checkLose(){
    std::pair<int, int> a,b,c,d;
    a.first = carSprite.getPosition().x+10;
    a.second = carSprite.getPosition().y+10;
    b.first = a.first + carSprite.getGlobalBounds().width-10;
    b.second = a.second;
    c.first = b.first;
    c.second = a.second + carSprite.getGlobalBounds().height-10;
    d.first = a.first;
    d.second = c.second;
    for(auto i : Enemies){
        std::pair<int, int> e,f,g,h;
        e.first = i.second.sprite.getPosition().x+10;
        e.second = i.second.sprite.getPosition().y+10;
        f.first = e.first + carSprite.getGlobalBounds().width-10;
        f.second = e.second;
        h.first = e.first;
        h.second = e.second + carSprite.getGlobalBounds().height-10;
        g.first = f.first;
        g.second = h.second;
        if(a.first < e.first && e.first < b.first && a.second < e.second && e.second < d.second) return true;
        if(a.first < f.first && f.first < b.first && a.second < f.second && f.second < d.second) return true;
        if(a.first < g.first && g.first < b.first && a.second < g.second && g.second < d.second) return true;
        if(a.first < h.first && h.first < b.first && a.second < h.second && h.second < d.second) return true;
    }
    return false;
}

// Update the window function
void Game::update(){
    this->eventLoop();
    sf::Time elapsed = clock.restart();
    timer += elapsed.asMilliseconds(); // Update time in seconds
    score = timer/500;
    scoreText.setString("Score: " + std::to_string(score));
    updateEnemies();
    this->window->clear();
    this->window->draw(roadSprite);
    this->window->draw(carSprite);
    for(auto  i : Enemies){
        this->window->draw(i.second.sprite);
    }
    this->window->draw(scoreText);
    if(checkLose())window->close();
}

// Render the window function
void Game::render(){
    this->window->display();
}

bool Game::getWindowIsOpen(){
    return this->window->isOpen();
}

/*
#include <bits/stdc++.h>
#include "game.cpp"
#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Menu");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("./sources/arial.ttf")) {
        std::cerr << "Failed to load font file 'arial.ttf'" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text title("Game Menu", font, 50);
    title.setPosition(250.f, 50.f);

    sf::Text playButton("Play", font, 30);
    playButton.setPosition(350.f, 200.f);

    sf::Text exitButton("Exit", font, 30);
    exitButton.setPosition(350.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (playButton.getGlobalBounds().contains(mousePos)) {
                        window.close();
                        window.setActive(false);
                        Game game;
                        game.lunchGame();
                        while (game.getWindowIsOpen()) {
                            game.update();
                            game.render();
                        }
                        window.setActive(true);
                    } else if (exitButton.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }
            }
        }

        window.clear(sf::Color::Black); // Draw a black background

        // Draw bounding boxes around text objects for debugging
        sf::RectangleShape titleBounds(sf::Vector2f(title.getGlobalBounds().width+30, title.getGlobalBounds().height+50));
        titleBounds.setPosition(sf::Vector2f(title.getPosition().x - 10, title.getPosition().y));
        titleBounds.setFillColor(sf::Color::Transparent);
        titleBounds.setOutlineColor(sf::Color::Red);
        titleBounds.setOutlineThickness(1.f);
        window.draw(titleBounds);

        window.draw(title);
        window.draw(playButton);
        window.draw(exitButton);

        window.display();
    }

    return 0;
}
*/