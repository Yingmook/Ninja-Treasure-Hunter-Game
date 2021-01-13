#include "Boss.h"



Boss::Boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, int level) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->level = level;
	row = 1;
	faceRight = true;

	body.setSize(sf::Vector2f(250.0f, 300.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);

	weapon.loadFromFile("Texture/Zombie/sparkles.png");
	bullet[0].setTexture(&weapon);
	bullet[1].setTexture(&weapon);
	bullet[2].setTexture(&weapon);
	bullet[3].setTexture(&weapon);
	bullet[4].setTexture(&weapon);
	bullet[5].setTexture(&weapon);

	buffer[0].loadFromFile("Sound/QUICKPOP.ogg");
	action[0].setBuffer(buffer[0]);
	action[1].setBuffer(buffer[1]);
	action[0].setVolume(50);
}

Boss::~Boss()
{
}

void Boss::BossLevel1(Player player)
{
	delaybullet = 1.5;
	bullet[0].setFillColor(sf::Color::Yellow);
	bullet[1].setFillColor(sf::Color::Yellow);
	bullet[0].setSize(sf::Vector2f(100.0f, 100.0f));
	bullet[1].setSize(sf::Vector2f(100.0f, 100.0f));
	if (abs(body.getPosition().x - player.GetPosition().x) <= 500.0f)
	{
		if (body.getPosition().y - player.GetPosition().y < -100.0f) {
			if (deltaTimeBullet >= delaybullet)
			{
				if (faceRight == true) {
					action[0].play();
					bullet[0].setPosition({ body.getPosition().x, body.getPosition().y + 30 });
					vbulletR.push_back(bullet[0]);
				}
				else {
					action[0].play();
					bullet[1].setPosition({ body.getPosition().x, body.getPosition().y + 30 });
					vbulletL.push_back(bullet[1]);
				}
				deltaTimeBullet = 0;
			}
		}
		else if (body.getPosition().y - player.GetPosition().y < 35.0f)
		{
			//printf("<= 50.0f\n");
			if (deltaTimeBullet >= delaybullet)
			{
				if (faceRight == true) {
					action[0].play();
					bullet[0].setPosition({ body.getPosition().x, body.getPosition().y - 50 });
					vbulletR.push_back(bullet[0]);
				}
				else {
					action[0].play();
					bullet[1].setPosition({ body.getPosition().x, body.getPosition().y - 50 });
					vbulletL.push_back(bullet[1]);
				}
				deltaTimeBullet = 0;
			}
		}
		else if (body.getPosition().y - player.GetPosition().y < 199.0f)
		{
			//printf("<= -50.0f\n");
			if (deltaTimeBullet >= delaybullet)
			{
				if (faceRight == true) {
					action[0].play();
					bullet[0].setPosition({ body.getPosition().x, body.getPosition().y - 150 });
					vbulletR.push_back(bullet[0]);
				}
				else {
					action[0].play();
					bullet[1].setPosition({ body.getPosition().x, body.getPosition().y - 150 });
					vbulletL.push_back(bullet[1]);
				}
				deltaTimeBullet = 0;
			}
		}
	}

	for (int i = 0; i < vbulletR.size(); i++)
	{
		vbulletR[i].move(20, 0);
		if (vbulletR[i].getPosition().x - bullet[0].getPosition().x > 500)
			vbulletR.erase(vbulletR.begin() + i);
	}
	for (int i = 0; i < vbulletL.size(); i++)
	{
		vbulletL[i].move(-20, 0);
		if (vbulletL[i].getPosition().x - bullet[1].getPosition().x < -500)
			vbulletL.erase(vbulletL.begin() + i);
	}
}

void Boss::BossLevel2(Player player)
{
	delaybullet = 2;
	for (int i = 0; i < 4; i++) {
		bullet[i].setFillColor(sf::Color::Cyan);
		bullet[i].setSize(sf::Vector2f(150.0f, 150.0f));
	}

	if (abs(body.getPosition().x - player.GetPosition().x) <= 600.0f)
	{
		if (deltaTimeBullet >= delaybullet)
		{
			if (faceRight == true) {
				action[0].play();
				bullet[0].setPosition({ body.getPosition().x, body.getPosition().y + 30 });
				bullet[2].setPosition({ body.getPosition().x, body.getPosition().y - 250 });
				vbulletR.push_back(bullet[0]);
				vbulletR.push_back(bullet[2]);
			}
			else {
				action[0].play();
				bullet[1].setPosition({ body.getPosition().x, body.getPosition().y + 30 });
				bullet[3].setPosition({ body.getPosition().x, body.getPosition().y - 250 });
				vbulletL.push_back(bullet[1]);
				vbulletL.push_back(bullet[3]);
			}
			deltaTimeBullet = 0;
		}
	}

	for (int i = 0; i < vbulletR.size(); i++)
	{
		vbulletR[i].move(30, 0);
		if (vbulletR[i].getPosition().x - bullet[0].getPosition().x > 900)
			vbulletR.erase(vbulletR.begin() + i);
	}
	for (int i = 0; i < vbulletL.size(); i++)
	{
		vbulletL[i].move(-30, 0);
		if (vbulletL[i].getPosition().x - bullet[1].getPosition().x < -900)
			vbulletL.erase(vbulletL.begin() + i);
	}
}

