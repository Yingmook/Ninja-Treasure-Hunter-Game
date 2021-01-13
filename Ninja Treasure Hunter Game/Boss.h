#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Player.h"
#include "Platform.h"

class Boss
{
public:
	Boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, int level);
	~Boss();

	void BossLevel1(Player player);
	void BossLevel2(Player player);
	void BossLevel3(Player player);
	void BossLevel4(Player player);
	void Update(float deltaTime, Player player);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::FloatRect getGlobalBounds() { return body.getGlobalBounds(); }

	void setPos(sf::Vector2f newPos)
	{
		body.setPosition(newPos);
	}
	void move(sf::Vector2f newPos)
	{
		body.move(newPos);
	}

	bool BulletIsCollisionWithPlayer(Player player);
	bool BulletIsCollisionWithPlatform(Platform platform);

public: std::vector<sf::RectangleShape> vbulletR, vbulletL;

private:
	sf::RectangleShape body;
	float speed;
	bool faceRight;
	unsigned int row;
	Animation animation;
	sf::Vector2f velocity;
	sf::Clock clock, clockConllision;

	sf::Texture weapon;
	sf::RectangleShape bullet[6];
	int level;
	//std::vector<sf::RectangleShape> vbulletR, vbulletL;
	float delaybullet;
	float deltaTimeBullet = 0.0f, deltaTimeCollision = 0.0f;

	sf::SoundBuffer buffer[5];
	sf::Sound action[5];
};

