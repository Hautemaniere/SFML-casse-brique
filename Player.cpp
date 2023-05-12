#include "player.h"



Player::Player(int y, int width, int height)

{
	this->y = y;
	position = sf::Vector2f(0, y);
	size = sf::Vector2f(width, height);
	shape.setSize(size);
	shape.setFillColor(sf::Color::White);
}

Player::~Player()
{

}

void Player::draw(sf::RenderWindow& window)
{
	position.x = sf::Mouse::getPosition(window).x - size.x / 2;
	shape.setPosition(position);

	window.draw(shape);
}

sf::RectangleShape Player::getShape()
{
	return shape;
}

sf::Vector2f Player::getPosition()
{
	return position;
}

sf::Vector2f Player::getSize()
{
	return size;
}