void Boss::BossLevel3(Player player)
{
	delaybullet = 3;
	for (int i = 0; i < 4; i++) {
		bullet[i].setFillColor(sf::Color::Red);
		bullet[i].setSize(sf::Vector2f(100.0f, 100.0f));
	}
	if (abs(body.getPosition().x - player.GetPosition().x) <= 700.0f)
	{
			if (deltaTimeBullet >= delaybullet)
			{
				if (faceRight == true) {
					action[0].play();
					bullet[0].setPosition({ body.getPosition().x, body.getPosition().y  });
					bullet[2].setPosition({ body.getPosition().x, body.getPosition().y + 50 });
					vbulletR.push_back(bullet[0]);
					vbulletR.push_back(bullet[2]);
				}
				else {
					action[0].play();
					bullet[1].setPosition({ body.getPosition().x, body.getPosition().y  });
					bullet[3].setPosition({ body.getPosition().x, body.getPosition().y + 50 });
					vbulletL.push_back(bullet[1]);
					vbulletL.push_back(bullet[3]);
				}
				deltaTimeBullet = 0;
			}
		
		for (int i = 0; i < vbulletR.size(); i++)
		{
			vbulletR[i].move(30, 0);
			if (vbulletR[i].getPosition().x - bullet[0].getPosition().x > 900)
				vbulletR.erase(vbulletR.begin() + i);
		}
		for (int i = 0; i < vbulletL.size(); i++)
		{
			vbulletL[i].move(-30, 0);
			if (vbulletL[i].getPosition().x - bullet[1].getPosition().x < -900)
				vbulletL.erase(vbulletL.begin() + i);
		}
	}
}

void Boss::BossLevel4(Player player)
{
	delaybullet = 3;
	for (int i = 0; i < 6; i++) {
		bullet[i].setFillColor(sf::Color::Blue);
		bullet[i].setSize(sf::Vector2f(50.0f, 50.0f));
	}

	if (abs(body.getPosition().x - player.GetPosition().x) <= 800.0f)
	{
		if (body.getPosition().y - player.GetPosition().y < -50.0f) {
			if (deltaTimeBullet >= delaybullet)
			{
				if (faceRight == true) {
					action[0].play();
					bullet[0].setPosition({ body.getPosition().x, body.getPosition().y + 80 });
					bullet[2].setPosition({ body.getPosition().x, body.getPosition().y + 40 });
					bullet[4].setPosition({ body.getPosition().x, body.getPosition().y });
					vbulletR.push_back(bullet[0]);
					vbulletR.push_back(bullet[2]);
					vbulletR.push_back(bullet[4]);
				}
				else {
					action[0].play();
					bullet[1].setPosition({ body.getPosition().x, body.getPosition().y + 80 });
					bullet[3].setPosition({ body.getPosition().x, body.getPosition().y + 40 });
					bullet[5].setPosition({ body.getPosition().x, body.getPosition().y });
					vbulletL.push_back(bullet[1]);
					vbulletL.push_back(bullet[3]);
					vbulletL.push_back(bullet[5]);
				}
				deltaTimeBullet = 0;
			}
		}
		else if (body.getPosition().y - player.GetPosition().y < 200.0f) {
			if (deltaTimeBullet >= delaybullet)
			{
				if (faceRight == true) {
					action[0].play();
					bullet[0].setPosition({ body.getPosition().x, body.getPosition().y - 150} );
					bullet[2].setPosition({ body.getPosition().x, body.getPosition().y - 200 });
					bullet[4].setPosition({ body.getPosition().x, body.getPosition().y - 250 });
					vbulletR.push_back(bullet[0]);
					vbulletR.push_back(bullet[2]);
					vbulletR.push_back(bullet[4]);
				}
				else {
					action[0].play();
					bullet[1].setPosition({ body.getPosition().x, body.getPosition().y - 150 });
					bullet[3].setPosition({ body.getPosition().x, body.getPosition().y - 200 });
					bullet[5].setPosition({ body.getPosition().x, body.getPosition().y - 250 });
					vbulletL.push_back(bullet[1]);
					vbulletL.push_back(bullet[3]);
					vbulletL.push_back(bullet[5]);
				}
				deltaTimeBullet = 0;
			}
		}
	}

	for (int i = 0; i < vbulletR.size(); i++)
	{
		vbulletR[i].move(30, 0);
		if (vbulletR[i].getPosition().x - bullet[0].getPosition().x > 900)
			vbulletR.erase(vbulletR.begin() + i);
	}
	for (int i = 0; i < vbulletL.size(); i++)
	{
		vbulletL[i].move(-30, 0);
		if (vbulletL[i].getPosition().x - bullet[1].getPosition().x < -900)
			vbulletL.erase(vbulletL.begin() + i);
	}
}

