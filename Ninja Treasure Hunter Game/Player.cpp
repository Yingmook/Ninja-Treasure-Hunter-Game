#include "Player.h"
#include <SFML/Audio.hpp>



Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, int bulletNum) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	
	//row = 0;
	faceRight = true;
	HP = 100.0f;
	heart = 3;
	
	body.setSize(sf::Vector2f(50.0f, 75.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(100.0f, 480.0f);
	body.setTexture(texture);
	body.setFillColor(sf::Color::White);

	if (bulletNum == 1) {
		kunai[0].loadFromFile("Texture/Player/Bullet4R.png");
		kunai[1].loadFromFile("Texture/Player/Bullet4L.png");
		SpeedBullet = 15.0f;
		bulletDistance = 300;
	}
	else if (bulletNum == 2) {
		kunai[0].loadFromFile("Texture/Player/Bullet7R.png");
		kunai[1].loadFromFile("Texture/Player/Bullet7L.png");
		SpeedBullet = 20.0f;
		bulletDistance = 400;
	}
	else if (bulletNum == 3) {
		kunai[0].loadFromFile("Texture/Player/Bullet3R.png");
		kunai[1].loadFromFile("Texture/Player/Bullet3L.png");
		SpeedBullet = 30.0f;
		bulletDistance = 500;
		bullet[0].setFillColor(sf::Color(0,255,255,255));
		bullet[1].setFillColor(sf::Color::Cyan);
	}
	else if (bulletNum == 4) {
		kunai[0].loadFromFile("Texture/Player/Bullet1R.png");
		kunai[1].loadFromFile("Texture/Player/Bullet1L.png");
		SpeedBullet = 40.0f;
		bulletDistance = 600;
	}
	bullet[0].setTexture(&kunai[0]);
	bullet[0].setSize(sf::Vector2f(50.0f, 20.0f));
	bullet[1].setTexture(&kunai[1]);
	bullet[1].setSize(sf::Vector2f(50.0f, 20.0f));
	delaybullet = 0.2f;

	font.loadFromFile("Font/Font0.ttf");
	Text.setFont(font);
	Text.setFillColor(sf::Color::White);
	Text.setCharacterSize(20);
	Text.setPosition(0, 0);
	Text.setString("HP");

	//buffer[0].loadFromFile("Sound/gravelwalk.ogg");
	buffer[0].loadFromFile("Sound/HOLOWPOP.ogg");
	buffer[1].loadFromFile("Sound/Arrow+Swoosh+1.ogg");
	buffer[2].loadFromFile("Sound/POP2.ogg");
	buffer[3].loadFromFile("Sound/SCREAM3.ogg");
	buffer[4].loadFromFile("Sound/Fireball-3.ogg");
	buffer[5].loadFromFile("Sound/FASTPOP.ogg");
	buffer[6].loadFromFile("Sound/HEAVBRK.ogg");

	action[0].setBuffer(buffer[0]);
	action[1].setBuffer(buffer[1]);
	action[2].setBuffer(buffer[2]);
	action[3].setBuffer(buffer[3]);
	action[4].setBuffer(buffer[4]);
	action[5].setBuffer(buffer[5]);
	action[6].setBuffer(buffer[6]);
	action[2].setVolume(60);
	action[3].setVolume(50);
	action[5].setVolume(60);
	//action[4].setVolume(70);
	action[6].setVolume(50);

}


Player::~Player()
{
}

void Player::UpdateBonusTime(float deltaTime)
{
	velocity.x = 0.0f;
	velocity.y += 1581.0f * deltaTime;
	row = 0;
	faceRight = true;
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	Text.setPosition(body.getPosition().x, body.getPosition().y - 60.f);
}

void Player::Update(float deltaTime)
{	
	velocity.x = 0.0f;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && body.getPosition().x >= 25)
	{
		velocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += speed;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))&& canJump)
	{
		action[2].play();
		canJump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		//square root ( 2.0 * gravity(=981.0f) * jumpHeight)
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		body.setSize(sf::Vector2f(55.0f, 75.0f));
		body.setOrigin(body.getSize() / 4.2f);
	}
	else
	{
		body.setSize(sf::Vector2f(50.0f, 75.0f));
		body.setOrigin(body.getSize() / 2.0f);
	}
	deltaTimeBullet += clock.restart().asSeconds();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (deltaTimeBullet >= delaybullet)
		{
			if (faceRight == true) {
				bullet[0].setPosition(body.getPosition().x - 25, body.getPosition().y);//setPosition(body.getGlobalBounds().left + body.getGlobalBounds().width, body.getGlobalBounds().top + body.getGlobalBounds().height / 2);
				vbulletR.push_back(bullet[0]);
				action[1].play();
			}
			else {
				bullet[1].setPosition(body.getPosition().x - 25, body.getPosition().y);
				vbulletL.push_back(bullet[1]);
				action[1].play();
			}
			deltaTimeBullet = 0;
		}
	}

	for (int i = 0; i < vbulletR.size(); i++)
	{
			vbulletR[i].move(SpeedBullet, 0.0f);
			if (vbulletR[i].getPosition().x - bullet[0].getPosition().x > bulletDistance)
				vbulletR.erase(vbulletR.begin() + i);
	}
	for (int i = 0; i < vbulletL.size(); i++)
	{
		vbulletL[i].move(-SpeedBullet, 0.0f);
		if (vbulletL[i].getPosition().x - bullet[1].getPosition().x < -bulletDistance)
			vbulletL.erase(vbulletL.begin() + i);
	}

	velocity.y += 1581.0f * deltaTime;
	if (canJump == false)
	{
		row = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			faceRight = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			faceRight = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			row = 4;
		}
		body.setSize(sf::Vector2f(50.0f, 75.0f));
		body.setOrigin(body.getSize() / 2.0f);
	}
	else if (velocity.x == 0.0f && deltaTimeBullet < 0.2f && ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		row = 3;
	}
	else if (velocity.x == 0.0f && deltaTimeBullet < 0.2f)
	{
		row = 4;
	}
	else if (velocity.x == 0.0f && (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		row = 3;
	}
	else if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else if (velocity.x > 0.0f || velocity.x < 0.0f)
	{
		if (velocity.x > 0.0f) {
			faceRight = true;
		}
		else
			faceRight = false;
		
		if ((velocity.x > 0.0f && deltaTimeBullet < 0.3f) || (velocity.x < 0.0f && deltaTimeBullet < 0.3f))
			row = 4;
		else if (velocity.x > 0.0f && ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))))
			row = 3;
		else if (velocity.x < 0.0f && ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))))
			row = 3;
		else
			row = 1;
	}


	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	Text.setPosition(body.getPosition().x, body.getPosition().y - 60.f);
}

