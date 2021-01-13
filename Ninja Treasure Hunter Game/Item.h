#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"
#include "Animation.h"
#include "Collider.h"
#include "Clash.h"


class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position);
	~Item();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direction);

	sf::FloatRect getGlobalBounds() { return body.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	Clash GetClash() { return Clash(body); }

	void setPos(sf::Vector2f newPos)
	{
		body.setPosition(newPos);
	}

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	bool faceRight;
	sf::Vector2f velocity;
};

