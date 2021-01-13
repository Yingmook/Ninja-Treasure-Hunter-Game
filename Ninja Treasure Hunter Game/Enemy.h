#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Collider.h"
#include "Platform.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
	~Enemy();
	void Update(float deltaTime, int walkRight);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::FloatRect getGlobalBounds() { return body.getGlobalBounds(); }
	//sf::Vector2f GetV() { return velocity; }

	void setPos(sf::Vector2f newPos)
	{
		body.setPosition(newPos);
	}
	void move(sf::Vector2f newPos)
	{
		body.move(newPos);
	}
	void setTextureRect(sf::IntRect rect)
	{
		body.setTextureRect(rect);
	}
	
private:
	bool checkEnenyRunRight(Platform platform)
	{
		if (body.getPosition().x <= platform.getGlobalBounds().width)
			return true;
		return true;
	}

public:
	Animation animation;
	sf::Vector2f velocity;
	sf::RectangleShape body;

private:
	float speed, delay;
	bool faceRight;
	unsigned int row;

	//sf::Vector2f velocity;
	sf::Clock clock;
	float deltaZombie = 0.0f, delayZombie;
};

