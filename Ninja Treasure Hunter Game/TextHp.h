#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Boss.h"

class TextHp
{
public:
	TextHp();
	~TextHp();

	void updateZombie(Enemy zombie);
	void updateBoss(Boss boss);
	void Draw(sf::RenderWindow& window);


public:
	sf::Text text;
private:
	sf::Font font;
	sf::RectangleShape rect;
};
