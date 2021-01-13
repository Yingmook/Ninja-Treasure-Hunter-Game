#include "Opject.h"



Opject::Opject(int num, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	//body.setTexture(texture);
	body.setPosition(position);

	switch (num)
	{
	case 1: body.setTexture(ResourceManager::GetInstance()->RequestTexture("bush"));
		break;
	case 2:  body.setTexture(ResourceManager::GetInstance()->RequestTexture("crate"));
		break;
	case 3:  body.setTexture(ResourceManager::GetInstance()->RequestTexture("arrow"));
		break;
	case 4:  body.setTexture(ResourceManager::GetInstance()->RequestTexture("stone"));
		break;
	case 5:  body.setTexture(ResourceManager::GetInstance()->RequestTexture("tree"));
		break;
	case 6:  body.setTexture(ResourceManager::GetInstance()->RequestTexture("skeleton"));
		break;
	default:
		break;
	}
}

Opject::~Opject()
{
}

void Opject::Update(float deltaTime)
{
	velocity.x = 0.0f;
	velocity.y += 9.810f * deltaTime;

	body.move(velocity * deltaTime);
}

void Opject::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Opject::OnCollision(sf::Vector2f direction)
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
