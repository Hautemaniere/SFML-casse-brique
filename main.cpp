#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "Brick.h"
#include <iostream>
#include <deque>

double mapValue(double value, double min, double max, double nMin, double nMax)
{
    double newVal = (((value - min) / (max - min)) * (nMax - nMin)) + nMin;
    return newVal;
}

int main(int argc, char** argv)
{
    std::deque<Brick*> bricks;

    const int BRICK_WIDTH = 50;
    const int BRICK_HEIGHT = 20;
    const int BRICK_MARGIN = 10;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 13; j++) {
            int x = j * (BRICK_WIDTH + BRICK_MARGIN) + BRICK_MARGIN;
            int y = i * (BRICK_HEIGHT + BRICK_MARGIN) + BRICK_MARGIN;
            bricks.push_back(new Brick(x, y, BRICK_WIDTH, BRICK_HEIGHT, 2));
        }
    }

    Ball ball(200, 250, 10, 400);
    Player player(550, 100, 10);
    Brick brick(25, 50, 50, 20, 2);
    sf::RenderWindow window(sf::VideoMode(800, 600), "C le Quass Brik");

    // Boule du bout
    sf::CircleShape circle3;
    circle3.setRadius(25);
    circle3.setPosition(180, 100);
    circle3.setFillColor(sf::Color::Blue);
    circle3.setOutlineColor(sf::Color::White);
    circle3.setOutlineThickness(2);

    //rectangle
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(100, 50));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(2);
    rectangle.setPosition(100, 100);


    // Boule du bas
    sf::CircleShape circle;
    circle.setRadius(20);
    circle.setPosition(85, 120);
    circle.setFillColor(sf::Color::Blue);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(2);


    // Boule du haut
    sf::CircleShape circle2;
    circle2.setRadius(20);
    circle2.setPosition(85, 85);
    circle2.setFillColor(sf::Color::Blue);
    circle2.setOutlineColor(sf::Color::White);
    circle2.setOutlineThickness(2);

    sf::RectangleShape rdr2;
    rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Clock clock;
    float ellapsedTime = 0;

    while (window.isOpen())
    {
        ellapsedTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball.move(ellapsedTime);
        ball.manageCollisionWith(window);
        ball.manageCollisionWith(player);
        for (int i = 0; i < bricks.size(); i++)
        {
            if (bricks[i]->isAlive())
            {
                bricks[i]->draw(window);
                ball.manageCollisionWith(bricks[i]);
            }
            else
            {
                bricks[i]->destroyAndDelete(bricks);
            }
        }

        window.clear();

        for (int i = 0; i < bricks.size(); i++) {
            bricks[i]->draw(window);
        }

		double mappedValue = mapValue(0, 0, window.getSize().y, 0, 255);
		rdr2.setFillColor(sf::Color(mappedValue, mappedValue, 190));
		rdr2.setPosition(0, 0);


        window.draw(rectangle);
        window.draw(circle);
        window.draw(circle2);
        window.draw(circle3);


        window.draw(rdr2);
        player.draw(window);
        ball.draw(window);
        for (auto& brick : bricks) {
            brick->draw(window);
        }
        window.display();
    }

    for (int i = 0; i < bricks.size(); i++) {
        delete bricks[i];
    }
    bricks.clear();

    return 0;
}