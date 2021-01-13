#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class background
{
public:
	background(int num);
	~background();

	void Draw(sf::RenderWindow& window);

private:
	sf::RectangleShape BackGround[21];
	sf::Texture texture[5];
	
};

