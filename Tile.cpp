#include "Tile.h"

Tile::Tile()
{
	active = false;
	pressed = false;
	alphaIdle = 0;
	alphaHover = 0;
	alphaPressed = 0;
}

Tile::Tile(sf::Vector2f position, float size, bool active)
{
	colorActive = sf::Color::Green;
	colorInactive = sf::Color::White;
	shape.setSize(sf::Vector2f(size, size));
	shape.setFillColor(this->colorInactive);
	shape.setPosition(position);
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(sf::Color::Black);
	active = active;
	pressed = false;
	alphaIdle = 100;
	alphaHover = 255;
	alphaPressed = 50;
}

Tile::~Tile()
{
}

void Tile::update(sf::Vector2f& mousePosView, const bool lmb_pressed)
{
	pressed = false;
	const sf::Color sc = shape.getFillColor();

	if (shape.getGlobalBounds().contains(mousePosView))//hover
	{
		shape.setFillColor(sf::Color(sc.r, sc.g, sc.b, alphaHover));
		if (lmb_pressed)//mouse click
		{
			shape.setFillColor(sf::Color(sc.r, sc.g, sc.b, alphaPressed));
			pressed = true;
		}
	}
	else 
	{
		shape.setFillColor(sf::Color(sc.r, sc.g, sc.b, alphaIdle));
	}
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
