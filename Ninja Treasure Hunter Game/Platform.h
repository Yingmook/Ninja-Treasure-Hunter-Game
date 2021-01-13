#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Clash.h"
#include "ResourceManager.h"

class Platform
{
public:
	Platform(int num, sf::Vector2f size, sf::Vector2f position);
	~Platform();

	void Draw(sf::RenderWindow& window);

	sf::FloatRect getGlobalBounds() { return body.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetSize() { return body.getSize(); }
	Collider GetCollider() { return Collider(body); }
	Clash GetClash() { return Clash(body); }

private:
	sf::RectangleShape body;
	//sf::Texture platfrom1;
	//std::vector<Platform> platforms;
};