void Boss::Update(float deltaTime, Player player)
{
	row = 1;
	velocity.x = 0.0f;
	velocity.x += speed;
	velocity.y += 981.0f * deltaTime;

	deltaTimeBullet += clock.restart().asSeconds();

	if(level == 1)
		BossLevel1(player);
	else if (level == 2)
		BossLevel2(player);
	else if (level == 3)
		BossLevel3(player);
	else
		BossLevel4(player);

	/*for (int i = 0; i < vbulletR.size(); i++)
	{
		vbulletR[i].move(abs(body.getPosition().x - player.GetPosition().x + 40) / 30, -abs(body.getPosition().y - player.GetPosition().y + 105) / 30);
		if (vbulletR[i].getPosition().x - bullet[0].getPosition().x > 500)
			vbulletR.erase(vbulletR.begin() + i);
	}
	for (int i = 0; i < vbulletL.size(); i++)
	{
		vbulletL[i].move(-abs(body.getPosition().x - player.GetPosition().x + 40) / 30, -abs(body.getPosition().y - player.GetPosition().y + 105) / 30);
		if (vbulletL[i].getPosition().x - bullet[1].getPosition().x < -500)
			vbulletL.erase(vbulletL.begin() + i);
	}*/
	if (body.getPosition().x - player.GetPosition().x >= 10) {
		faceRight = false;
		velocity.x *= -1;
	}
	else if (body.getPosition().x - player.GetPosition().x <= -10) {
		faceRight = true;
	}
	else
		velocity.x == 0;

	body.move(velocity * deltaTime);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Boss::Draw(sf::RenderWindow & window)
{
	window.draw(body);
	for (int i = 0; i < vbulletR.size(); i++)
		window.draw(vbulletR[i]);
	for (int i = 0; i < vbulletL.size(); i++)
		window.draw(vbulletL[i]);
}

void Boss::OnCollision(sf::Vector2f direction)
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


bool Boss::BulletIsCollisionWithPlayer(Player player)
{
	//deltaTimeCollision += clockConllision.restart().asSeconds();
	//if (deltaTimeCollision > 3.f) {
		//player.setFillColor(sf::Color(255, 255, 255, 255));
		for (int i = 0; i < vbulletR.size(); i++)
			if (vbulletR[i].getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				if (abs(vbulletR[i].getPosition().x - player.GetPosition().x) < 10.0f)
				{
					vbulletR.erase(vbulletR.begin() + i);
					//deltaTimeCollision = 0.0f;
					action[0].play();
					return true;
				}
			}
		for (int i = 0; i < vbulletL.size(); i++)
			if (vbulletL[i].getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				if (abs(vbulletL[i].getPosition().x - player.GetPosition().x) < 10.0f)
				{
					vbulletL.erase(vbulletL.begin() + i);
					//deltaTimeCollision = 0.0f;
					action[0].play();
					return true;
				}
			}
	//}
	/*else {
		if (deltaTimeCollision < 0.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (deltaTimeCollision < 0.5f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (deltaTimeCollision < 0.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (deltaTimeCollision < 1.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (deltaTimeCollision < 1.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (deltaTimeCollision < 1.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (deltaTimeCollision < 1.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (deltaTimeCollision < 2.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (deltaTimeCollision < 2.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (deltaTimeCollision < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (deltaTimeCollision < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else
			player.setFillColor(sf::Color(255, 255, 255, 250));
	}*/
	return false;
}

bool Boss::BulletIsCollisionWithPlatform(Platform platform)
{
	for (int i = 0; i < vbulletR.size(); i++)
		if (vbulletR[i].getGlobalBounds().intersects(platform.getGlobalBounds()))
		{
			if (abs(vbulletR[i].getPosition().x - platform.GetPosition().x) < 5.0f)
			{
				vbulletR.erase(vbulletR.begin() + i);
				return true;
			}
		}
	for (int i = 0; i < vbulletL.size(); i++)
		if (vbulletL[i].getGlobalBounds().intersects(platform.getGlobalBounds()))
		{
			if (abs(vbulletL[i].getPosition().x - platform.GetPosition().x) < 5.0f)
			{
				vbulletL.erase(vbulletL.begin() + i);
				return true;
			}
		}
	return false;
}