void Player::Draw(sf::RenderWindow & window)
{
	window.draw(body);
	window.draw(Text);
	for (int i = 0; i < vbulletR.size(); i++)
		window.draw(vbulletR[i]);
	for (int i = 0; i < vbulletL.size(); i++)
		window.draw(vbulletL[i]);
}

void Player::OnCollision(sf::Vector2f direction)
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
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;
	}
}

bool Player::isCollisionWithZombie(Enemy zombie)
{
	if (body.getGlobalBounds().intersects(zombie.getGlobalBounds())) {
		if (abs(body.getPosition().x - zombie.GetPosition().x) < 30.0f)
		{
			action[3].play();
			return true;
		}
	}
	return false;
}

bool Player::BulletIsCollisionWithEnermy(Enemy zombie)
{	
	for (int i = 0; i < vbulletR.size(); i++)
		if (vbulletR[i].getGlobalBounds().intersects(zombie.getGlobalBounds()))
			if (abs(vbulletR[i].getPosition().x - zombie.GetPosition().x) < 60.0f)
			{
				vbulletR.erase(vbulletR.begin() + i);
				action[4].play();
				return true;
			}
	for (int i = 0; i < vbulletL.size(); i++)
		if (vbulletL[i].getGlobalBounds().intersects(zombie.getGlobalBounds()))
			if (abs(vbulletL[i].getPosition().x - zombie.GetPosition().x) < 60.0f)
			{
				vbulletL.erase(vbulletL.begin() + i);
				action[4].play();
				return true;
			}
	return false;
}

bool Player::BulletIsCollisionWithBox(Item box)
{
	for (int i = 0; i < vbulletR.size(); i++)
		if (vbulletR[i].getGlobalBounds().intersects(box.getGlobalBounds()))
		{
			action[0].play();
			action[6].play();
			vbulletR.erase(vbulletR.begin() + i);
			return true;
		}
	for (int i = 0; i < vbulletL.size(); i++)
		if (vbulletL[i].getGlobalBounds().intersects(box.getGlobalBounds()))
		{
			action[0].play();
			action[6].play();
			vbulletL.erase(vbulletL.begin() + i);
			return true;
		}
	return false;
}

