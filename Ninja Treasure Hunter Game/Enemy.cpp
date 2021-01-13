#include "Enemy.h"



Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	//this->delay = delay;
	row = 0;
	faceRight = true;
	//delayZombie = 2.0f;

	//body.setSize(sf::Vector2f(50.0f, 75.0f));
	body.setSize(sf::Vector2f(65.0f, 80.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
	body.setFillColor(sf::Color::White);
}


Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, int walkRight)
{
	deltaZombie += clock.restart().asSeconds();
	row = 0;
	velocity.x = 0.0f;
	velocity.x += speed;
	velocity.y += 981.0f * deltaTime;

	if(walkRight == 0)
	{
		faceRight = false;
		velocity.x *= -1.0f;
	}
	else if (walkRight == 1)
	{
		faceRight = true;
	}
	else if (walkRight == 2)
	{
		row = 1;
		faceRight = false;
		velocity.x *= -1.2f;
	}
	else if (walkRight == 3)
	{
		row = 1;
		faceRight = true;
		velocity.x *= 1.2f;
	}
	else if (walkRight == 4)
	{
		row = 2;
		faceRight = false;
		velocity.x *= -1.2f;
	}
	else if (walkRight == 5)
	{
		row = 2;
		faceRight = true;
		velocity.x *= 1.2f;
	}
	body.move(velocity * deltaTime);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Enemy::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Enemy::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left.
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom.
		velocity.y = 0.0f;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;
	}
}
