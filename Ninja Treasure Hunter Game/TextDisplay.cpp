#include "TextDisplay.h"



TextDisplay::TextDisplay()
{
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(40);
	text.setPosition(0, 0);
	font.loadFromFile("Font/Font0.ttf");
	text.setFont(font);
}


TextDisplay::~TextDisplay()
{
}

void TextDisplay::update()
{
	text.move(0, -3);
	counter++;
	if (counter >= 50)
	{
		destroy = true;
	}
}

void TextDisplay::Draw(sf::RenderWindow & window)
{
	window.draw(text);
}
