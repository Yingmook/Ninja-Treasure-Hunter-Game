#include "Effect.h"



Effect::Effect(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int num) :
	animation(texture, imageCount, switchTime)
{
	this->num = num;
	row = 0;
	faceRight = false;
	//delayZombie = 2.0f;
	if(num == 0)
		body.setSize(sf::Vector2f(80.0f, 76.0f));
	else if(num == 1)
		body.setSize(sf::Vector2f(100.0f, 80.0f));
		//body.setSize(sf::Vector2f(80.0f, 76.0f));
	else if(num == 2)
		body.setSize(sf::Vector2f(60.0f, 40.0f));
	else if (num == 3)
		body.setSize(sf::Vector2f(80.0f, 80.0f));
	else if (num == 4)
		body.setSize(sf::Vector2f(400.0f, 300.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition({ 422234, 423432 });
	body.setTexture(texture);
}


Effect::~Effect()
{
}

void Effect::Update(float deltaTime, Player player)
{
	row = 0;
	velocity.x = 0.0f;
	//velocity.x += speed;
	velocity.y += 98.10f * deltaTime;
	if (num == 3) {
		row = 6;
	}
	else
		row = 0;
	if (num == 0) {
		faceRight = true;
	}
	else if (num == 2 || num == 3) {
		velocity.y = 0.f;
		faceRight = false;
	}
	else {
		if (body.getPosition().x > player.GetPosition().x) {
			faceRight = false;
		}
		else {
			faceRight = true;
		}
	}
	body.move(velocity * deltaTime);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Effect::Update2(float deltaTime, Enemy zombie)
{
	//row = 0;
	//velocity.x = 0.0f;
	//velocity.x += speed;
	//velocity.y += 981.0f * deltaTime;
	if (num == 3) {
		row = 6;
		velocity = zombie.velocity;
	}
	else
		row = 0;
	if (num == 2 || num == 3) {
		velocity.y = 0.f;
		faceRight = false;
	}
	
	body.move(velocity * deltaTime);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Effect::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Effect::OnCollision(sf::Vector2f direction)
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
