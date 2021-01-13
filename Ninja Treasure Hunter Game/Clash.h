#pragma once
#include <SFML/Graphics.hpp>
class Clash
{
public:
	Clash(sf::RectangleShape& body);
	~Clash();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckClash(Clash other, sf::Vector2f & direction, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

private:
	sf::RectangleShape& body;
};

