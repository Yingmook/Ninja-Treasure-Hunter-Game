#include "TextHp.h"



TextHp::TextHp()
{
	font.loadFromFile("Font/Font0.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(0, 0);

	rect.setSize(sf::Vector2f(20.0f, 10.0f));
	rect.setOrigin(rect.getSize() / 2.0f);
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Red);
}


TextHp::~TextHp()
{
}

void TextHp::updateZombie(Enemy zombie)
{
	text.setPosition(zombie.GetPosition().x, zombie.GetPosition().y - 60.f);
	rect.setPosition(zombie.GetPosition().x + 8.f, zombie.GetPosition().y - 44.f);
}

void TextHp::updateBoss(Boss boss)
{
	text.setPosition(boss.GetPosition().x - 17.f, boss.GetPosition().y - 115.f);
	rect.setPosition(boss.GetPosition().x - 10.f, boss.GetPosition().y - 90.f);
	text.setCharacterSize(40);
	rect.setSize(sf::Vector2f(50.0f, 25.0f));
}

void TextHp::Draw(sf::RenderWindow & window)
{
	window.draw(rect);
	window.draw(text);
}
