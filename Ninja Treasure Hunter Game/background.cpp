#include "background.h"



background::background(int num)
{
	switch (num)
	{
	case 1:
		for (int i = 0; i < 21; i++)
		{
			BackGround[i].setSize(sf::Vector2f(960.0f, 945.0f));
			BackGround[i].setTexture(ResourceManager::GetInstance()->RequestTexture("bg_1"));
			BackGround[0].setPosition(0.0f, -405.0f);
			BackGround[i + 1].setPosition(BackGround[i].getPosition().x + 959, -405.0f);
		}	break;
	case 2:
		for (int i = 0; i < 21; i++)
		{
			BackGround[i].setSize(sf::Vector2f(960.0f, 945.0f));
			BackGround[i].setTexture(ResourceManager::GetInstance()->RequestTexture("bg_2"));
			BackGround[0].setPosition(0.0f, -405.0f);
			BackGround[i + 1].setPosition(BackGround[i].getPosition().x + 959, -405.0f);
		}	break;
	case 3:
		for (int i = 0; i < 21; i++)
		{
			BackGround[i].setSize(sf::Vector2f(960.0f, 945.0f));
			BackGround[i].setTexture(ResourceManager::GetInstance()->RequestTexture("bg_3"));
			BackGround[0].setPosition(0.0f, -405.0f);
			BackGround[i + 1].setPosition(BackGround[i].getPosition().x + 959, -405.0f);
		}	break;
	case 4:
		for (int i = 0; i < 21; i++)
		{
			BackGround[i].setSize(sf::Vector2f(960.0f, 945.0f));
			BackGround[i].setTexture(ResourceManager::GetInstance()->RequestTexture("bg_4"));
			BackGround[0].setPosition(0.0f, -405.0f);
			BackGround[i + 1].setPosition(BackGround[i].getPosition().x + 959, -405.0f);
		}	break;
	case 5:
		for (int i = 0; i < 21; i++)
		{
			BackGround[i].setSize(sf::Vector2f(960.0f, 945.0f));
			BackGround[i].setTexture(ResourceManager::GetInstance()->RequestTexture("bg_5"));
			BackGround[0].setPosition(0.0f, -405.0f);
			BackGround[i + 1].setPosition(BackGround[i].getPosition().x + 959, -405.0f);
		}	break;
	}
}

background::~background()
{
	//ResourceManager::GetInstance()->Cleanup();
}

void background::Draw(sf::RenderWindow & window)
{	
	for (int i = 0; i < 21; i++)
		window.draw(BackGround[i]);
}
