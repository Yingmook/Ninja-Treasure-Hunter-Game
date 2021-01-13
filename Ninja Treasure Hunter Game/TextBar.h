#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "ResourceManager.h"

class TextBar
{
public:
	TextBar(int score, int heart, int armor, int goldCoin, int silverCoin, int bronzeCoin, int chest, int level, int playerNum);
	~TextBar();

	void Update(int score, int heart, int armor, int goldCoin, int silverCoin, int bronzeCoin, int chest, int level, sf::Vector2f position);
	void Draw(sf::RenderWindow& window);

private:
	sf::Font font;
	//sf::Text textScore, textHeart, textArmor, textGold, textSilver, textBronze, textChest, textLevel;
	std::ostringstream ssScore, ssHeart, ssArmor, ssGold, ssSiver, ssBronze, ssChest, ssLevel;
	sf::Text Text[8];
	sf::RectangleShape Bar;
};

