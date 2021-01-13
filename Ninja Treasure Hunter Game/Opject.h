#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Clash.h"
#include "ResourceManager.h"

class Opject
{
public:
	Opject(int num, sf::Vector2f size, sf::Vector2f position);
	~Opject();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::FloatRect getGlobalBounds() { return body.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetSize() { return body.getSize(); }
	Collider GetCollider() { return Collider(body); }
	Clash GetClash() { return Clash(body); }

private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
};

