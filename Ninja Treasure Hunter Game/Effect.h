#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Player.h"
#include "Enemy.h"

class Effect
{
public:
	Effect(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int num);
	~Effect();

	void Update(float deltaTime, Player player);
	void Update2(float deltaTime, Enemy zombie);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	void setPos(sf::Vector2f newPos)
	{
		body.setPosition(newPos);
	}
	void move(sf::Vector2f newPos)
	{
		body.move(newPos);
	}


private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	sf::Clock clock;
	int num;
};

