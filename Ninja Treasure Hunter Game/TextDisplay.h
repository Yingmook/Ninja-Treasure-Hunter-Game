#include <SFML/Graphics.hpp>

#pragma once
class TextDisplay
{
public:
	TextDisplay();
	~TextDisplay();

	void update();
	void Draw(sf::RenderWindow& window);

public:
	sf::Text text;
	int counter = 0;
	bool destroy = false;
	sf::Font font;
};


