#include "TextBar.h"



TextBar::TextBar(int score, int heart, int armor, int goldCoin, int silverCoin, int bronzeCoin, int chest, int level, int playerNum)
{
	Bar.setSize(sf::Vector2f(960.0f, 45.0f));
	if (playerNum == 1)
	{
		Bar.setTexture(ResourceManager::GetInstance()->RequestTexture("Bar1"));
	}
	else if(playerNum == 2)
	{
		Bar.setTexture(ResourceManager::GetInstance()->RequestTexture("Bar2"));
	}
	font.loadFromFile("Font/Font0.ttf");
	
	for (int i = 0; i < 8; i++)
	{
		Text[i].setFont(font);
		Text[i].setCharacterSize(40);
		Text[i].setFillColor(sf::Color::White);
	}
	Text[7].setCharacterSize(30);

	ssScore << "Score : " << score;
	ssHeart << "" << heart;
	ssArmor << "" << armor;
	ssGold << "" << goldCoin;
	ssSiver << "" << silverCoin;
	ssBronze << "" << bronzeCoin;
	ssChest << "" << chest;
	if(level == 5)
		ssLevel << "LEVEL BONUS TIME ";
	else
		ssLevel << "LEVEL " << level;

	Text[0].setString(ssScore.str());
	Text[1].setString(ssHeart.str());
	Text[2].setString(ssArmor.str());
	Text[3].setString(ssChest.str());
	Text[4].setString(ssGold.str());
	Text[5].setString(ssSiver.str());
	Text[6].setString(ssBronze.str());
	Text[7].setString(ssLevel.str());
	
}


TextBar::~TextBar()
{
	//ResourceManager::GetInstance()->Cleanup();
}

void TextBar::Update(int score, int heart, int armor, int goldCoin, int silverCoin, int bronzeCoin, int chest, int level, sf::Vector2f position)
{
	ssScore.str("");
	ssScore << "Score : " << score;
	Text[0].setString(ssScore.str());

	ssHeart.str("");
	ssHeart << "" << heart;
	Text[1].setString(ssHeart.str());

	ssArmor.str("");
	ssArmor << "" << armor;
	Text[2].setString(ssArmor.str());

	ssChest.str("");
	ssChest << "" << chest;
	Text[3].setString(ssChest.str());

	ssGold.str("");
	ssGold << "" << goldCoin;
	Text[4].setString(ssGold.str());

	ssSiver.str("");
	ssSiver << "" << silverCoin;
	Text[5].setString(ssSiver.str());

	ssBronze.str("");
	ssBronze << "" << bronzeCoin;
	Text[6].setString(ssBronze.str());

	Bar.setPosition(position.x - 470.0f, position.y - 270.0f);
	Text[0].setPosition(position.x - 365.0f, position.y - 280.0f);
	Text[1].setPosition(position.x - 132.0f, position.y - 280.0f);
	Text[2].setPosition(position.x - 35.0f, position.y - 280.0f);
	Text[3].setPosition(position.x + 55.0f, position.y - 280.0f);
	Text[4].setPosition(position.x + 155.0f, position.y - 280.0f);
	Text[5].setPosition(position.x + 255.0f, position.y - 280.0f);
	Text[6].setPosition(position.x + 355.0f, position.y - 280.0f);
	Text[7].setPosition(position.x - 430.0f, position.y - 235.0f);
}

void TextBar::Draw(sf::RenderWindow & window)
{
	window.draw(Bar);
	for (int i = 0; i < 8; i++)
	{
		window.draw(Text[i]);
	}
}
