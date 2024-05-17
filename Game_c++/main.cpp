#include <bits/stdc++.h>
#include "game.cpp"
#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Menu");
    window.setFramerateLimit(60);

    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    if (!bgTexture.loadFromFile("./sources/bg.jpg")) {
        std::cout << "failed to load\n";
    }

    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(800.0f / bgTexture.getSize().x, 600.0f / bgTexture.getSize().y);


    sf::Font font;
    if (!font.loadFromFile("./sources/LuckiestGuy-Regular.ttf")) {
        std::cerr << "Failed to load font file LuckiestGuy-Regular.ttf" << std::endl;
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
                        Game game;
                        game.lunchGame();
                        while (game.getWindowIsOpen()) {
                            game.update();
                            game.render();
                        }
                        game.~Game();
                        main();
                    } else if (exitButton.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }
            }
        }

        // window.clear(sf::Color::Black); // Draw a black background

        // Draw bounding boxes around text objects for debugging
        sf::RectangleShape titleBounds(sf::Vector2f(title.getGlobalBounds().width+30, title.getGlobalBounds().height+50));
        titleBounds.setPosition(sf::Vector2f(title.getPosition().x - 10, title.getPosition().y));
        titleBounds.setFillColor(sf::Color::Transparent);
        titleBounds.setOutlineColor(sf::Color::Red);
        titleBounds.setOutlineThickness(1.f);

        title.setOutlineColor(sf::Color::Black); // Outline color
        title.setOutlineThickness(2);
        playButton.setOutlineColor(sf::Color::Black); // Outline color
        playButton.setOutlineThickness(2);
        exitButton.setOutlineColor(sf::Color::Black); // Outline color
        exitButton.setOutlineThickness(2);
        window.draw(bgSprite);
        window.draw(titleBounds);

        window.draw(title);
        window.draw(playButton);
        window.draw(exitButton);

        window.display();
    }

    return 0;
}