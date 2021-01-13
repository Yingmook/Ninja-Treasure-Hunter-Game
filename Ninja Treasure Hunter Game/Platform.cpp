#include "Platform.h"



Platform::Platform(int num, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	//body.setTexture(texture);
	body.setPosition(position);

	switch (num)
	{
	case 1: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform1"));
		break;
	case 2: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2"));
		break;
	case 3: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3"));
		break;
	case 4: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4"));
		break;
	case 5: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform5"));
		break;
	case 6: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform6"));
		break;
	case 7: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform7"));
		break;
	case 8: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform8"));
		break;
	case 9: body.setTexture(ResourceManager::GetInstance()->RequestTexture("water"));
		break;
	case 10: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2_1"));
		break;
	case 11: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2_2"));
		break;
	case 12: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2_3"));
		break;
	case 13: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2_4"));
		break;
	case 14: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2_5"));
		break;
	case 15: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2_6"));
		break;
	case 16: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2_7"));
		break;
	case 17: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform2_8"));
		break;
	case 18: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3_1"));
		break;
	case 19: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3_2"));
		break;
	case 20: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3_3"));
		break;
	case 21: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3_4"));
		break;
	case 22: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3_5"));
		break;
	case 23: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3_6"));
		break;
	case 24: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3_7"));
		break;
	case 25: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform3_8"));
		break;
	case 26: body.setTexture(ResourceManager::GetInstance()->RequestTexture("crystal"));
		break;
	case 27: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4_1"));
		break;
	case 28: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4_2"));
		break;
	case 29: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4_3"));
		break;
	case 30: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4_4"));
		break;
	case 31: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4_5"));
		break;
	case 32: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4_6"));
		break;
	case 33: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4_7"));
		break;
	case 34: body.setTexture(ResourceManager::GetInstance()->RequestTexture("platform4_8"));
		break;
	default:
		break;
	}
}


Platform::~Platform()
{
}

void Platform::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}