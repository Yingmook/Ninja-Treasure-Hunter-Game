#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "ResourceManager.h"
#include "Animation.h"
#include "Collider.h"
#include "Clash.h"
#include "Item.h"
#include "Platform.h"
#include "Enemy.h"
#include "TextDisplay.h"
#include <SFML/Audio.hpp>


class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, int bulletNum);
	~Player();

	void UpdateBonusTime(float deltaTime);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	bool isCollisionWithZombie(Enemy zombie);
	bool BulletIsCollisionWithEnermy(Enemy zombie);
	bool BulletIsCollisionWithBox(Item box);
	std::vector<sf::RectangleShape> bulletR()
	{
		return vbulletR;
	}
	std::vector<sf::RectangleShape> bulletL()
	{
		return vbulletL;
	}

	bool BulletIsCollisionWithPlatform(Platform platform)
	{
		for (int i = 0; i < vbulletR.size(); i++)
			if (vbulletR[i].getGlobalBounds().intersects(platform.getGlobalBounds()))
			{
				vbulletR.erase(vbulletR.begin() + i);
				return true;
			}
		for (int i = 0; i < vbulletL.size(); i++)
			if (vbulletL[i].getGlobalBounds().intersects(platform.getGlobalBounds()))
			{
				vbulletL.erase(vbulletL.begin() + i);
				return true;
			}
		return false;
	}

	bool isCollisionWithItem(Item coin)
	{
		if (body.getGlobalBounds().intersects(coin.getGlobalBounds()))
		{
			action[5].play();
			return true;
		}
		return false;
	}
	

	void setPos(sf::Vector2f newPos)
	{
		body.setPosition(newPos);
	}
	void setFillColor(sf::Color color)
	{
		body.setFillColor(color);
	}
	void move(sf::Vector2f newPos)
	{
		body.move(newPos);
	}

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body);}
	Clash GetClash() { return Clash(body); }
	sf::FloatRect getGlobalBounds() { return body.getGlobalBounds(); }

public:
	sf::Text Text;
	std::vector<sf::RectangleShape> vbulletR, vbulletL;
	sf::RectangleShape body;
private:
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

	sf::Texture kunai[2];
	sf::RectangleShape bullet[2];
	float SpeedBullet;
	float delaybullet;
	sf::Clock clock, clockConllision;
	float deltaTimeBullet = 0.0f;
	float bulletDistance;
	float direction;

	int count;
	bool destroy = false;
	float HP;
	float deltaTimeCollision = 0.0f;
	int heart;

	sf::Font font;

	sf::SoundBuffer buffer[8];
	sf::Sound action[8];
};

