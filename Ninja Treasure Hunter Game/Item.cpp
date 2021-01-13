#include "Item.h"



Item::Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	row = 0;
	faceRight = true;
}


Item::~Item()
{
}

void Item::Update(float deltaTime)
{
	row = 0;
	faceRight = true;
	velocity.x = 0.0f;
	velocity.y += 981.0f * deltaTime;

	body.move(velocity * deltaTime);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Item::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Item::OnCollision(sf::Vector2f direction)
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

