#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "ResourceManager.h"
#include "Player.h"
#include "Platform.h"
#include "background.h"
#include "Item.h"
#include <sstream>
#include "Enemy.h"
#include "Effect.h"
#include "Clash.h"
#include "TextHp.h"
#include "TextDisplay.h"
#include "Boss.h"
#include "Textbar.h"
#include "Opject.h"

using namespace std;
static const float VIEW_WIDTH = 960.0f;
static const float VIEW_HEIGHT = 540.0f;
int score = 0, heart = 3, armor = 0, playerNum = 1;
vector<pair<int, string>> scoreboard;
string name = "";
sf::Texture playerTexture, playerOverGame;
//std::vector<std::pair<int, std::string>> scoreboard;

void WriteScore();
void ReadScore();
void Myname(sf::RenderWindow& window, sf::Vector2f position);
void platform_water(sf::RenderWindow& window, int num);
void EnterName(sf::RenderWindow& window);
void Scoreboard(sf::RenderWindow& window);
void HowToPlay(sf::RenderWindow& window);
void ChoosePlayer(sf::RenderWindow& window);
void Game(sf::RenderWindow& window);
void GameLevel_2(sf::RenderWindow& window);
void GameLevel_3(sf::RenderWindow& window);
void GameLevel_4(sf::RenderWindow& window);
void GameBonus(sf::RenderWindow& window);
void Menu(sf::RenderWindow& window);
int CheckShootBoss(Player player, Boss boss);
void GameOver(sf::RenderWindow& window, int level);
void LevelUp(sf::RenderWindow& window, int level);

void ResizeVeiw(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(960, 540), "Ninja Treasure Hunter Game", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);

	ofstream myFile;
	myFile.open("Myscore.txt", ios::out);
	myFile << "\n" << "unknow" << " " << "0";
	myFile << "\n" << "unknow" << " " << "0";
	myFile << "\n" << "unknow" << " " << "0";
	myFile << "\n" << "unknow" << " " << "0";
	myFile << "\n" << "unknow" << " " << "0";
	myFile.close();

	playerTexture.loadFromFile("Texture/Player/Player2.png");
	playerOverGame.loadFromFile("Texture/Player/PlayerDie1.png");
	sf::Image icon;
	icon.loadFromFile("Texture/item/icon.png");
	window.setIcon(300, 300, icon.getPixelsPtr());

	sf::Music music;
	music.openFromFile("Sound/Lost-Jungle.ogg");
	music.setLoop(true);
	while (window.isOpen())
	{
		music.play();
		Menu(window);	
	}
	return 0;
}

void WriteScore()
{
	ofstream myFile;
	myFile.open("Myscore.txt", ios::out | ios::app);
	myFile << "\n" << name << " " << score;
	//scoreboard.push_back({ score,name });
	myFile.close();
}

void ReadScore()
{
	scoreboard.clear();
	ifstream loadFile;
	loadFile.open("Myscore.txt");
	while (!loadFile.eof()) {
		string tempName;
		int tempScore;
		loadFile >> tempName >> tempScore;
		cout << ">> \"" << tempName << "\" " << tempScore << endl;
		scoreboard.push_back({ tempScore,tempName });
	}
	sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());
}

void Myname(sf::RenderWindow& window, sf::Vector2f position)
{
	sf::Text myname;
	sf::Font font;
	font.loadFromFile("Font/Font0.ttf");
	myname.setCharacterSize(35);
	myname.setOutlineThickness(3);
	myname.setOutlineColor(sf::Color::Black);
	myname.setFont(font);
	myname.setString("RAWITSARA NUPENG 61010888");
	myname.setOrigin(myname.getLocalBounds().width / 2, myname.getLocalBounds().height / 2);
	myname.setPosition(position);
	window.draw(myname);
}

void platform_water(sf::RenderWindow& window, int num)
{
	std::vector<Platform> platforms;
	//platforms.push_back(Platform(num, sf::Vector2f(640.0f, 64.0f), sf::Vector2f(18860.0f, 520.0f)));
	//platforms.push_back(Platform(9, sf::Vector2f(640.0f, 64.0f), sf::Vector2f(10800.0f, 520.0f)));
	float px = 0.0f;
	for (int i = 0; i < 31; i++)
	{
		platforms.push_back(Platform(num, sf::Vector2f(640.0f, 64.0f), sf::Vector2f(320.0f + px, 520.0f)));
		px += 640.0f;
	}
	for (Platform& platform : platforms)
		platform.Draw(window);
}

void EnterName(sf::RenderWindow & window)
{
	sf::SoundBuffer buffer, buffer2;
	sf::Sound sound, sound2;
	buffer.loadFromFile("Sound/cackle3.ogg");
	buffer2.loadFromFile("Sound/POP7.ogg");
	sound.setBuffer(buffer);
	sound2.setBuffer(buffer2);

	sf::RectangleShape EnterNameBg, Mode[2];
	EnterNameBg.setSize(sf::Vector2f(960.0f, 540.0f));
	for (int i = 0; i<2; i++)
		Mode[i].setSize(sf::Vector2f(960.0f, 540.0f));
	EnterNameBg.setTexture(ResourceManager::GetInstance()->RequestTexture("EnterNameBg"));
	Mode[0].setTexture(ResourceManager::GetInstance()->RequestTexture("EnterName0"));
	Mode[1].setTexture(ResourceManager::GetInstance()->RequestTexture("EnterName1"));
	sf::Vector2i mouse;
	int mode = 0;

	sf::String yourName;
	sf::Text player;
	sf::Font font;
	font.loadFromFile("Font/KRR_AengAei.ttf");

	name = "";
	while (mode == 0)
	{
		mouse = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape)
				Menu(window);
			if (event.type == sf::Event::TextEntered)
			{
				if ((event.text.unicode == '\b') && (yourName.getSize() > 0))
				{
					yourName.erase(yourName.getSize() - 1, 1);
					name.erase(name.size()-1, 1);
					player.setFont(font);
					player.setString(yourName);
				}
				else
				{
					if ((event.text.unicode < 128) && (yourName.getSize() < 10) && (event.text.unicode != '\r'))
					{
						yourName += static_cast<char>(event.text.unicode);
						name += static_cast<char>(event.text.unicode);
						if (event.text.unicode == '\b') {
							yourName.erase(yourName.getSize() - 1, 1);
							name.erase(name.size() - 1, 1);
						}
						player.setFont(font);
						player.setString(yourName);
					}
					else if ((event.text.unicode < 128) && (yourName.getSize() >= 10))
					{
						yourName.erase(yourName.getSize() - 1, 1);
						name.erase(name.size() - 1, 1);
					}						
				}
				player.setCharacterSize(60);
				player.setPosition(480.0f, 290.0f);
				player.setOrigin({ player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2 });
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					if (name == "") {
						printf("enter your name");
						sound2.play();
					}
					else {
						sound.play();
						player.setString(yourName);
						Game(window);
					}
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mouse.x > window.getSize().x / 2.15f && mouse.x < window.getSize().x / 1.87f && mouse.y > window.getSize().y / 1.45f && mouse.y < window.getSize().y / 1.23f)
					{
						if (name == "") {
							sound2.play();
							printf("enter your name");
						}
						else {
							mode = 1;
							sound.play();
						}
					}
				}
		}
		window.clear();
		window.draw(EnterNameBg);
		window.draw(player);
		if (mouse.x > window.getSize().x / 2.15f && mouse.x < window.getSize().x / 1.87f && mouse.y > window.getSize().y / 1.45f && mouse.y < window.getSize().y / 1.23f)
			window.draw(Mode[1]);
		else
			window.draw(Mode[0]);

		Myname(window, sf::Vector2f(480, 490));
		window.display();
		if (mode == 1)
			Game(window);
	}
}

void Scoreboard(sf::RenderWindow & window)
{
	ReadScore();
	sf::SoundBuffer buffer;
	sf::Sound sound;
	buffer.loadFromFile("Sound/POP7.ogg");
	sound.setBuffer(buffer);

	int count = 0;
	sf::Font font;
	font.loadFromFile("Font/Font0.ttf");
	sf::Text a[6], b[6];
	sf::RectangleShape ScoreboardBg, Mode[2];
	ScoreboardBg.setSize(sf::Vector2f(960.0f, 540.0f));
	for (int i = 0; i<2; i++)
		Mode[i].setSize(sf::Vector2f(960.0f, 540.0f));
	ScoreboardBg.setTexture(ResourceManager::GetInstance()->RequestTexture("ScoreboardBg"));
	Mode[0].setTexture(ResourceManager::GetInstance()->RequestTexture("Exit0"));
	Mode[1].setTexture(ResourceManager::GetInstance()->RequestTexture("Exit1"));
	sf::Vector2i mouse;
	int mode = 0;

	while (window.isOpen())
	{
		while (mode == 0)
		{
			mouse = sf::Mouse::getPosition(window);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (mouse.x > window.getSize().x / 1.11f && mouse.x < window.getSize().x / 1.04f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f)
						{
							mode = 1;
							sound.play();
						}
					}
				}
			}
			window.draw(ScoreboardBg);
			if (mouse.x > window.getSize().x / 1.11f && mouse.x < window.getSize().x / 1.04f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f)
			{
				window.draw(Mode[1]);
			}
			else
				window.draw(Mode[0]);

			for (vector<pair<int, string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i) {
				++count;
				if (count > 5) break;

				a[count].setString(std::to_string(i->first));
				a[count].setFont(font);
				a[count].setCharacterSize(60);
				a[count].setPosition(570, 70 + (60 * count));
				a[count].setFillColor(sf::Color::White);
				a[count].setStyle(sf::Text::Bold);
				a[count].setOutlineThickness(3);
				a[count].setOutlineColor(sf::Color::Black);
				//window.draw(a[count]);

				b[count].setString(i->second);
				b[count].setFont(font);
				b[count].setCharacterSize(60);
				b[count].setPosition(300, 70 + (60 * count));
				b[count].setFillColor(sf::Color::White);
				b[count].setStyle(sf::Text::Bold);
				b[count].setOutlineThickness(3);
				b[count].setOutlineColor(sf::Color::Black);
				//window.draw(b[count]);
			}
			Myname(window, sf::Vector2f(480, 490));
			for (int i = 1; i <= 5; i++)
			{
				window.draw(a[i]);
				window.draw(b[i]);
			}
			window.display();
			window.clear();

			if (mode == 1)
			{
				Menu(window);
			}
		}
	}
}

void HowToPlay(sf::RenderWindow & window)
{
	sf::SoundBuffer buffer;
	sf::Sound sound;
	buffer.loadFromFile("Sound/POP7.ogg");
	sound.setBuffer(buffer);

	bool nextPage = false, previousPage = true;
	sf::RectangleShape HowToPlayBg, Mode[6];
	HowToPlayBg.setSize(sf::Vector2f(960.0f, 540.0f));
	for (int i = 0; i<6; i++)
		Mode[i].setSize(sf::Vector2f(960.0f, 540.0f));
	HowToPlayBg.setTexture(ResourceManager::GetInstance()->RequestTexture("HowToPlayBg"));
	Mode[0].setTexture(ResourceManager::GetInstance()->RequestTexture("Exit0"));
	Mode[1].setTexture(ResourceManager::GetInstance()->RequestTexture("Exit1"));
	Mode[2].setTexture(ResourceManager::GetInstance()->RequestTexture("How_to_play01"));
	Mode[3].setTexture(ResourceManager::GetInstance()->RequestTexture("How_to_play11"));
	Mode[4].setTexture(ResourceManager::GetInstance()->RequestTexture("How_to_play02"));
	Mode[5].setTexture(ResourceManager::GetInstance()->RequestTexture("How_to_play12"));

	sf::Vector2i mouse;
	int mode = 0;

	while (mode == 0)
	{
		mouse = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//ResizeVeiw(window, view);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mouse.x > window.getSize().x / 1.11f && mouse.x < window.getSize().x / 1.04f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f)
					{
						mode = 1;
						sound.play();
					}
					else if ((mouse.x > window.getSize().x / 1.27f && mouse.x < window.getSize().x / 1.17f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f) && (nextPage == false))
					{
						previousPage = false;
						nextPage = true;
						sound.play();
					}
					else if ((mouse.x > window.getSize().x / 1.27f && mouse.x < window.getSize().x / 1.17f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f) && (nextPage == true))
					{
						nextPage = false;
						previousPage = true;
						sound.play();
					}
				}
			}
		}
		window.clear();
		window.draw(HowToPlayBg);
		if (previousPage == true)
		{
			if (mouse.x > window.getSize().x / 1.11f && mouse.x < window.getSize().x / 1.04f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f)
			{
				window.draw(Mode[1]);
				window.draw(Mode[2]);
			}
			else if (mouse.x > window.getSize().x / 1.27f && mouse.x < window.getSize().x / 1.17f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f)
			{
				window.draw(Mode[0]);
				window.draw(Mode[3]);
			}
			else
			{
				window.draw(Mode[0]);
				window.draw(Mode[2]);
			}
		}
		else if (nextPage == true)
		{
			if (mouse.x > window.getSize().x / 1.11f && mouse.x < window.getSize().x / 1.04f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f)
			{
				window.draw(Mode[1]);
				window.draw(Mode[4]);
			}
			else if (mouse.x > window.getSize().x / 1.27f && mouse.x < window.getSize().x / 1.17f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f)
			{
				window.draw(Mode[5]);
				window.draw(Mode[0]);
			}
			else
			{
				window.draw(Mode[4]);
				window.draw(Mode[0]);
			}
		}
		
		//printf("mode = %d \n", mode);
		//window.setView(window.getDefaultView());
		Myname(window, sf::Vector2f(480, 490));
		window.display();
		if (mode == 1)
		{
			Menu(window);
		}
	}
}

void ChoosePlayer(sf::RenderWindow & window)
{
	sf::SoundBuffer buffer;
	sf::Sound sound;
	buffer.loadFromFile("Sound/POP7.ogg");
	sound.setBuffer(buffer);

	sf::RectangleShape ChoosePlayerBg, Mode[3];
	ChoosePlayerBg.setSize(sf::Vector2f(960.0f, 540.0f));
	for (int i = 0; i<3; i++)
		Mode[i].setSize(sf::Vector2f(960.0f, 540.0f));
	ChoosePlayerBg.setTexture(ResourceManager::GetInstance()->RequestTexture("menuBg"));
	Mode[0].setTexture(ResourceManager::GetInstance()->RequestTexture("ChoosePlayer0"));
	Mode[1].setTexture(ResourceManager::GetInstance()->RequestTexture("ChoosePlayer1"));
	Mode[2].setTexture(ResourceManager::GetInstance()->RequestTexture("ChoosePlayer2"));
	sf::Vector2i mouse;
	int mode = 0;

	while (mode == 0)
	{
		mouse = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape)
				Menu(window);
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//ResizeVeiw(window, view);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mouse.x > window.getSize().x / 2.87f && mouse.x < window.getSize().x / 2.24f && mouse.y > window.getSize().y / 1.6f && mouse.y < window.getSize().y / 1.41f)
					{
						mode = 1;
						sound.play();
					}
					else if (mouse.x > window.getSize().x / 1.82f && mouse.x < window.getSize().x / 0.87f && mouse.y > window.getSize().y / 1.6f && mouse.y < window.getSize().y / 1.41f)
					{
						mode = 2;
						sound.play();
					}
				}
			}
		}
		window.clear();
		window.draw(ChoosePlayerBg);
		if (mouse.x > window.getSize().x / 2.87f && mouse.x < window.getSize().x / 2.24f && mouse.y > window.getSize().y / 1.6f && mouse.y < window.getSize().y / 1.41f)
		{
			window.draw(Mode[1]);
		}
		else if (mouse.x > window.getSize().x / 1.82f && mouse.x < window.getSize().x / 0.87f && mouse.y > window.getSize().y / 1.6f && mouse.y < window.getSize().y / 1.41f)
		{
			window.draw(Mode[2]);
		}
		else
			window.draw(Mode[0]);
		//printf("mode = %d \n", mode);
		//window.setView(window.getDefaultView());
		Myname(window, sf::Vector2f(480, 490));
		window.display();
		if (mode == 1)
		{
			playerTexture.loadFromFile("Texture/Player/Player2.png");
			playerOverGame.loadFromFile("Texture/Player/PlayerDie1.png");
			playerNum = 1;
			EnterName(window);
		}
		else if (mode == 2)
		{
			playerTexture.loadFromFile("Texture/Player/Player3.png");
			playerOverGame.loadFromFile("Texture/Player/PlayerDie2.png");
			playerNum = 2;
			EnterName(window);
		}
	}
}

void Game(sf::RenderWindow & window)
{
	sf::View gameView;
	gameView.reset(sf::FloatRect(0.0f, 0.0f, VIEW_WIDTH, VIEW_HEIGHT));

	sf::Vector2f position(VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
	background bg(1);

	/************************SET SOUND EFFECT*************************/

	sf::SoundBuffer buffer[6];
	sf::Sound sound[5];
	buffer[0].loadFromFile("Sound/SCREAM3.ogg");
	buffer[1].loadFromFile("Sound/Fireball-3.ogg"); 
	buffer[2].loadFromFile("Sound/FASTPOP.ogg");
	buffer[3].loadFromFile("Sound/Monster.ogg");
	buffer[4].loadFromFile("Sound/HOLOWPOP.ogg");
	sound[0].setBuffer(buffer[0]);
	sound[1].setBuffer(buffer[1]);
	sound[2].setBuffer(buffer[2]);
	sound[3].setBuffer(buffer[3]);
	sound[4].setBuffer(buffer[4]);
	sound[0].setVolume(50);
	sound[2].setVolume(20);
	sound[2].setVolume(50);
	sound[3].setVolume(40);
	sound[4].setVolume(50);

	/***********************player / Enemy*****************************/
	Player player(&playerTexture, sf::Vector2u(10, 5), 0.1f, 300.0f, 300.0f, 1);
	std::vector<Enemy> zombieVec;
	
	/****************************BOSS********************************/
	Boss boss(ResourceManager::GetInstance()->RequestTexture("boss1"), sf::Vector2u(6, 4), 0.1f, 150.0f, sf::Vector2f(20000.0f, 0.0f), 1);
	Item bigChest(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, sf::Vector2f(120.0f, 80.0f), sf::Vector2f(20000.0f, rand() % 500));

	/**********************Effect***********************/
	Effect playerDie(&playerOverGame, sf::Vector2u(10, 1), 0.4f, 0);
	Effect zombieDie(ResourceManager::GetInstance()->RequestTexture("zombie1_die"), sf::Vector2u(8, 1), 0.15f, 1);
	Effect bossDie(ResourceManager::GetInstance()->RequestTexture("boss1_die"), sf::Vector2u(8, 1), 0.3f, 4);
	Effect Boom(ResourceManager::GetInstance()->RequestTexture("boom"), sf::Vector2u(8, 8), 0.1f, 3);
	Effect ChestOpen(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, 2);

	/******************************coin*******************************************/
	std::vector<Item> coinGoldVec , coinSilverVec, coinBronzeVec;
	int randCoin[150];
	for (int i = 0; i < 150; i++)
	{
		randCoin[i] = (rand() % 410) * 40 +250;
		for (int j = i - 1; j >= 0; j--)
			while (randCoin[i] == randCoin[j]) {
				randCoin[i] = (rand() % 410) * 40 + 250;
				j = i - 1;
			}
	}
	for (int i = 0; i < 50; i++)
	{
		coinGoldVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinGold"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i], rand() % 400)));
		coinSilverVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinSilver"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i+50], rand() % 400)));
		coinBronzeVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinBronze"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i+100], rand() % 400)));
	}	
	
	/******************************TEASURE CHEST******************************************/
	std::vector<Item> ChestVec;
	int randChest[10];
	for (int i = 0; i < 10; i++)
	{
		randChest[i] = (rand() % 250) * 70 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randChest[i] == randChest[j]) {
				randChest[i] = (rand() % 250) * 70 + 250;
				j = i - 1;
			}
		ChestVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("chestClosed"), sf::Vector2u(1, 1), 0.6f, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(randChest[i], rand()%400)));
	}

	/********************************ITEM HEART / ARMOR*******************************************/
	std::vector<Item> HeartVec;
	for (int i = 0; i < 1; i++)
		HeartVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("heart"), sf::Vector2u(1, 1), 0.1f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(((rand() % 800) * 20) + 2000, rand() % 540)));

	std::vector<Item> ArmorVec;
	for (int i = 0; i < 1; i++)
		ArmorVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("armor"), sf::Vector2u(1, 1), 0.1f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(((rand() % 800) * 20) + 2000, rand() % 540)));
	
	/***********************************OPJECT*******************************************************/
	std::vector<Item> Boxs;
	for (int i = 0; i < 50; i++) {
		Boxs.push_back(Item(ResourceManager::GetInstance()->RequestTexture("crate"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 300, rand() % 540)));
	}
	std::vector<Opject> OpjectVec;
	for (int i = 0; i < 30; i++) {
		OpjectVec.push_back(Opject(3, sf::Vector2f(60.0f, 60.0f), sf::Vector2f(((rand() % 300) * 60) + 200, rand() % 540)));
		OpjectVec.push_back(Opject(4, sf::Vector2f(40.0f, 60.0f), sf::Vector2f(((rand() % 420) * 40) + 200, rand() % 540)));
		//OpjectVec.push_back(Opject(5, sf::Vector2f(80.0f, 100.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
		//OpjectVec.push_back(Opject(6, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
	}
	std::vector<Item> StoneVec;
	for (int i = 0; i < 50; i++) {
		StoneVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("stone_pink"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(30000, 30000)));
		//TombStone.push_back(Opject(4, sf::Vector2f(40.0f, 60.0f), sf::Vector2f(30000, 30000)));
	}
	/******************************platform Level 1******************************************/
	std::vector<Platform> platforms;

	float px = 0.0f, count = 0.0f;
	for (int i = 0; i < 29; i++)
	{
		platforms.push_back(Platform(1, sf::Vector2f(640.0f, 64.0f), sf::Vector2f(320.0f + px, 520.0f)));
		px += 640.0f;
	}
	for (int i = 0; i < 7; i++)
	{
		platforms.push_back(Platform(4, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(100.0f + count, 380.0f)));
		platforms.push_back(Platform(5, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(140.0f + count, 100.0f)));
		platforms.push_back(Platform(2, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(360.0f + count, 250.0f)));
		platforms.push_back(Platform(7, sf::Vector2f(420.0f, 38.5f), sf::Vector2f(700.0f + count, 380.0f)));
		platforms.push_back(Platform(2, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(600.0f + count, 100.0f)));
		platforms.push_back(Platform(4, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(850.0f + count, 230.0f)));
		platforms.push_back(Platform(8, sf::Vector2f(470.0f, 38.5f), sf::Vector2f(1250.0f + count, 95.0f)));
		platforms.push_back(Platform(3, sf::Vector2f(210.0f, 38.5f), sf::Vector2f(1450.0f + count, 360.0f)));
		platforms.push_back(Platform(6, sf::Vector2f(370.0f, 38.5f), sf::Vector2f(1800.0f + count, 230.0f)));			
		platforms.push_back(Platform(5, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2000.0f + count, 350.0f)));
		platforms.push_back(Platform(5, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2300.0f + count, 210.0f)));
		count += 2500;
	}
	
	/****************************************Random Zombie Position********************************************/
	float platformP[200]; 
	int ranP[50];
	for (int i = 0; i<platforms.size(); i++)
		platformP[i] = platforms[i].GetPosition().x - (platforms[i].GetSize().x / 2)+25.0f;

	int damageZombie = 10, zombieHp[50], bossHp = 300;
	for (int i = 0; i < 50; i++)
		zombieHp[i] = 30;
	TextHp textHp, textBossHp;
	std::vector<TextHp> textHpVec;
	
	for (int i = 0; i < 50; i++) {
		ranP[i] = rand() % 104+2;
		for(int j = i-1; j >= 0; j--)
			while (ranP[i] == ranP[j]) {
				ranP[i] = rand() % 104 + 2;
				j = i - 1;
			}
		zombieVec.push_back(Enemy(ResourceManager::GetInstance()->RequestTexture("zombie1"), sf::Vector2u(6, 4), 0.15f, 80.0f, sf::Vector2f(platformP[ranP[i]], platforms[ranP[i]].GetPosition().y-platforms[ranP[i]].GetSize().y)));
		textHp.text.setPosition(zombieVec[i].GetPosition().x, zombieVec[i].GetPosition().y - 60);
		textHp.text.setString(std::to_string(zombieHp[i]));
		textHpVec.push_back(textHp);
	}
	int zombieWalk[50];
	for (int i = 0; i < 50; i++)
		zombieWalk[i] = 0;
	
	/**********************************Textbar************************************/
	int goldCoin = 50, silverCoin = 50, bronzeCoin = 50, chest = 10, level = 1;
	TextBar textBar(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, playerNum);
	
	/************************TextDisplay*******************************************/	
	std::vector<TextDisplay> textArray, textBossVec;
	TextDisplay text_dm, text_boss;

	bool touchBigchest = false, p = false, bossDead = false, shootBoss = false, gameOver = false, playerDead = false;
	float timer = 0.0f, Chesttimer = 0.0f, BlinkTime = 0.0f, OverTime = 0.0f, BossDieTime = 0.0f;
	float deltaTime = 0.0f;
	sf::Clock clock, clockTimer, clockChest, clockPlayer, clockOver, clockBossDie;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.key.code == sf::Keyboard::Escape)
				GameOver(window, 1);
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//ResizeVeiw(window, view);
				break;
			}
		}
		
		/************position*************/
		if (player.GetPosition().x + 25 > VIEW_WIDTH / 2)
			position.x = player.GetPosition().x + 25;
		else
			position.x = VIEW_WIDTH / 2;
		if (player.GetPosition().y + 25 < VIEW_HEIGHT / 2)
			position.y = player.GetPosition().y + 25;
		else
			position.y = VIEW_HEIGHT / 2;
		gameView.setCenter(position);

		/******************Update player********************/
		if (heart > 0)
			player.Update(deltaTime);

		/**********************CLOCK************************/
		timer += clockTimer.restart().asSeconds();
		Chesttimer += clockChest.restart().asSeconds();
		BlinkTime += clockPlayer.restart().asSeconds();
		OverTime += clockOver.restart().asSeconds();
		BossDieTime += clockBossDie.restart().asSeconds();

		/************************CHECK / UPDATE ZOMBIE*********************************/
		if(heart > 0)
		for (int i = 0; i < zombieVec.size(); i++) {	
			if ((abs(player.GetPosition().y - zombieVec[i].GetPosition().y) <= 10.0f) && (abs(player.GetPosition().x - zombieVec[i].GetPosition().x) <= 120.0f)) {
				if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
					zombieWalk[i] = 5;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else {
					zombieWalk[i] = 4;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
			}
			else if ((abs(player.GetPosition().y - zombieVec[i].GetPosition().y) <= 10.0f) && (abs(player.GetPosition().x - zombieVec[i].GetPosition().x) <= 300.0f)) {
				if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
					zombieWalk[i] = 3;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}					
				else {
					zombieWalk[i] = 2;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
			}
			else {
				if (zombieVec[i].GetPosition().x > platforms[ranP[i]].GetPosition().x + platforms[ranP[i]].GetSize().x / 2.2f) {
					zombieWalk[i] = 0;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else if (zombieVec[i].GetPosition().x < platforms[ranP[i]].GetPosition().x - platforms[ranP[i]].GetSize().x / 2.2f) {
					zombieWalk[i] = 1;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
			}
			textHpVec[i].updateZombie(zombieVec[i]);

			/*************************Check player kill zombie********************************************/
			if (player.BulletIsCollisionWithEnermy(zombieVec[i]))
			{
				sound[4].play();
				timer = 0.0f;
				Boom.setPos(zombieVec[i].GetPosition());
				text_dm.text.setString(std::to_string(damageZombie));
				text_dm.text.setPosition(zombieVec[i].GetPosition().x, zombieVec[i].GetPosition().y - 30.f);
				textArray.push_back(text_dm);
				zombieHp[i] -= damageZombie;
				textHpVec[i].text.setString(std::to_string(zombieHp[i]));
				if (zombieHp[i] <= 0) {
					StoneVec[i].setPos(zombieVec[i].GetPosition());
					zombieDie.setPos(zombieVec[i].GetPosition());
					zombieVec[i].setPos({ 422234, 423432 });
				}

				if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
					zombieVec[i].move(sf::Vector2f(-10, 0));
				}
				else {
					zombieVec[i].move(sf::Vector2f(10, 0));
				}
			}
			/**************************player Collision With Zombie**********************************/
			if (BlinkTime > 3.f) {
				if (player.isCollisionWithZombie(zombieVec[i]))
				{
					sound[3].play();
					BlinkTime = 0.0f;
					if (player.GetPosition().x >= zombieVec[i].GetPosition().x)
						player.setPos({ player.GetPosition().x + 100.f, player.GetPosition().y });
					else
						player.setPos({ player.GetPosition().x - 100.f, player.GetPosition().y });
					if (armor > 0) {
						armor -= 1;
						text_dm.text.setString("ARMOR -1");
						text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
						textArray.push_back(text_dm);
					}
					else {
						heart -= 1;
						text_dm.text.setString("HEART -1");
						text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
						textArray.push_back(text_dm);
					}
				}
			}
		}
		else /*******************UPDATE zombie (Heart <= 0)**************************/
			for (int i = 0; i < zombieVec.size(); i++) {
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
				textHpVec[i].updateZombie(zombieVec[i]);
			}

		/**********************set condition***************************/
		player.Text.setString(std::to_string(heart));
		if (player.GetPosition().y > VIEW_HEIGHT) {
			BlinkTime = 0.0f;
			player.setPos({ player.GetPosition().x - 200, 500 });
			heart -= 1;
			text_dm.text.setString("HEART -1");
			text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
			textArray.push_back(text_dm);
			sound[0].play();
		}
		for (int i = 0; i < textArray.size(); i++)
			if (textArray[i].destroy)
				textArray.erase(textArray.begin());

		/***************Update Item************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			coinGoldVec[i].Update(deltaTime);
		for (int i = 0; i < coinSilverVec.size(); i++)
			coinSilverVec[i].Update(deltaTime);
		for (int i = 0; i < coinBronzeVec.size(); i++)
			coinBronzeVec[i].Update(deltaTime);
		for (int i = 0; i < ChestVec.size(); i++)
			ChestVec[i].Update(deltaTime);
		for (int i = 0; i < HeartVec.size(); i++)
			HeartVec[i].Update(deltaTime);
		for (int i = 0; i < ArmorVec.size(); i++)
			ArmorVec[i].Update(deltaTime);
		for (int i = 0; i < Boxs.size(); i++)
			Boxs[i].Update(deltaTime);

		/***************************DEBUG Random ITEM*******************************************/
		for (Item& coinGold : coinGoldVec) {
			while (coinGold.GetPosition().y > 540.0f && coinGold.GetPosition().x < 25000.0f)
				coinGold.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinSilver : coinSilverVec) {
			while (coinSilver.GetPosition().y > 540.0f && coinSilver.GetPosition().x < 25000.0f)
				coinSilver.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinBronze : coinBronzeVec) {
			while (coinBronze.GetPosition().y > 540.0f && coinBronze.GetPosition().x < 25000.0f)
				coinBronze.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& chest : ChestVec) {
			while (chest.GetPosition().y > 540.0f && chest.GetPosition().x < 25000.0f)
				chest.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& heart : HeartVec) {
			while (heart.GetPosition().y > 540.0f && heart.GetPosition().x < 25000.0f)
				heart.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& armor : ArmorVec) {
			while (armor.GetPosition().y > 540.0f && armor.GetPosition().x < 25000.0f)
				armor.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}

		/******************************Oncollision with Platform*********************************/
		sf::Vector2f direction;
		for (Platform& platform : platforms) {
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
			player.BulletIsCollisionWithPlatform(platform);
			if (platform.GetCollider().CheckCollision(playerDie.GetCollider(), direction, 1.0f))
				playerDie.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(zombieDie.GetCollider(), direction, 1.0f))
				zombieDie.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(bigChest.GetCollider(), direction, 1.0f))
				bigChest.OnCollision(direction);
			for (Enemy& zombie : zombieVec) {
				if (platform.GetCollider().CheckCollision(zombie.GetCollider(), direction, 1.0f))
					zombie.OnCollision(direction);
			}
			for (Item& coinGold : coinGoldVec) {
				if (platform.GetClash().CheckClash(coinGold.GetClash(), direction, 1.0f))
					coinGold.OnCollision(direction);
			}
			for (Item& coinSilver : coinSilverVec) {
				if (platform.GetClash().CheckClash(coinSilver.GetClash(), direction, 1.0f))
					coinSilver.OnCollision(direction);
			}
			for (Item& coinBronze : coinBronzeVec) {
				if (platform.GetClash().CheckClash(coinBronze.GetClash(), direction, 1.0f))
					coinBronze.OnCollision(direction);
			}
			for (Item& chest : ChestVec) {
				if (platform.GetClash().CheckClash(chest.GetClash(), direction, 1.0f))
					chest.OnCollision(direction);
			}
			for (Item& heart : HeartVec) {
				if (platform.GetClash().CheckClash(heart.GetClash(), direction, 1.0f))
					heart.OnCollision(direction);
			}
			for (Item& armor : ArmorVec) {
				if (platform.GetClash().CheckClash(armor.GetClash(), direction, 1.0f))
					armor.OnCollision(direction);
			}
			for (Item& opject : Boxs) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
			for (Opject& opject : OpjectVec) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
		}
		for (Item& box : Boxs) {
			if (player.BulletIsCollisionWithBox(box)) {
				box.setPos({ 42356, 45623 });
			}
			if (box.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
		}
		/***************************Boss onconllision with platform 0-29*******************************************************/
		for (int i = 0; i < 29; i++) {
			if (platforms[i].GetCollider().CheckCollision(boss.GetCollider(), direction, 1.0f))
				boss.OnCollision(direction);
			if (platforms[i].GetCollider().CheckCollision(bossDie.GetCollider(), direction, 1.0f))
				bossDie.OnCollision(direction);
		}

		/**************************item logic & score item****************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			if (player.isCollisionWithItem(coinGoldVec[i]))
			{
				coinGoldVec[i].setPos({ 422234, 423432 });
				score += 3;
				goldCoin -= 1;
			}
		for (int i = 0; i < coinSilverVec.size(); i++)
			if (player.isCollisionWithItem(coinSilverVec[i]))
			{
				coinSilverVec[i].setPos({ 422234, 423432 });
				score += 2;
				silverCoin -= 1;
			}
		for (int i = 0; i < coinBronzeVec.size(); i++)
			if (player.isCollisionWithItem(coinBronzeVec[i]))
			{
				coinBronzeVec[i].setPos({ 422234, 423432 });
				score++;
				bronzeCoin -= 1;
			}
		for (int i = 0; i < StoneVec.size(); i++)
			if (player.isCollisionWithItem(StoneVec[i]))
			{
				StoneVec[i].setPos({ 422234, 423432 });
				score+= 3;
			}
		for (Item& Chest : ChestVec)
			if (player.isCollisionWithItem(Chest))
			{
				Chesttimer = 0.f;
				ChestOpen.setPos(Chest.GetPosition());
				Chest.setPos({ 422234, 423432 });
				score += 5;
				chest -= 1;
			}
		if (Chesttimer > 2)
			ChestOpen.setPos({ 422234, 423432 });

		for (int i = 0; i < HeartVec.size(); i++)
			if (player.isCollisionWithItem(HeartVec[i]))
			{
				HeartVec[i].setPos({ 422234, 423432 });
				heart += 1;
			}
		for (int i = 0; i < ArmorVec.size(); i++)
			if (player.isCollisionWithItem(ArmorVec[i]))
			{
				ArmorVec[i].setPos({ 422234, 423432 });
				armor += 1;
			}

		/********************************Check BOSS / Big Chest********************************************/
		bigChest.Update(deltaTime);
		if (chest <= 0 && touchBigchest == false)
		{
			bigChest.setPos(sf::Vector2f(18000.0f, 450.0f));
			/*if (p == false) {
				player.setPos(sf::Vector2f(17500.0f, 450.0f));
				p = true;
			}*/
			if (player.isCollisionWithItem(bigChest)) {
				sound[2].play();
				score += 50;
				bigChest.setPos({ 422234, 423432 });
				boss.setPos(sf::Vector2f(18200.0f, 100.0f));
				touchBigchest = true;
			}
		}

		if (touchBigchest == true) {
			boss.Update(deltaTime, player);
		}

		if (bossHp <= 0 && bossDead == false) {
			BossDieTime = 0.0f;
			bossDie.setPos(boss.GetPosition());
			boss.setPos({ 42324, 43214 });
			bossDead = true;
			bossDie.Update(deltaTime, player);
		}

		else if (bossDead == true)
			bossDie.Update(deltaTime, player);

		/***************************Boss Attack player*******************************************/
		if (BlinkTime > 3.f) {
			if (boss.BulletIsCollisionWithPlayer(player))
			{ 
				sound[0].play();
				sound[1].play();
				BlinkTime = 0.0f;
				boss.BulletIsCollisionWithPlayer(player);
				heart -= 1;
				text_dm.text.setString("HEART -1");
				text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
				textArray.push_back(text_dm);
			}
			if (player.getGlobalBounds().intersects(boss.getGlobalBounds()))
			{
				BlinkTime = 0.0f;
				if (player.GetPosition().x < boss.GetPosition().x)
					player.move(sf::Vector2f(-200, 0));
				else
					player.move(sf::Vector2f(200, 0));

				heart -= 1;
				text_dm.text.setString("HEART -1");
				text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
				textArray.push_back(text_dm);
			}
		}

		/*************************Player Blink**************************************/
		if (BlinkTime< 0.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 0.5f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 0.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 1.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 1.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 1.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 1.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 2.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 2.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 3.0f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else
			player.setFillColor(sf::Color(255, 255, 255, 255));

		/*************************Check Player shoot boss****************************/
		if (CheckShootBoss(player, boss) == 1) {
			shootBoss = true;
			sound[1].play();
			sound[4].play();
			player.vbulletR.erase(player.vbulletR.begin());
		}
		else if (CheckShootBoss(player, boss) == 2) {
			shootBoss = true;
			sound[1].play();
			sound[4].play();
			player.vbulletL.erase(player.vbulletL.begin());
		}
		
		if (shootBoss == true)
		{
			text_boss.text.setString(std::to_string(damageZombie));
			text_boss.text.setPosition(boss.GetPosition().x, boss.GetPosition().y - 60.f);
			textBossVec.push_back(text_boss);
			bossHp -= damageZombie;
			printf("%i\n", bossHp);
			shootBoss = false;
		}
		for (TextDisplay& text : textBossVec)
			text.update();
		for (int i = 0; i < textBossVec.size(); i++)
			if (textBossVec[i].destroy)
				textBossVec.erase(textBossVec.begin());
		textBossHp.updateBoss(boss);
		textBossHp.text.setString(std::to_string(bossHp));
	
		/*****************************Show score***************************************/
		textBar.Update(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, position);
		
		/***********************Update Effect*****************************/
		ChestOpen.Update(deltaTime, player);
		playerDie.Update(deltaTime, player);
		zombieDie.Update(deltaTime, player);
		Boom.Update(deltaTime, player);
		for (Opject& opject : OpjectVec)
			opject.Update(deltaTime);
		if (timer > 1) {
			zombieDie.setPos({ 422234, 423432 });
			Boom.setPos({ 422234, 423432 });
		}
		for (TextDisplay& text : textArray) {
			text.update();
		}

		/*********************Heart <= 0 / Player dead******************/		
		if (heart <= 0 && playerDead == false) {
			OverTime = 0.0f;
			playerDie.setPos(player.GetPosition());
			gameOver = true;
			playerDead = true;
		}

		/************************************NEXT**************************/
		if(OverTime > 3 && gameOver == true)
			GameOver(window, 1);
		if (bossDead == true && BossDieTime > 3)
			LevelUp(window, 1);

		/***************************Window DRAW**********************************/
		bg.Draw(window);
		window.setView(gameView);
		platform_water(window, 9);

		for (Opject& opject : OpjectVec)
			opject.Draw(window);
		for (Item& box : Boxs)
			box.Draw(window);
		for (Item& chest : ChestVec)
			chest.Draw(window);
		for (Item& coin : coinGoldVec)
			coin.Draw(window);
		for (Item& coin : coinSilverVec)
			coin.Draw(window);
		for (Item& coin : coinBronzeVec)
			coin.Draw(window);
		for (Item& heart : HeartVec)
			heart.Draw(window);
		for (Item& armor : ArmorVec)
			armor.Draw(window);
		for (Item& stone : StoneVec)
			stone.Draw(window);
		for (Platform& platform : platforms)
			platform.Draw(window);
		for (Enemy& zombie : zombieVec)
			zombie.Draw(window);
		bigChest.Draw(window);
		boss.Draw(window);
		zombieDie.Draw(window);
		playerDie.Draw(window);
		textBossHp.Draw(window);
		if (heart > 0)
			player.Draw(window);
		for (TextDisplay& text : textArray)
			text.Draw(window);
		for (TextDisplay& text : textBossVec)
			text.Draw(window);
		ChestOpen.Draw(window);
		for (TextHp& textHp : textHpVec)
			textHp.Draw(window);
		bossDie.Draw(window);
		Boom.Draw(window);
		textBar.Draw(window);
		Myname(window, sf::Vector2f(position.x, position.y + 230));
		window.display();
		window.clear();
	}
}

void GameLevel_2(sf::RenderWindow & window)
{
	sf::View gameView;
	gameView.reset(sf::FloatRect(0.0f, 0.0f, VIEW_WIDTH, VIEW_HEIGHT));

	sf::Vector2f position(VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
	background bg(2);

	/************************SET SOUND EFFECT*************************/
	sf::SoundBuffer buffer[5];
	sf::Sound sound[5];
	buffer[0].loadFromFile("Sound/SCREAM3.ogg");
	buffer[1].loadFromFile("Sound/Fireball-3.ogg");
	buffer[2].loadFromFile("Sound/FASTPOP.ogg");
	buffer[3].loadFromFile("Sound/Monster.ogg");
	buffer[4].loadFromFile("Sound/HOLOWPOP.ogg");
	sound[0].setBuffer(buffer[0]);
	sound[1].setBuffer(buffer[1]);
	sound[2].setBuffer(buffer[2]);
	sound[3].setBuffer(buffer[3]);
	sound[4].setBuffer(buffer[4]);
	sound[0].setVolume(50);
	sound[0].setVolume(20);
	sound[2].setVolume(50);
	sound[3].setVolume(40);
	sound[4].setVolume(50);

	/***********************player / Zombie*****************************/
	Player player(&playerTexture, sf::Vector2u(10, 5), 0.09f, 315.0f, 300.0f, 2);
	std::vector<Enemy> zombieVec;

	/****************************BOSS********************************/
	Boss boss(ResourceManager::GetInstance()->RequestTexture("boss2"), sf::Vector2u(6, 4), 0.1f, 160.0f, sf::Vector2f(20000.0f, 0.0f), 2);
	Item bigChest(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, sf::Vector2f(120.0f, 80.0f), sf::Vector2f(20000.0f, rand() % 500));

	/**********************Effect Zombie***********************/
	Effect playerDie(&playerOverGame, sf::Vector2u(10, 1), 0.4f, 0);
	Effect zombieDie(ResourceManager::GetInstance()->RequestTexture("zombie2_die"), sf::Vector2u(8, 1), 0.15f, 1);
	Effect bossDie(ResourceManager::GetInstance()->RequestTexture("boss2_die"), sf::Vector2u(8, 1), 0.3f, 4);
	Effect Boom(ResourceManager::GetInstance()->RequestTexture("boom"), sf::Vector2u(8, 8), 0.1f, 3);
	Effect ChestOpen(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, 2);
	
	/******************************coin*******************************************/
	std::vector<Item> coinGoldVec, coinSilverVec, coinBronzeVec;
	int randCoin[180];
	for (int i = 0; i < 180; i++)
	{
		randCoin[i] = (rand() % 410) * 40 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randCoin[i] == randCoin[j]) {
				randCoin[i] = (rand() % 410) * 40 + 250;
				j = i - 1;
			}
	}
	for (int i = 0; i < 60; i++)
	{
		coinGoldVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinGold"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i], rand() % 400)));
		coinSilverVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinSilver"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i + 60], rand() % 400)));
		coinBronzeVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinBronze"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i + 120], rand() % 400)));
	}

	/******************************TEASURE CHEST******************************************/
	std::vector<Item> ChestVec;
	int randChest[15];
	for (int i = 0; i < 15; i++)
	{
		randChest[i] = (rand() % 250) * 70 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randChest[i] == randChest[j]) {
				randChest[i] = (rand() % 250) * 70 + 250;
				j = i - 1;
			}
		ChestVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("chestClosed"), sf::Vector2u(1, 1), 0.6f, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(randChest[i], rand() % 400)));
	}

	/********************************ITEM HEART / ARMOR*******************************************/
	std::vector<Item> HeartVec, ArmorVec;
	for (int i = 0; i < 2; i++)
		HeartVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("heart"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(((rand() % 800) * 20) + 2000, rand() % 540)));

	for (int i = 0; i < 2; i++)
		ArmorVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("armor"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(((rand() % 800) * 20) + 2000, rand() % 540)));

	/***********************************OPJECT*******************************************************/
	std::vector<Item> Boxs;
	for (int i = 0; i < 50; i++) {
		Boxs.push_back(Item(ResourceManager::GetInstance()->RequestTexture("crate"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
	}
	std::vector<Opject> OpjectVec;
	for (int i = 0; i < 30; i++) {
		OpjectVec.push_back(Opject(3, sf::Vector2f(60.0f, 60.0f), sf::Vector2f(((rand() % 300) * 60) + 200, rand() % 540)));
		OpjectVec.push_back(Opject(4, sf::Vector2f(40.0f, 60.0f), sf::Vector2f(((rand() % 420) * 40) + 200, rand() % 540)));
		//OpjectVec.push_back(Opject(5, sf::Vector2f(80.0f, 100.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
		//OpjectVec.push_back(Opject(6, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
	}
	std::vector<Item> StoneVec;
	for (int i = 0; i < 60; i++) {
		StoneVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("stone_yellow"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(30000, 30000)));
	}

	/******************************platform Level 2******************************************/
	std::vector<Platform> platforms;

	float px = 0.0f, count = 0.0f, hole = 0.0f;
	for (int i = 0; i < 29; i++)
	{
		platforms.push_back(Platform(10, sf::Vector2f(640.0f, 64.0f), sf::Vector2f(320.0f + px + hole, 520.0f)));
		px += 600.0f;
		if (i % 5 == 0)
			hole += 150.0f;
	}
	for (int i = 0; i < 7; i++)
	{
		platforms.push_back(Platform(13, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(100.0f + count, 250.0f)));
		platforms.push_back(Platform(14, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(300.0f + count, 90.0f)));
		platforms.push_back(Platform(11, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(360.0f + count, 390.0f)));
		platforms.push_back(Platform(16, sf::Vector2f(420.0f, 38.5f), sf::Vector2f(750.0f + count, 380.0f)));
		platforms.push_back(Platform(11, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(650.0f + count, 100.0f)));
		platforms.push_back(Platform(13, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(1000.0f + count, 230.0f)));
		platforms.push_back(Platform(17, sf::Vector2f(470.0f, 38.5f), sf::Vector2f(1250.0f + count, 80.0f)));
		platforms.push_back(Platform(12, sf::Vector2f(210.0f, 38.5f), sf::Vector2f(1450.0f + count, 360.0f)));
		platforms.push_back(Platform(15, sf::Vector2f(370.0f, 38.5f), sf::Vector2f(1800.0f + count, 200.0f)));
		platforms.push_back(Platform(14, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2000.0f + count, 350.0f)));
		platforms.push_back(Platform(14, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2300.0f + count, 210.0f)));
		count += 2550;
	}

	/****************************************Random Zombie Position********************************************/
	float platformP[200];
	for (int i = 0; i<platforms.size(); i++)
		platformP[i] = platforms[i].GetPosition().x - (platforms[i].GetSize().x / 2) + 25.0f;

	int ranP[60], damageZombie = 15, zombieHp[60], bossHp = 400;
	for (int i = 0; i < 60; i++)
		zombieHp[i] = 60;
	TextHp textHp, textBossHp;
	std::vector<TextHp> textHpVec;
 
	for (int i = 0; i < 60; i++) {
		ranP[i] = rand() % 104 + 2;
		for (int j = i - 1; j >= 0; j--)
			while (ranP[i] == ranP[j]) {
				ranP[i] = rand() % 104 + 2;
				j = i - 1;
			}
		zombieVec.push_back(Enemy(ResourceManager::GetInstance()->RequestTexture("zombie2"), sf::Vector2u(6, 4), 0.15f, 88.0f, sf::Vector2f(platformP[ranP[i]]+50.0f, platforms[ranP[i]].GetPosition().y - platforms[ranP[i]].GetSize().y)));
		textHp.text.setPosition(zombieVec[i].GetPosition().x, zombieVec[i].GetPosition().y - 60);
		textHp.text.setString(std::to_string(zombieHp[i]));
		textHpVec.push_back(textHp);
	}
	int zombieWalk[60];
	for (int i = 0; i < 60; i++)
		zombieWalk[i] = 0;

	/**********************************score coin************************************/
	int goldCoin = 60, silverCoin = 60, bronzeCoin = 60, chest = 15, level = 2;
	TextBar textBar(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, playerNum);

	/************************TextDisplay**************************/
	std::vector<TextDisplay> textArray, textBossVec;
	TextDisplay text_dm, text_boss;

	bool touchBigchest = false, p = false, bossDead = false, shootBoss = false, gameOver = false, playerDead = false;
	float timer = 0.0f, Chesttimer = 0.0f, BlinkTime = 0.0f, OverTime = 0.0f, BossDieTime = 0.0f;
	float deltaTime = 0.0f;
	sf::Clock clock, clockTimer, clockChest, clockPlayer, clockOver, clockBossDie;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.key.code == sf::Keyboard::Escape)
				GameOver(window, 2);
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				break;
			}
		}

		/************position view*************/
		if (player.GetPosition().x + 25 > VIEW_WIDTH / 2)
			position.x = player.GetPosition().x + 25;
		else
			position.x = VIEW_WIDTH / 2;
		if (player.GetPosition().y + 25 < VIEW_HEIGHT / 2)
			position.y = player.GetPosition().y + 25;
		else
			position.y = VIEW_HEIGHT / 2;
		gameView.setCenter(position);

		/******************Update player********************/
		if (heart > 0)
			player.Update(deltaTime);

		/**********************CLOCK************************/
		timer += clockTimer.restart().asSeconds();
		Chesttimer += clockChest.restart().asSeconds();
		BlinkTime += clockPlayer.restart().asSeconds();
		OverTime += clockOver.restart().asSeconds();
		BossDieTime += clockBossDie.restart().asSeconds();

		/************************CHECK / UPDATE ZOMBIE*********************************/
		if (heart > 0)
		{
			for (int i = 0; i < zombieVec.size(); i++) {
				if ((abs(player.GetPosition().y - zombieVec[i].GetPosition().y) <= 10.0f) && (abs(player.GetPosition().x - zombieVec[i].GetPosition().x) <= 120.0f)) {
					if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
						zombieWalk[i] = 5;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					else {
						zombieWalk[i] = 4;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else if ((abs(player.GetPosition().y - zombieVec[i].GetPosition().y) <= 10.0f) && (abs(player.GetPosition().x - zombieVec[i].GetPosition().x) <= 300.0f)) {
					if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
						zombieWalk[i] = 3;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					else {
						zombieWalk[i] = 2;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else {
					if (zombieVec[i].GetPosition().x > platforms[ranP[i]].GetPosition().x + platforms[ranP[i]].GetSize().x / 2.2f) {
						zombieWalk[i] = 0;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					else if (zombieVec[i].GetPosition().x < platforms[ranP[i]].GetPosition().x - platforms[ranP[i]].GetSize().x / 2.2f) {
						zombieWalk[i] = 1;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				textHpVec[i].updateZombie(zombieVec[i]);

				/*************************Check player kill zombie********************************************/
				if (player.BulletIsCollisionWithEnermy(zombieVec[i]))
				{
					sound[4].play();
					timer = 0.0f;
					Boom.setPos(zombieVec[i].GetPosition());
					text_dm.text.setString(std::to_string(damageZombie));
					text_dm.text.setPosition(zombieVec[i].GetPosition().x, zombieVec[i].GetPosition().y - 30.f);
					textArray.push_back(text_dm);
					zombieHp[i] -= damageZombie;
					textHpVec[i].text.setString(std::to_string(zombieHp[i]));
					if (zombieHp[i] <= 0) {
						StoneVec[i].setPos(zombieVec[i].GetPosition());
						zombieDie.setPos(zombieVec[i].GetPosition());
						zombieVec[i].setPos({ 422234, 423432 });
					}

					if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
						zombieVec[i].move(sf::Vector2f(-10, 0));
					}
					else {
						zombieVec[i].move(sf::Vector2f(10, 0));
					}
				}
				/**************************player Collision With Zombie**********************************/
				if (BlinkTime > 3.f) {
					if (player.isCollisionWithZombie(zombieVec[i]))
					{
						sound[3].play();
						BlinkTime = 0.0f;
						if (player.GetPosition().x >= zombieVec[i].GetPosition().x)
							player.setPos({ player.GetPosition().x + 100.f, player.GetPosition().y });
						else
							player.setPos({ player.GetPosition().x - 100.f, player.GetPosition().y });
						if (armor > 0) {
							armor -= 1;
							text_dm.text.setString("ARMOR -1");
							text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
							textArray.push_back(text_dm);
						}
						else {
							heart -= 1;
							text_dm.text.setString("HEART -1");
							text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
							textArray.push_back(text_dm);
						}
					}
				}
			}
		}
		else /*******************UPDATE zombie (Heart <= 0)**************************/
			for (int i = 0; i < zombieVec.size(); i++) {
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
				textHpVec[i].updateZombie(zombieVec[i]);
			}

		/**********************set condition***************************/
		player.Text.setString(std::to_string(heart));
		if (player.GetPosition().y > VIEW_HEIGHT) {
			BlinkTime = 0.0f;
			player.setPos({ player.GetPosition().x - 200, 500 });
			heart -= 1;
			text_dm.text.setString("HEART -1");
			text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
			textArray.push_back(text_dm);
			sound[0].play();
		}
		for (int i = 0; i < textArray.size(); i++)
			if (textArray[i].destroy)
				textArray.erase(textArray.begin());

		/***************Update Item************************/
		for (int i = 0; i < coinGoldVec.size(); i++) 
			coinGoldVec[i].Update(deltaTime);
		for (int i = 0; i < coinSilverVec.size(); i++)
			coinSilverVec[i].Update(deltaTime);
		for (int i = 0; i < coinBronzeVec.size(); i++)
			coinBronzeVec[i].Update(deltaTime);		
		for (int i = 0; i < ChestVec.size(); i++)
			ChestVec[i].Update(deltaTime);
		for (int i = 0; i < HeartVec.size(); i++)
			HeartVec[i].Update(deltaTime);
		for (int i = 0; i < ArmorVec.size(); i++)
			ArmorVec[i].Update(deltaTime);
		for (int i = 0; i < Boxs.size(); i++)
			Boxs[i].Update(deltaTime);

		/***************************DEBUG Random ITEM*******************************************/
		for (Item& coinGold : coinGoldVec) {
			while (coinGold.GetPosition().y > 540.0f && coinGold.GetPosition().x < 25000.0f)
				coinGold.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinSilver : coinSilverVec) {
			while (coinSilver.GetPosition().y > 540.0f && coinSilver.GetPosition().x < 25000.0f)
				coinSilver.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinBronze : coinBronzeVec) {
			while (coinBronze.GetPosition().y > 540.0f && coinBronze.GetPosition().x < 25000.0f)
				coinBronze.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& chest : ChestVec) {
			while (chest.GetPosition().y > 540.0f && chest.GetPosition().x < 25000.0f)
				chest.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& heart : HeartVec) {
			while (heart.GetPosition().y > 540.0f && heart.GetPosition().x < 25000.0f)
				heart.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& armor : ArmorVec) {
			while (armor.GetPosition().y > 540.0f && armor.GetPosition().x < 25000.0f)
				armor.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		
		/******************************Oncollision with Platform*********************************/
		sf::Vector2f direction;
		for (Platform& platform : platforms) {
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
			player.BulletIsCollisionWithPlatform(platform);
			boss.BulletIsCollisionWithPlatform(platform);
			if (platform.GetCollider().CheckCollision(playerDie.GetCollider(), direction, 1.0f))
				playerDie.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(zombieDie.GetCollider(), direction, 1.0f))
				zombieDie.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(bigChest.GetCollider(), direction, 1.0f))
				bigChest.OnCollision(direction);
			for (Enemy& zombie : zombieVec) {
				if (platform.GetCollider().CheckCollision(zombie.GetCollider(), direction, 1.0f))
					zombie.OnCollision(direction);
			}
			for (Item& coinGold : coinGoldVec) {
				if (platform.GetClash().CheckClash(coinGold.GetClash(), direction, 1.0f))
					coinGold.OnCollision(direction);
			}
			for (Item& coinSilver : coinSilverVec) {
				if (platform.GetClash().CheckClash(coinSilver.GetClash(), direction, 1.0f))
					coinSilver.OnCollision(direction);
			}
			for (Item& coinBronze : coinBronzeVec) {
				if (platform.GetClash().CheckClash(coinBronze.GetClash(), direction, 1.0f))
					coinBronze.OnCollision(direction);
			}
			for (Item& chest : ChestVec) {
				if (platform.GetClash().CheckClash(chest.GetClash(), direction, 1.0f))
					chest.OnCollision(direction);
			}
			for (Item& heart : HeartVec) {
				if (platform.GetClash().CheckClash(heart.GetClash(), direction, 1.0f))
					heart.OnCollision(direction);
			}
			for (Item& armor : ArmorVec) {
				if (platform.GetClash().CheckClash(armor.GetClash(), direction, 1.0f))
					armor.OnCollision(direction);
			}
			for (Item& opject : Boxs) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
			for (Opject& opject : OpjectVec) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
		}
		for (Item& box : Boxs) {
			if (player.BulletIsCollisionWithBox(box)) {
				box.setPos({ 42356, 45623 });
			}
			if (box.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
		}
		/***************************Boss onconllision with platform 0-29*******************************************************/
		for (int i = 0; i < 29; i++) {
			if (platforms[i].GetCollider().CheckCollision(boss.GetCollider(), direction, 1.0f))
				boss.OnCollision(direction);
			if (platforms[i].GetCollider().CheckCollision(bossDie.GetCollider(), direction, 1.0f))
				bossDie.OnCollision(direction);
		}

		/**************************item logic & score item****************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			if (player.isCollisionWithItem(coinGoldVec[i]))
			{
				coinGoldVec[i].setPos({ 422234, 423432 });
				score += 3;
				goldCoin -= 1;
			}
		for (int i = 0; i < coinSilverVec.size(); i++)
			if (player.isCollisionWithItem(coinSilverVec[i]))
			{
				coinSilverVec[i].setPos({ 422234, 423432 });
				score += 2;
				silverCoin -= 1;
			}
		for (int i = 0; i < coinBronzeVec.size(); i++)
			if (player.isCollisionWithItem(coinBronzeVec[i]))
			{
				coinBronzeVec[i].setPos({ 422234, 423432 });
				score++;
				bronzeCoin -= 1;
			}
		for (int i = 0; i < StoneVec.size(); i++)
			if (player.isCollisionWithItem(StoneVec[i]))
			{
				StoneVec[i].setPos({ 422234, 423432 });
				score += 6;
			}
		for (Item& Chest : ChestVec)
			if (player.isCollisionWithItem(Chest))
			{
				Chesttimer = 0.f;
				ChestOpen.setPos(Chest.GetPosition());
				Chest.setPos({ 422234, 423432 });
				score += 5;
				chest -= 1;
			}
		if (Chesttimer > 2)
			ChestOpen.setPos({ 422234, 423432 });

		for (int i = 0; i < HeartVec.size(); i++)
			if (player.isCollisionWithItem(HeartVec[i]))
			{
				HeartVec[i].setPos({ 422234, 423432 });
				heart += 1;
			}
		for (int i = 0; i < ArmorVec.size(); i++)
			if (player.isCollisionWithItem(ArmorVec[i]))
			{
				ArmorVec[i].setPos({ 422234, 423432 });
				armor += 1;
			}

		/********************************Check BOSS / Big Chest********************************************/
		bigChest.Update(deltaTime);
		if (chest <= 0 && touchBigchest == false)
		{
			bigChest.setPos(sf::Vector2f(18000.0f, 450.0f));
			/*if (p == false) {
			player.setPos(sf::Vector2f(17500.0f, 450.0f));
			p = true;
			}*/
			if (player.isCollisionWithItem(bigChest)) {
				sound[2].play();
				score += 50;
				bigChest.setPos({ 422234, 423432 });
				boss.setPos(sf::Vector2f(18200.0f, 100.0f));
				touchBigchest = true;
			}
		}

		if (touchBigchest == true) {
			boss.Update(deltaTime, player);
		}

		if (bossHp <= 0 && bossDead == false) {
			BossDieTime = 0.0f;
			bossDie.setPos(boss.GetPosition());
			boss.setPos({ 42324, 43214 });
			bossDead = true;
			bossDie.Update(deltaTime, player);
		}

		else if (bossDead == true)
			bossDie.Update(deltaTime, player);
		/***************************Boss Attack player*******************************************/
		if (BlinkTime > 3.f) {
			if (boss.BulletIsCollisionWithPlayer(player))
			{
				sound[0].play();
				sound[3].play();
				BlinkTime = 0.0f;
				boss.BulletIsCollisionWithPlayer(player);
				heart -= 1;
				text_dm.text.setString("HEART -1");
				text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
				textArray.push_back(text_dm);
			}
			if (player.getGlobalBounds().intersects(boss.getGlobalBounds()))
			{
				BlinkTime = 0.0f;
				if (player.GetPosition().x < boss.GetPosition().x)
					player.move(sf::Vector2f(-200, 0));
				else
					player.move(sf::Vector2f(200, 0));

				heart -= 1;
				text_dm.text.setString("HEART -1");
				text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
				textArray.push_back(text_dm);
			}
		}

		/*************************Player Blink**************************************/
		if (BlinkTime< 0.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 0.5f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 0.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 1.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 1.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 1.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 1.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 2.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 2.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 3.0f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else
			player.setFillColor(sf::Color(255, 255, 255, 255));

		/*************************Check Player shoot boss****************************/
		if (CheckShootBoss(player, boss) == 1) {
			sound[1].play();
			sound[4].play();
			shootBoss = true;
			player.vbulletR.erase(player.vbulletR.begin());
		}
		else if (CheckShootBoss(player, boss) == 2) {
			sound[1].play();
			sound[4].play();
			shootBoss = true;
			player.vbulletL.erase(player.vbulletL.begin());
		}

		if (shootBoss == true)
		{
			text_boss.text.setString(std::to_string(damageZombie));
			text_boss.text.setPosition(boss.GetPosition().x, boss.GetPosition().y - 60.f);
			textBossVec.push_back(text_boss);
			bossHp -= damageZombie;
			printf("%i\n", bossHp);
			shootBoss = false;
		}
		for (TextDisplay& text : textBossVec)
			text.update();
		for (int i = 0; i < textBossVec.size(); i++)
			if (textBossVec[i].destroy)
				textBossVec.erase(textBossVec.begin());
		textBossHp.updateBoss(boss);
		textBossHp.text.setString(std::to_string(bossHp));

		/*****************************Show score***************************************/
		textBar.Update(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, position);

		/***********************Update Effect*****************************/
		ChestOpen.Update(deltaTime, player);
		playerDie.Update(deltaTime, player);
		zombieDie.Update(deltaTime, player);
		Boom.Update(deltaTime, player);
		for (Opject& opject : OpjectVec)
			opject.Update(deltaTime);
		if (timer > 1) {
			zombieDie.setPos({ 422234, 423432 });
			Boom.setPos({ 422234, 423432 });
		}
		for (TextDisplay& text : textArray) {
			text.update();
		}

		/*********************Heart <= 0 / Player dead******************/
		if (heart <= 0 && playerDead == false) {
			OverTime = 0.0f;
			playerDie.setPos(player.GetPosition());
			gameOver = true;
			playerDead = true;
		}

		/************************************NEXT**************************/
		if (OverTime > 3 && gameOver == true)
			GameOver(window, 2);
		if (bossDead == true && BossDieTime > 3)
			LevelUp(window, 2);

		/***************************Window DRAW**********************************/
		bg.Draw(window);
		window.setView(gameView);
		platform_water(window, 9);

		for (Opject& opject : OpjectVec)
			opject.Draw(window);
		for (Item& box : Boxs)
			box.Draw(window);
		for (Item& chest : ChestVec)
			chest.Draw(window);
		for (Item& coin : coinGoldVec)
			coin.Draw(window);
		for (Item& coin : coinSilverVec)
			coin.Draw(window);
		for (Item& coin : coinBronzeVec)
			coin.Draw(window);
		for (Item& heart : HeartVec)
			heart.Draw(window);
		for (Item& armor : ArmorVec)
			armor.Draw(window);
		for (Item& stone : StoneVec)
			stone.Draw(window);
		for (Platform& platform : platforms)
			platform.Draw(window);
		for (Enemy& zombie : zombieVec)
			zombie.Draw(window);
		bigChest.Draw(window);
		boss.Draw(window);
		zombieDie.Draw(window);
		playerDie.Draw(window);
		textBossHp.Draw(window);
		if (heart > 0)
			player.Draw(window);
		for (TextDisplay& text : textArray)
			text.Draw(window);
		for (TextDisplay& text : textBossVec)
			text.Draw(window);
		ChestOpen.Draw(window);
		for (TextHp& textHp : textHpVec)
			textHp.Draw(window);
		bossDie.Draw(window);
		Boom.Draw(window);
		textBar.Draw(window);
		Myname(window, sf::Vector2f(position.x, position.y + 230));
		window.display();
		window.clear();
	}
}

void GameLevel_3(sf::RenderWindow & window)
{
	sf::View gameView;
	gameView.reset(sf::FloatRect(0.0f, 0.0f, VIEW_WIDTH, VIEW_HEIGHT));

	sf::Vector2f position(VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
	background bg(3);

	/************************SET SOUND EFFECT*************************/
	sf::SoundBuffer buffer[5];
	sf::Sound sound[5];
	buffer[0].loadFromFile("Sound/SCREAM3.ogg");
	buffer[1].loadFromFile("Sound/Fireball-3.ogg");
	buffer[2].loadFromFile("Sound/FASTPOP.ogg");
	buffer[3].loadFromFile("Sound/Monster.ogg");
	buffer[4].loadFromFile("Sound/HOLOWPOP.ogg");
	sound[0].setBuffer(buffer[0]);
	sound[1].setBuffer(buffer[1]);
	sound[2].setBuffer(buffer[2]);
	sound[3].setBuffer(buffer[3]);
	sound[4].setBuffer(buffer[4]);
	sound[0].setVolume(50);
	sound[2].setVolume(20);
	sound[2].setVolume(50);
	sound[3].setVolume(40);
	sound[4].setVolume(50);

	/***********************player / Enemy*****************************/
	Player player(&playerTexture, sf::Vector2u(10, 5), 0.1f, 330.75f, 300.0f, 3);
	std::vector<Enemy> zombieVec;

	/****************************BOSS********************************/
	Boss boss(ResourceManager::GetInstance()->RequestTexture("boss3"), sf::Vector2u(6, 4), 0.08f, 170.0f, sf::Vector2f(20000.0f, 0.0f), 3);
	Item bigChest(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, sf::Vector2f(120.0f, 80.0f), sf::Vector2f(20000.0f, rand() % 500));
	
	/**********************Effect Zombie***********************/
	Effect playerDie(&playerOverGame, sf::Vector2u(10, 1), 0.4f, 0);
	Effect zombieDie(ResourceManager::GetInstance()->RequestTexture("zombie3_die"), sf::Vector2u(8, 1), 0.2f, 1);
	Effect bossDie(ResourceManager::GetInstance()->RequestTexture("boss3_die"), sf::Vector2u(8, 1), 0.3f, 4);
	Effect Boom(ResourceManager::GetInstance()->RequestTexture("boom"), sf::Vector2u(8, 8), 0.1f, 3);
	Effect ChestOpen(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, 2);

	/******************************coin*******************************************/
	std::vector<Item> coinGoldVec, coinSilverVec, coinBronzeVec;
	int randCoin[210];
	for (int i = 0; i < 210; i++)
	{
		randCoin[i] = (rand() % 410) * 40 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randCoin[i] == randCoin[j]) {
				randCoin[i] = (rand() % 410) * 40 + 250;
				j = i - 1;
			}
	}
	for (int i = 0; i < 70; i++)
	{
		coinGoldVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinGold"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i], rand() % 400)));
		coinSilverVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinSilver"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i + 70], rand() % 400)));
		coinBronzeVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinBronze"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i + 140], rand() % 400)));
	}

	/******************************TEASURE CHEST******************************************/
	std::vector<Item> ChestVec;
	int randChest[20];
	for (int i = 0; i < 0; i++)
	{
		randChest[i] = (rand() % 250) * 70 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randChest[i] == randChest[j]) {
				randChest[i] = (rand() % 250) * 70 + 250;
				j = i - 1;
			}
		ChestVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("chestClosed"), sf::Vector2u(1, 1), 0.6f, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(randChest[i], rand() % 400)));
	}

	/********************************ITEM HEART / ARMOR*******************************************/
	std::vector<Item> HeartVec, ArmorVec;
	for (int i = 0; i < 3; i++)
		HeartVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("heart"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(((rand() % 800) * 20) + 2000, rand() % 540)));

	for (int i = 0; i < 3; i++)
		ArmorVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("armor"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(((rand() % 800) * 20) + 2000, rand() % 540)));

	/***********************************OPJECT*******************************************************/
	std::vector<Item> Boxs;
	for (int i = 0; i < 50; i++) {
		Boxs.push_back(Item(ResourceManager::GetInstance()->RequestTexture("crate"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
	}
	std::vector<Opject> OpjectVec;
	for (int i = 0; i < 30; i++) {
		OpjectVec.push_back(Opject(3, sf::Vector2f(60.0f, 60.0f), sf::Vector2f(((rand() % 300) * 60) + 200, rand() % 540)));
		OpjectVec.push_back(Opject(4, sf::Vector2f(40.0f, 60.0f), sf::Vector2f(((rand() % 420) * 40) + 200, rand() % 540)));
		//OpjectVec.push_back(Opject(5, sf::Vector2f(80.0f, 100.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
		//OpjectVec.push_back(Opject(6, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
	}
	std::vector<Item> StoneVec;
	for (int i = 0; i < 70; i++) {
		StoneVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("stone_green"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(30000, 30000)));
	}
	/******************************platform Level 3******************************************/
	std::vector<Platform> platforms;

	float px = 0.0f, count = 0.0f, hole = 0.0f;
	for (int i = 0; i < 29; i++)
	{
		platforms.push_back(Platform(18, sf::Vector2f(640.0f, 64.0f), sf::Vector2f(320.0f + px + hole, 520.0f)));
		px += 600.0f;
		if (i % 4 == 0 && i != 0)
			hole += 200.0f;
	}
	for (int i = 0; i < 7; i++)
	{
		platforms.push_back(Platform(19, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(60.0f + count, 120.0f)));
		platforms.push_back(Platform(21, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(120.0f + count, 250.0f)));
		platforms.push_back(Platform(22, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(150.0f + count, 390.0f)));
		platforms.push_back(Platform(25, sf::Vector2f(470.0f, 38.5f), sf::Vector2f(600.0f + count, 190.0f)));
		platforms.push_back(Platform(25, sf::Vector2f(470.0f, 38.5f), sf::Vector2f(900.0f + count, 350.0f)));
		platforms.push_back(Platform(19, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(1600.0f + count, 110.0f)));
		platforms.push_back(Platform(21, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(1000.0f + count, 70.0f)));
		platforms.push_back(Platform(20, sf::Vector2f(210.0f, 38.5f), sf::Vector2f(1250.0f + count, 200.0f)));
		platforms.push_back(Platform(25, sf::Vector2f(470.0f, 38.5f), sf::Vector2f(1600.0f + count, 360.0f)));
		platforms.push_back(Platform(19, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(2400.0f + count, 180.0f)));
		platforms.push_back(Platform(21, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(1600.0f + count, 240.0f)));
		platforms.push_back(Platform(23, sf::Vector2f(370.0f, 38.5f), sf::Vector2f(2100.0f + count, 70.0f)));
		platforms.push_back(Platform(22, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2100.0f + count, 300.0f)));
		//platforms.push_back(Platform(22, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2300.0f + count, 210.0f)));
		count += 2550;
	}

	/****************************************Random Zombie Position********************************************/
	float platformP[300];
	for (int i = 0; i<platforms.size(); i++)
		platformP[i] = platforms[i].GetPosition().x - (platforms[i].GetSize().x / 2) + 25.0f;

	int ranP[70], damageZombie = 20, zombieHp[70], bossHp = 500;
	for (int i = 0; i < 70; i++)
		zombieHp[i] = 100;
	TextHp textHp, textBossHp;
	std::vector<TextHp> textHpVec;

	for (int i = 0; i < 70; i++) {
		ranP[i] = rand() % 104 + 2;
		for (int j = i - 1; j >= 0; j--)
			while (ranP[i] == ranP[j]) {
				ranP[i] = rand() % 104 + 2;
				j = i - 1;
			}
		zombieVec.push_back(Enemy(ResourceManager::GetInstance()->RequestTexture("zombie3"), sf::Vector2u(6, 4), 0.13f, 96.8f, sf::Vector2f(platformP[ranP[i]] + 50.0f, platforms[ranP[i]].GetPosition().y - platforms[ranP[i]].GetSize().y)));
		textHp.text.setPosition(zombieVec[i].GetPosition().x, zombieVec[i].GetPosition().y - 60);
		textHp.text.setString(std::to_string(zombieHp[i]));
		textHpVec.push_back(textHp);
	}
	int zombieWalk[70];
	for (int i = 0; i < 70; i++)
		zombieWalk[i] = 0;

	/**********************************score coin************************************/
	int goldCoin = 70, silverCoin = 70, bronzeCoin = 70, chest = 20, level = 3;
	TextBar textBar(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, playerNum);

	/************************TextDisplay**************************/
	std::vector<TextDisplay> textArray, textBossVec;
	TextDisplay text_dm, text_boss;

	bool touchBigchest = false, p = false, bossDead = false, shootBoss = false, gameOver = false, playerDead = false;
	float timer = 0.0f, Chesttimer = 0.0f, BlinkTime = 0.0f, OverTime = 0.0f, BossDieTime = 0.0f;
	float deltaTime = 0.0f;
	sf::Clock clock, clockTimer, clockChest, clockPlayer, clockOver, clockBossDie;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.key.code == sf::Keyboard::Escape)
				GameOver(window, 3);
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//ResizeVeiw(window, view);
				break;
			}
		}

		/************position*************/
		if (player.GetPosition().x + 25 > VIEW_WIDTH / 2)
			position.x = player.GetPosition().x + 25;
		else
			position.x = VIEW_WIDTH / 2;
		if (player.GetPosition().y + 25 < VIEW_HEIGHT / 2)
			position.y = player.GetPosition().y + 25;
		else
			position.y = VIEW_HEIGHT / 2;
		gameView.setCenter(position);

		/******************Update player********************/
		if (heart > 0)
			player.Update(deltaTime);

		/**********************CLOCK************************/
		timer += clockTimer.restart().asSeconds();
		Chesttimer += clockChest.restart().asSeconds();
		BlinkTime += clockPlayer.restart().asSeconds();
		OverTime += clockOver.restart().asSeconds();
		BossDieTime += clockBossDie.restart().asSeconds();

		/************************CHECK / UPDATE ZOMBIE*********************************/
		if (heart > 0)
		{
			for (int i = 0; i < zombieVec.size(); i++) {
				if ((abs(player.GetPosition().y - zombieVec[i].GetPosition().y) <= 10.0f) && (abs(player.GetPosition().x - zombieVec[i].GetPosition().x) <= 120.0f)) {
					if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
						zombieWalk[i] = 5;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					else {
						zombieWalk[i] = 4;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else if ((abs(player.GetPosition().y - zombieVec[i].GetPosition().y) <= 10.0f) && (abs(player.GetPosition().x - zombieVec[i].GetPosition().x) <= 300.0f)) {
					if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
						zombieWalk[i] = 3;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					else {
						zombieWalk[i] = 2;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else {
					if (zombieVec[i].GetPosition().x > platforms[ranP[i]].GetPosition().x + platforms[ranP[i]].GetSize().x / 2.2f) {
						zombieWalk[i] = 0;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					else if (zombieVec[i].GetPosition().x < platforms[ranP[i]].GetPosition().x - platforms[ranP[i]].GetSize().x / 2.2f) {
						zombieWalk[i] = 1;
						zombieVec[i].Update(deltaTime, zombieWalk[i]);
					}
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				textHpVec[i].updateZombie(zombieVec[i]);

				/*************************Check player kill zombie********************************************/
				if (player.BulletIsCollisionWithEnermy(zombieVec[i]))
				{
					sound[4].play();
					timer = 0.0f;
					Boom.setPos(zombieVec[i].GetPosition());
					text_dm.text.setString(std::to_string(damageZombie));
					text_dm.text.setPosition(zombieVec[i].GetPosition().x, zombieVec[i].GetPosition().y - 30.f);
					textArray.push_back(text_dm);
					zombieHp[i] -= damageZombie;
					textHpVec[i].text.setString(std::to_string(zombieHp[i]));
					if (zombieHp[i] <= 0) {
						StoneVec[i].setPos(zombieVec[i].GetPosition());
						zombieDie.setPos(zombieVec[i].GetPosition());
						zombieVec[i].setPos({ 422234, 423432 });
					}

					if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
						zombieVec[i].move(sf::Vector2f(-10, 0));
					}
					else {
						zombieVec[i].move(sf::Vector2f(10, 0));
					}
				}
				/**************************player Collision With Zombie**********************************/
				if (BlinkTime > 3.f) {
					if (player.isCollisionWithZombie(zombieVec[i]))
					{
						sound[3].play();
						BlinkTime = 0.0f;
						if (player.GetPosition().x >= zombieVec[i].GetPosition().x)
							player.setPos({ player.GetPosition().x + 100.f, player.GetPosition().y });
						else
							player.setPos({ player.GetPosition().x - 100.f, player.GetPosition().y });
						if (armor > 0) {
							armor -= 1;
							text_dm.text.setString("ARMOR -1");
							text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
							textArray.push_back(text_dm);
						}
						else {
							heart -= 1;
							text_dm.text.setString("HEART -1");
							text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
							textArray.push_back(text_dm);
						}
					}
				}
			}
		}
		else /*******************UPDATE zombie (Heart <= 0)**************************/
			for (int i = 0; i < zombieVec.size(); i++) {
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
				textHpVec[i].updateZombie(zombieVec[i]);
			}

		/**********************set condition***************************/
		player.Text.setString(std::to_string(heart));
		if (player.GetPosition().y > VIEW_HEIGHT) {
			BlinkTime = 0.0f;
			player.setPos({ player.GetPosition().x - 200, 500 });
			heart -= 1;
			text_dm.text.setString("HEART -1");
			text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
			textArray.push_back(text_dm);
			sound[0].play();
		}
		for (int i = 0; i < textArray.size(); i++)
			if (textArray[i].destroy)
				textArray.erase(textArray.begin());

		/***************Update Item************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			coinGoldVec[i].Update(deltaTime);
		for (int i = 0; i < coinSilverVec.size(); i++)
			coinSilverVec[i].Update(deltaTime);
		for (int i = 0; i < coinBronzeVec.size(); i++)
			coinBronzeVec[i].Update(deltaTime);
		for (int i = 0; i < ChestVec.size(); i++)
			ChestVec[i].Update(deltaTime);
		for (int i = 0; i < HeartVec.size(); i++)
			HeartVec[i].Update(deltaTime);
		for (int i = 0; i < ArmorVec.size(); i++)
			ArmorVec[i].Update(deltaTime);
		for (int i = 0; i < Boxs.size(); i++)
			Boxs[i].Update(deltaTime);

		/***************************DEBUG Random ITEM*******************************************/
		for (Item& coinGold : coinGoldVec) {
			while (coinGold.GetPosition().y > 540.0f && coinGold.GetPosition().x < 25000.0f)
				coinGold.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinSilver : coinSilverVec) {
			while (coinSilver.GetPosition().y > 540.0f && coinSilver.GetPosition().x < 25000.0f)
				coinSilver.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinBronze : coinBronzeVec) {
			while (coinBronze.GetPosition().y > 540.0f && coinBronze.GetPosition().x < 25000.0f)
				coinBronze.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& chest : ChestVec) {
			while (chest.GetPosition().y > 540.0f && chest.GetPosition().x < 25000.0f)
				chest.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& heart : HeartVec) {
			while (heart.GetPosition().y > 540.0f && heart.GetPosition().x < 25000.0f)
				heart.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& armor : ArmorVec) {
			while (armor.GetPosition().y > 540.0f && armor.GetPosition().x < 25000.0f)
				armor.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}

		/******************************Oncollision with Platform*********************************/
		sf::Vector2f direction;
		for (Platform& platform : platforms) {
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
			player.BulletIsCollisionWithPlatform(platform);
			boss.BulletIsCollisionWithPlatform(platform);
			if (platform.GetCollider().CheckCollision(playerDie.GetCollider(), direction, 1.0f))
				playerDie.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(zombieDie.GetCollider(), direction, 1.0f))
				zombieDie.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(bigChest.GetCollider(), direction, 1.0f))
				bigChest.OnCollision(direction);
			for (Enemy& zombie : zombieVec) {
				if (platform.GetCollider().CheckCollision(zombie.GetCollider(), direction, 1.0f))
					zombie.OnCollision(direction);
			}
			for (Item& coinGold : coinGoldVec) {
				if (platform.GetClash().CheckClash(coinGold.GetClash(), direction, 1.0f))
					coinGold.OnCollision(direction);
			}
			for (Item& coinSilver : coinSilverVec) {
				if (platform.GetClash().CheckClash(coinSilver.GetClash(), direction, 1.0f))
					coinSilver.OnCollision(direction);
			}
			for (Item& coinBronze : coinBronzeVec) {
				if (platform.GetClash().CheckClash(coinBronze.GetClash(), direction, 1.0f))
					coinBronze.OnCollision(direction);
			}
			for (Item& chest : ChestVec) {
				if (platform.GetClash().CheckClash(chest.GetClash(), direction, 1.0f))
					chest.OnCollision(direction);
			}
			for (Item& heart : HeartVec) {
				if (platform.GetClash().CheckClash(heart.GetClash(), direction, 1.0f))
					heart.OnCollision(direction);
			}
			for (Item& armor : ArmorVec) {
				if (platform.GetClash().CheckClash(armor.GetClash(), direction, 1.0f))
					armor.OnCollision(direction);
			}
			for (Item& opject : Boxs) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
			for (Opject& opject : OpjectVec) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
		}
		for (Item& box : Boxs) {
			if (player.BulletIsCollisionWithBox(box)) {
				box.setPos({ 42356, 45623 });
			}
			if (box.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
		}
		/***************************Boss onconllision with platform 0-29*******************************************************/
		for (int i = 0; i < 29; i++) {
			if (platforms[i].GetCollider().CheckCollision(boss.GetCollider(), direction, 1.0f))
				boss.OnCollision(direction);
			if (platforms[i].GetCollider().CheckCollision(bossDie.GetCollider(), direction, 1.0f))
				bossDie.OnCollision(direction);
		}

		/**************************item logic & score item****************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			if (player.isCollisionWithItem(coinGoldVec[i]))
			{
				coinGoldVec[i].setPos({ 422234, 423432 });
				score += 3;
				goldCoin -= 1;
			}
		for (int i = 0; i < coinSilverVec.size(); i++)
			if (player.isCollisionWithItem(coinSilverVec[i]))
			{
				coinSilverVec[i].setPos({ 422234, 423432 });
				score += 2;
				silverCoin -= 1;
			}
		for (int i = 0; i < coinBronzeVec.size(); i++)
			if (player.isCollisionWithItem(coinBronzeVec[i]))
			{
				coinBronzeVec[i].setPos({ 422234, 423432 });
				score++;
				bronzeCoin -= 1;
			}
		for (int i = 0; i < StoneVec.size(); i++)
			if (player.isCollisionWithItem(StoneVec[i]))
			{
				StoneVec[i].setPos({ 422234, 423432 });
				score += 9;
			}
		for (Item& Chest : ChestVec)
			if (player.isCollisionWithItem(Chest))
			{
				Chesttimer = 0.f;
				ChestOpen.setPos(Chest.GetPosition());
				Chest.setPos({ 422234, 423432 });
				score += 5;
				chest -= 1;
			}
		if (Chesttimer > 2)
			ChestOpen.setPos({ 422234, 423432 });

		for (int i = 0; i < HeartVec.size(); i++)
			if (player.isCollisionWithItem(HeartVec[i]))
			{
				HeartVec[i].setPos({ 422234, 423432 });
				heart += 1;
			}
		for (int i = 0; i < ArmorVec.size(); i++)
			if (player.isCollisionWithItem(ArmorVec[i]))
			{
				ArmorVec[i].setPos({ 422234, 423432 });
				armor += 1;
			}

		/********************************Check BOSS / Big Chest********************************************/
		bigChest.Update(deltaTime);
		if (chest <= 0 && touchBigchest == false)
		{
			bigChest.setPos(sf::Vector2f(18000.0f, 450.0f));
			/*if (p == false) {
			player.setPos(sf::Vector2f(17500.0f, 450.0f));
			p = true;
			}*/
			if (player.isCollisionWithItem(bigChest)) {
				sound[2].play();
				score += 50;
				bigChest.setPos({ 422234, 423432 });
				boss.setPos(sf::Vector2f(18200.0f, 100.0f));
				touchBigchest = true;
			}
		}

		if (touchBigchest == true) {
			boss.Update(deltaTime, player);
		}

		if (bossHp <= 0 && bossDead == false) {
			BossDieTime = 0.0f;
			bossDie.setPos(boss.GetPosition());
			boss.setPos({ 42324, 43214 });
			bossDead = true;
			bossDie.Update(deltaTime, player);
		}
		else if (bossDead == true)
			bossDie.Update(deltaTime, player);
		
		/***************************Boss Attack player*******************************************/
		if (BlinkTime > 3.f) {
			if (boss.BulletIsCollisionWithPlayer(player))
			{
				sound[0].play();
				sound[1].play();
				BlinkTime = 0.0f;
				boss.BulletIsCollisionWithPlayer(player);
				heart -= 1;
				text_dm.text.setString("HEART -1");
				text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
				textArray.push_back(text_dm);
			}
			if (player.getGlobalBounds().intersects(boss.getGlobalBounds()))
			{
				BlinkTime = 0.0f;
				if (player.GetPosition().x < boss.GetPosition().x)
					player.move(sf::Vector2f(-200, 0));
				else
					player.move(sf::Vector2f(200, 0));

				heart -= 1;
				text_dm.text.setString("HEART -1");
				text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
				textArray.push_back(text_dm);
			}
		}

		/*************************Player Blink**************************************/
		if (BlinkTime< 0.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 0.5f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 0.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 1.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 1.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 1.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 1.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 2.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 2.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 3.0f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else
			player.setFillColor(sf::Color(255, 255, 255, 255));

		/*************************Check Player shoot boss****************************/
		if (CheckShootBoss(player, boss) == 1) {
			sound[1].play();
			sound[4].play();
			shootBoss = true;
			player.vbulletR.erase(player.vbulletR.begin());
		}
		else if (CheckShootBoss(player, boss) == 2) {
			sound[1].play();
			sound[4].play();
			shootBoss = true;
			player.vbulletL.erase(player.vbulletL.begin());
		}

		if (shootBoss == true)
		{
			text_boss.text.setString(std::to_string(damageZombie));
			text_boss.text.setPosition(boss.GetPosition().x, boss.GetPosition().y - 60.f);
			textBossVec.push_back(text_boss);
			bossHp -= damageZombie;
			printf("%i\n", bossHp);
			shootBoss = false;
		}
		for (TextDisplay& text : textBossVec)
			text.update();
		for (int i = 0; i < textBossVec.size(); i++)
			if (textBossVec[i].destroy)
				textBossVec.erase(textBossVec.begin());
		textBossHp.updateBoss(boss);
		textBossHp.text.setString(std::to_string(bossHp));

		/*****************************Show score***************************************/
		textBar.Update(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, position);

		/***********************Update Effect*****************************/
		ChestOpen.Update(deltaTime, player);
		playerDie.Update(deltaTime, player);
		zombieDie.Update(deltaTime, player);
		Boom.Update(deltaTime, player);
		for (Opject& opject : OpjectVec)
			opject.Update(deltaTime);
		if (timer > 1) {
			zombieDie.setPos({ 422234, 423432 });
			Boom.setPos({ 422234, 423432 });
		}
		for (TextDisplay& text : textArray) {
			text.update();
		}

		/*********************Heart <= 0 / Player dead******************/
		if (heart <= 0 && playerDead == false) {
			OverTime = 0.0f;
			playerDie.setPos(player.GetPosition());
			gameOver = true;
			playerDead = true;
		}

		/************************************NEXT**************************/
		if (OverTime > 3 && gameOver == true)
			GameOver(window, 3);
		if (bossDead == true && BossDieTime > 3)
			LevelUp(window, 3);

		/***************************Window DRAW**********************************/
		bg.Draw(window);
		window.setView(gameView);
		platform_water(window, 26);

		for (Opject& opject : OpjectVec)
			opject.Draw(window);
		for (Item& box : Boxs)
			box.Draw(window);
		for (Item& chest : ChestVec)
			chest.Draw(window);
		for (Item& coin : coinGoldVec)
			coin.Draw(window);
		for (Item& coin : coinSilverVec)
			coin.Draw(window);
		for (Item& coin : coinBronzeVec)
			coin.Draw(window);
		for (Item& heart : HeartVec)
			heart.Draw(window);
		for (Item& armor : ArmorVec)
			armor.Draw(window);
		for (Item& stone : StoneVec)
			stone.Draw(window);
		for (Platform& platform : platforms)
			platform.Draw(window);
		for (Enemy& zombie : zombieVec)
			zombie.Draw(window);
		bigChest.Draw(window);
		boss.Draw(window);
		zombieDie.Draw(window);
		playerDie.Draw(window);
		textBossHp.Draw(window);
		if (heart > 0)
			player.Draw(window);
		for (TextDisplay& text : textArray)
			text.Draw(window);
		for (TextDisplay& text : textBossVec)
			text.Draw(window);
		ChestOpen.Draw(window);
		for (TextHp& textHp : textHpVec)
			textHp.Draw(window);
		bossDie.Draw(window);
		Boom.Draw(window);
		textBar.Draw(window);
		Myname(window, sf::Vector2f(position.x, position.y + 230));
		window.display();
		window.clear();
	}
}

void GameLevel_4(sf::RenderWindow & window)
{
	sf::View gameView;
	gameView.reset(sf::FloatRect(0.0f, 0.0f, VIEW_WIDTH, VIEW_HEIGHT));

	sf::Vector2f position(VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
	background bg(4);

	/************************SET SOUND EFFECT*************************/
	sf::SoundBuffer buffer[5];
	sf::Sound sound[5];
	buffer[0].loadFromFile("Sound/SCREAM3.ogg");
	buffer[1].loadFromFile("Sound/Fireball-3.ogg");
	buffer[2].loadFromFile("Sound/FASTPOP.ogg");
	buffer[3].loadFromFile("Sound/Monster.ogg");
	buffer[4].loadFromFile("Sound/HOLOWPOP.ogg");
	sound[0].setBuffer(buffer[0]);
	sound[1].setBuffer(buffer[1]);
	sound[2].setBuffer(buffer[2]);
	sound[3].setBuffer(buffer[3]);
	sound[4].setBuffer(buffer[4]);
	sound[0].setVolume(50);
	sound[0].setVolume(20);
	sound[2].setVolume(20);
	sound[2].setVolume(50);
	sound[3].setVolume(40);
	sound[4].setVolume(50);

	/***********************player / Enemy*****************************/
	Player player(&playerTexture, sf::Vector2u(10, 5), 0.07f, 347.2875f, 300.0f, 4);
	std::vector<Enemy> zombieVec;

	/****************************BOSS********************************/
	Boss boss(ResourceManager::GetInstance()->RequestTexture("boss4"), sf::Vector2u(6, 4), 0.1f, 180.0f, sf::Vector2f(20000.0f, 0.0f), 4);
	Item bigChest(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, sf::Vector2f(120.0f, 80.0f), sf::Vector2f(20000.0f, rand() % 500));

	/**********************Effect Zombie***********************/
	Effect playerDie(&playerOverGame, sf::Vector2u(10, 1), 0.4f, 0);
	Effect zombieDie(ResourceManager::GetInstance()->RequestTexture("zombie4_die"), sf::Vector2u(8, 1), 0.1f, 1);
	Effect bossDie(ResourceManager::GetInstance()->RequestTexture("boss4_die"), sf::Vector2u(8, 1), 0.3f, 4);
	Effect Boom(ResourceManager::GetInstance()->RequestTexture("boom"), sf::Vector2u(8, 8), 0.1f, 3);
	Effect ChestOpen(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, 2);

	/******************************coin*******************************************/
	std::vector<Item> coinGoldVec, coinSilverVec, coinBronzeVec;
	int randCoin[240];
	for (int i = 0; i < 240; i++)
	{
		randCoin[i] = (rand() % 410) * 40 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randCoin[i] == randCoin[j]) {
				randCoin[i] = (rand() % 410) * 40 + 250;
				j = i - 1;
			}
	}
	for (int i = 0; i < 80; i++)
	{
		coinGoldVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinGold"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i], rand() % 400)));
		coinSilverVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinSilver"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i + 80], rand() % 400)));
		coinBronzeVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinBronze"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i + 160], rand() % 400)));
	}

	/******************************TEASURE CHEST******************************************/
	std::vector<Item> ChestVec;
	int randChest[25];
	for (int i = 0; i < 25; i++)
	{
		randChest[i] = (rand() % 250) * 70 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randChest[i] == randChest[j]) {
				randChest[i] = (rand() % 250) * 70 + 250;
				j = i - 1;
			}
		ChestVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("chestClosed"), sf::Vector2u(1, 1), 0.6f, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(randChest[i], rand() % 400)));
	}

	/********************************ITEM HEART / ARMOR*******************************************/
	std::vector<Item> HeartVec, ArmorVec;
	for (int i = 0; i < 4; i++)
		HeartVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("heart"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(((rand() % 800) * 20) + 2000, rand() % 540)));

	for (int i = 0; i < 4; i++)
		ArmorVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("armor"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(((rand() % 800) * 20) + 2000, rand() % 540)));

	/***********************************OPJECT*******************************************************/
	std::vector<Item> Boxs;
	for (int i = 0; i < 50; i++) {
		Boxs.push_back(Item(ResourceManager::GetInstance()->RequestTexture("crate"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
	}
	std::vector<Opject> OpjectVec;
	for (int i = 0; i < 30; i++) {
		OpjectVec.push_back(Opject(3, sf::Vector2f(60.0f, 60.0f), sf::Vector2f(((rand() % 300) * 60) + 200, rand() % 540)));
		OpjectVec.push_back(Opject(4, sf::Vector2f(40.0f, 60.0f), sf::Vector2f(((rand() % 420) * 40) + 200, rand() % 540)));
		//OpjectVec.push_back(Opject(5, sf::Vector2f(80.0f, 100.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
		//OpjectVec.push_back(Opject(6, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
	}
	std::vector<Item> StoneVec;
	for (int i = 0; i < 80; i++) {
		StoneVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("stone_blue"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(30000, 30000)));
	}
	
	/******************************platform Level 4******************************************/
	std::vector<Platform> platforms;

	float px = 0.0f, count = 0.0f, hole = 0.0f;
	for (int i = 0; i < 29; i++)
	{
		platforms.push_back(Platform(27, sf::Vector2f(640.0f, 64.0f), sf::Vector2f(320.0f + px + hole, 520.0f)));
		px += 600.0f;
		if (i % 4 == 0 && i != 0)
			hole += 200.0f;
	}
	for (int i = 0; i < 7; i++)
	{
		platforms.push_back(Platform(30, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(100.0f + count, 390.0f)));
		platforms.push_back(Platform(31, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(200.0f + count, 90.0f)));
		platforms.push_back(Platform(28, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(360.0f + count, 250.0f)));
		platforms.push_back(Platform(33, sf::Vector2f(420.0f, 38.5f), sf::Vector2f(750.0f + count, 380.0f)));
		platforms.push_back(Platform(28, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(600.0f + count, 150.0f)));
		platforms.push_back(Platform(30, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(1000.0f + count, 230.0f)));
		platforms.push_back(Platform(34, sf::Vector2f(470.0f, 38.5f), sf::Vector2f(1250.0f + count, 80.0f)));
		platforms.push_back(Platform(29, sf::Vector2f(210.0f, 38.5f), sf::Vector2f(1450.0f + count, 360.0f)));
		platforms.push_back(Platform(32, sf::Vector2f(370.0f, 38.5f), sf::Vector2f(1800.0f + count, 200.0f)));
		platforms.push_back(Platform(32, sf::Vector2f(420.0f, 38.5f), sf::Vector2f(2000.0f + count, 70.0f)));
		platforms.push_back(Platform(31, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2000.0f + count, 350.0f)));
		platforms.push_back(Platform(31, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2400.0f + count, 220.0f)));
		count += 2550;
	}

	/****************************************Random Zombie Position********************************************/
	float platformP[200];
	int ranP[80];
	for (int i = 0; i<platforms.size(); i++)
		platformP[i] = platforms[i].GetPosition().x - (platforms[i].GetSize().x / 2) + 25.0f;

	int damageZombie = 25, zombieHp[150], bossHp = 600;
	for (int i = 0; i < 80; i++)
		zombieHp[i] = 150;
	TextHp textHp, textBossHp;
	std::vector<TextHp> textHpVec;

	for (int i = 0; i < 80; i++) {
		ranP[i] = rand() % 104 + 2;
		for (int j = i - 1; j >= 0; j--)
			while (ranP[i] == ranP[j]) {
				ranP[i] = rand() % 104 + 2;
				j = i - 1;
			}
		zombieVec.push_back(Enemy(ResourceManager::GetInstance()->RequestTexture("zombie4"), sf::Vector2u(6, 4), 0.13f, 106.48f, sf::Vector2f(platformP[ranP[i]] + 50.0f, platforms[ranP[i]].GetPosition().y - platforms[ranP[i]].GetSize().y)));
		textHp.text.setPosition(zombieVec[i].GetPosition().x, zombieVec[i].GetPosition().y - 60);
		textHp.text.setString(std::to_string(zombieHp[i]));
		textHpVec.push_back(textHp);
	}
	int zombieWalk[80];
	for (int i = 0; i < 80; i++)
		zombieWalk[i] = 0;

	/**********************************score coin************************************/
	int goldCoin = 80, silverCoin = 80, bronzeCoin = 80, chest = 25, level = 4;
	TextBar textBar(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, playerNum);

	/************************TextDisplay**************************/
	std::vector<TextDisplay> textArray, textBossVec;
	TextDisplay text_dm, text_boss;

	bool touchBigchest = false, p = false, bossDead = false, shootBoss = false, gameOver = false, playerDead = false;
	float timer = 0.0f, Chesttimer = 0.0f, BlinkTime = 0.0f, OverTime = 0.0f, BossDieTime = 0.0f;
	float deltaTime = 0.0f;
	sf::Clock clock, clockTimer, clockChest, clockPlayer, clockOver, clockBossDie;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.key.code == sf::Keyboard::Escape)
				GameOver(window, 4);
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//ResizeVeiw(window, view);
				break;
			}
		}

		/************position*************/
		if (player.GetPosition().x + 25 > VIEW_WIDTH / 2)
			position.x = player.GetPosition().x + 25;
		else
			position.x = VIEW_WIDTH / 2;
		if (player.GetPosition().y + 25 < VIEW_HEIGHT / 2)
			position.y = player.GetPosition().y + 25;
		else
			position.y = VIEW_HEIGHT / 2;
		gameView.setCenter(position);

		/******************Update player********************/
		if (heart > 0)
			player.Update(deltaTime);

		/**********************CLOCK************************/
		timer += clockTimer.restart().asSeconds();
		Chesttimer += clockChest.restart().asSeconds();
		BlinkTime += clockPlayer.restart().asSeconds();
		OverTime += clockOver.restart().asSeconds();
		BossDieTime += clockBossDie.restart().asSeconds();

		/************************CHECK / UPDATE ZOMBIE*********************************/
		if (heart > 0)
		for (int i = 0; i < zombieVec.size(); i++) {
			if ((abs(player.GetPosition().y - zombieVec[i].GetPosition().y) <= 10.0f) && (abs(player.GetPosition().x - zombieVec[i].GetPosition().x) <= 120.0f)) {
				if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
					zombieWalk[i] = 5;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else {
					zombieWalk[i] = 4;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
			}
			else if ((abs(player.GetPosition().y - zombieVec[i].GetPosition().y) <= 10.0f) && (abs(player.GetPosition().x - zombieVec[i].GetPosition().x) <= 300.0f)) {
				if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
					zombieWalk[i] = 3;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else {
					zombieWalk[i] = 2;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
			}
			else {
				if (zombieVec[i].GetPosition().x > platforms[ranP[i]].GetPosition().x + platforms[ranP[i]].GetSize().x / 2.2f) {
					zombieWalk[i] = 0;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				else if (zombieVec[i].GetPosition().x < platforms[ranP[i]].GetPosition().x - platforms[ranP[i]].GetSize().x / 2.2f) {
					zombieWalk[i] = 1;
					zombieVec[i].Update(deltaTime, zombieWalk[i]);
				}
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
			}
			textHpVec[i].updateZombie(zombieVec[i]);

			/*************************Check player kill zombie********************************************/
			if (player.BulletIsCollisionWithEnermy(zombieVec[i]))
			{
				sound[4].play();
				timer = 0.0f;
				Boom.setPos(zombieVec[i].GetPosition());
				text_dm.text.setString(std::to_string(damageZombie));
				text_dm.text.setPosition(zombieVec[i].GetPosition().x, zombieVec[i].GetPosition().y - 30.f);
				textArray.push_back(text_dm);
				zombieHp[i] -= damageZombie;
				textHpVec[i].text.setString(std::to_string(zombieHp[i]));
				if (zombieHp[i] <= 0) {
					StoneVec[i].setPos(zombieVec[i].GetPosition());
					zombieDie.setPos(zombieVec[i].GetPosition());
					zombieVec[i].setPos({ 422234, 423432 });
				}

				if (player.GetPosition().x >= zombieVec[i].GetPosition().x) {
					zombieVec[i].move(sf::Vector2f(-10, 0));
				}
				else {
					zombieVec[i].move(sf::Vector2f(10, 0));
				}
			}
			/**************************player Collision With Zombie**********************************/
			if (BlinkTime > 3.f) {
				if (player.isCollisionWithZombie(zombieVec[i]))
				{
					sound[3].play();
					BlinkTime = 0.0f;
					if (player.GetPosition().x >= zombieVec[i].GetPosition().x)
						player.setPos({ player.GetPosition().x + 100.f, player.GetPosition().y });
					else
						player.setPos({ player.GetPosition().x - 100.f, player.GetPosition().y });
					if (armor > 0) {
						armor -= 1;
						text_dm.text.setString("ARMOR -1");
						text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
						textArray.push_back(text_dm);
					}
					else {
						heart -= 1;
						text_dm.text.setString("HEART -1");
						text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
						textArray.push_back(text_dm);
					}
				}
			}
		}
		else /*******************UPDATE zombie (Heart <= 0)**************************/
			for (int i = 0; i < zombieVec.size(); i++) {
				zombieVec[i].Update(deltaTime, zombieWalk[i]);
				textHpVec[i].updateZombie(zombieVec[i]);
			}

		/**********************set condition***************************/
		player.Text.setString(std::to_string(heart));
		if (player.GetPosition().y > VIEW_HEIGHT) {
			BlinkTime = 0.0f;
			player.setPos({ player.GetPosition().x - 200, 500 });
			heart -= 1;
			text_dm.text.setString("HEART -1");
			text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
			textArray.push_back(text_dm);
			sound[0].play();
		}
		for (int i = 0; i < textArray.size(); i++)
			if (textArray[i].destroy)
				textArray.erase(textArray.begin());

		/***************Update Item************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			coinGoldVec[i].Update(deltaTime);
		for (int i = 0; i < coinSilverVec.size(); i++)
			coinSilverVec[i].Update(deltaTime);
		for (int i = 0; i < coinBronzeVec.size(); i++)
			coinBronzeVec[i].Update(deltaTime);
		for (int i = 0; i < ChestVec.size(); i++)
			ChestVec[i].Update(deltaTime);
		for (int i = 0; i < HeartVec.size(); i++)
			HeartVec[i].Update(deltaTime);
		for (int i = 0; i < ArmorVec.size(); i++)
			ArmorVec[i].Update(deltaTime);
		for (int i = 0; i < Boxs.size(); i++)
			Boxs[i].Update(deltaTime);

		/***************************DEBUG Random ITEM*******************************************/
			for (Item& coinGold : coinGoldVec) {
				while (coinGold.GetPosition().y > 540.0f && coinGold.GetPosition().x < 25000.0f)
					coinGold.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
			}
		for (Item& coinSilver : coinSilverVec) {
			while (coinSilver.GetPosition().y > 540.0f && coinSilver.GetPosition().x < 25000.0f)
				coinSilver.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinBronze : coinBronzeVec) {
			while (coinBronze.GetPosition().y > 540.0f && coinBronze.GetPosition().x < 25000.0f)
				coinBronze.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& chest : ChestVec) {
			while (chest.GetPosition().y > 540.0f && chest.GetPosition().x < 25000.0f)
				chest.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& heart : HeartVec) {
			while (heart.GetPosition().y > 540.0f && heart.GetPosition().x < 25000.0f)
				heart.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& armor : ArmorVec) {
			while (armor.GetPosition().y > 540.0f && armor.GetPosition().x < 25000.0f)
				armor.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}

		/******************************Oncollision with Platform*********************************/
		sf::Vector2f direction;
		for (Platform& platform : platforms) {
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
			player.BulletIsCollisionWithPlatform(platform);
			boss.BulletIsCollisionWithPlatform(platform);
			if (platform.GetCollider().CheckCollision(playerDie.GetCollider(), direction, 1.0f))
				playerDie.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(zombieDie.GetCollider(), direction, 1.0f))
				zombieDie.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(bigChest.GetCollider(), direction, 1.0f))
				bigChest.OnCollision(direction);
			for (Enemy& zombie : zombieVec) {
				if (platform.GetCollider().CheckCollision(zombie.GetCollider(), direction, 1.0f))
					zombie.OnCollision(direction);
			}
			for (Item& coinGold : coinGoldVec) {
				if (platform.GetClash().CheckClash(coinGold.GetClash(), direction, 1.0f))
					coinGold.OnCollision(direction);
			}
			for (Item& coinSilver : coinSilverVec) {
				if (platform.GetClash().CheckClash(coinSilver.GetClash(), direction, 1.0f))
					coinSilver.OnCollision(direction);
			}
			for (Item& coinBronze : coinBronzeVec) {
				if (platform.GetClash().CheckClash(coinBronze.GetClash(), direction, 1.0f))
					coinBronze.OnCollision(direction);
			}
			for (Item& chest : ChestVec) {
				if (platform.GetClash().CheckClash(chest.GetClash(), direction, 1.0f))
					chest.OnCollision(direction);
			}
			for (Item& heart : HeartVec) {
				if (platform.GetClash().CheckClash(heart.GetClash(), direction, 1.0f))
					heart.OnCollision(direction);
			}
			for (Item& armor : ArmorVec) {
				if (platform.GetClash().CheckClash(armor.GetClash(), direction, 1.0f))
					armor.OnCollision(direction);
			}
			for (Item& opject : Boxs) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
			for (Opject& opject : OpjectVec) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
		}
		for (Item& box : Boxs) {
			if (player.BulletIsCollisionWithBox(box)) {
				box.setPos({ 42356, 45623 });
			}
			if (box.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
		}
		/***************************Boss onconllision with platform 0-29*******************************************************/
		for (int i = 0; i < 29; i++) {
			if (platforms[i].GetCollider().CheckCollision(boss.GetCollider(), direction, 1.0f))
				boss.OnCollision(direction);
			if (platforms[i].GetCollider().CheckCollision(bossDie.GetCollider(), direction, 1.0f))
				bossDie.OnCollision(direction);
		}

		/**************************item logic & score item****************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			if (player.isCollisionWithItem(coinGoldVec[i]))
			{
				coinGoldVec[i].setPos({ 422234, 423432 });
				score += 3;
				goldCoin -= 1;
			}
		for (int i = 0; i < coinSilverVec.size(); i++)
			if (player.isCollisionWithItem(coinSilverVec[i]))
			{
				coinSilverVec[i].setPos({ 422234, 423432 });
				score += 2;
				silverCoin -= 1;
			}
		for (int i = 0; i < coinBronzeVec.size(); i++)
			if (player.isCollisionWithItem(coinBronzeVec[i]))
			{
				coinBronzeVec[i].setPos({ 422234, 423432 });
				score++;
				bronzeCoin -= 1;
			}
		for (int i = 0; i < StoneVec.size(); i++)
			if (player.isCollisionWithItem(StoneVec[i]))
			{
				StoneVec[i].setPos({ 422234, 423432 });
				score += 3;
			}
		for (Item& Chest : ChestVec)
			if (player.isCollisionWithItem(Chest))
			{
				Chesttimer = 0.f;
				ChestOpen.setPos(Chest.GetPosition());
				Chest.setPos({ 422234, 423432 });
				score += 5;
				chest -= 1;
			}
		if (Chesttimer > 2)
			ChestOpen.setPos({ 422234, 423432 });

		for (int i = 0; i < HeartVec.size(); i++)
			if (player.isCollisionWithItem(HeartVec[i]))
			{
				HeartVec[i].setPos({ 422234, 423432 });
				heart += 1;
			}
		for (int i = 0; i < ArmorVec.size(); i++)
			if (player.isCollisionWithItem(ArmorVec[i]))
			{
				ArmorVec[i].setPos({ 422234, 423432 });
				armor += 1;
			}

		/********************************Check BOSS / Big Chest********************************************/
		bigChest.Update(deltaTime);
		if (chest <= 0 && touchBigchest == false)
		{
			bigChest.setPos(sf::Vector2f(18000.0f, 450.0f));
			/*if (p == false) {
			player.setPos(sf::Vector2f(17500.0f, 450.0f));
			p = true;
			}**/
			if (player.isCollisionWithItem(bigChest)) {
				sound[2].play();
				score += 50;
				bigChest.setPos({ 422234, 423432 });
				boss.setPos(sf::Vector2f(18200.0f, 100.0f));
				touchBigchest = true;
			}
		}

		if (touchBigchest == true) {
			boss.Update(deltaTime, player);
		}

		if (bossHp <= 0 && bossDead == false) {
			BossDieTime = 0.0f;
			bossDie.setPos(boss.GetPosition());
			boss.setPos({ 42324, 43214 });
			bossDead = true;
			bossDie.Update(deltaTime, player);
		}

		else if (bossDead == true)
			bossDie.Update(deltaTime, player);

		/***************************Boss Attack player*******************************************/
		if (BlinkTime > 3.f) {
			if (boss.BulletIsCollisionWithPlayer(player))
			{
				sound[0].play();
				sound[1].play();
				BlinkTime = 0.0f;
				boss.BulletIsCollisionWithPlayer(player);
				heart -= 1;
				text_dm.text.setString("HEART -1");
				text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
				textArray.push_back(text_dm);
			}
			if (player.getGlobalBounds().intersects(boss.getGlobalBounds()))
			{
				BlinkTime = 0.0f;
				if (player.GetPosition().x < boss.GetPosition().x)
					player.move(sf::Vector2f(-200, 0));
				else
					player.move(sf::Vector2f(200, 0));

				heart -= 1;
				text_dm.text.setString("HEART -1");
				text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
				textArray.push_back(text_dm);
			}
		}

		/*************************Player Blink**************************************/
		if (BlinkTime< 0.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 0.5f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 0.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 1.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 1.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 1.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 1.75f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 2.f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 2.25f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else if (BlinkTime < 2.50f)
			player.setFillColor(sf::Color(255, 255, 255, 250));
		else if (BlinkTime < 3.0f)
			player.setFillColor(sf::Color(255, 255, 255, 150));
		else
			player.setFillColor(sf::Color(255, 255, 255, 255));


		/*************************Check Player shoot boss****************************/
		if (CheckShootBoss(player, boss) == 1) {
			sound[1].play();
			sound[4].play();
			shootBoss = true;
			player.vbulletR.erase(player.vbulletR.begin());
		}
		else if (CheckShootBoss(player, boss) == 2) {
			sound[1].play();
			sound[4].play();
			shootBoss = true;
			player.vbulletL.erase(player.vbulletL.begin());
		}

		if (shootBoss == true)
		{
			text_boss.text.setString(std::to_string(damageZombie));
			text_boss.text.setPosition(boss.GetPosition().x, boss.GetPosition().y - 60.f);
			textBossVec.push_back(text_boss);
			bossHp -= damageZombie;
			printf("%i\n", bossHp);
			shootBoss = false;
		}
		for (TextDisplay& text : textBossVec)
			text.update();
		for (int i = 0; i < textBossVec.size(); i++)
			if (textBossVec[i].destroy)
				textBossVec.erase(textBossVec.begin());
		textBossHp.updateBoss(boss);
		textBossHp.text.setString(std::to_string(bossHp));

		/*****************************Show score***************************************/
		textBar.Update(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, position);

		/***********************Update Effect*****************************/
		ChestOpen.Update(deltaTime, player);
		playerDie.Update(deltaTime, player);
		zombieDie.Update(deltaTime, player);
		Boom.Update(deltaTime, player);
		for (Opject& opject : OpjectVec)
			opject.Update(deltaTime);
		if (timer > 1) {
			zombieDie.setPos({ 422234, 423432 });
			Boom.setPos({ 422234, 423432 });
		}
		for (TextDisplay& text : textArray) {
			text.update();
		}

		/*********************Heart <= 0 / Player dead******************/
		if (heart <= 0 && playerDead == false) {
			OverTime = 0.0f;
			playerDie.setPos(player.GetPosition());
			gameOver = true;
			playerDead = true;
		}

		/************************************NEXT**************************/
		if (OverTime > 3 && gameOver == true)
			GameOver(window, 4);
		if (bossDead == true && BossDieTime > 3)
			LevelUp(window, 4);

		/***************************Window DRAW**********************************/
		bg.Draw(window);
		window.setView(gameView);
		platform_water(window, 9);

		for (Opject& opject : OpjectVec)
			opject.Draw(window);
		for (Item& box : Boxs)
			box.Draw(window);
		for (Item& chest : ChestVec)
			chest.Draw(window);
		for (Item& coin : coinGoldVec)
			coin.Draw(window);
		for (Item& coin : coinSilverVec)
			coin.Draw(window);
		for (Item& coin : coinBronzeVec)
			coin.Draw(window);
		for (Item& heart : HeartVec)
			heart.Draw(window);
		for (Item& armor : ArmorVec)
			armor.Draw(window);
		for (Item& stone : StoneVec)
			stone.Draw(window);
		for (Platform& platform : platforms)
			platform.Draw(window);
		for (Enemy& zombie : zombieVec)
			zombie.Draw(window);
		bigChest.Draw(window);
		boss.Draw(window);
		zombieDie.Draw(window);
		playerDie.Draw(window);
		textBossHp.Draw(window);
		if (heart > 0)
			player.Draw(window);
		for (TextDisplay& text : textArray)
			text.Draw(window);
		for (TextDisplay& text : textBossVec)
			text.Draw(window);
		ChestOpen.Draw(window);
		for (TextHp& textHp : textHpVec)
			textHp.Draw(window);
		bossDie.Draw(window);
		Boom.Draw(window);
		textBar.Draw(window);
		Myname(window, sf::Vector2f(position.x, position.y + 230));
		window.display();
		window.clear();
	}
}

void GameBonus(sf::RenderWindow & window)
{
	sf::View gameView;
	gameView.reset(sf::FloatRect(0.0f, 0.0f, VIEW_WIDTH, VIEW_HEIGHT));

	sf::Vector2f position(VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
	background bg(5);

	/************************SET SOUND EFFECT*************************/
	sf::SoundBuffer buffer, buffer2;
	sf::Sound sound, sound2;
	buffer.loadFromFile("Sound/Tick-Tock-Game-.ogg");
	buffer2.loadFromFile("Sound/clock-tick1.ogg");
	sound.setBuffer(buffer);
	sound2.setBuffer(buffer2);
	sound.play();

	/***********************player / Enemy*****************************/
	Player player(&playerTexture, sf::Vector2u(10, 5), 0.07f, 347.2875f, 300.0f, 4);

	/****************************BOSS********************************/
	Item bigChest(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, sf::Vector2f(120.0f, 80.0f), sf::Vector2f(20000.0f, rand() % 500));

	/**********************Effect***********************/
	Effect ChestOpen(ResourceManager::GetInstance()->RequestTexture("chest"), sf::Vector2u(3, 1), 0.6f, 2);

	/******************************coin*******************************************/
	std::vector<Item> coinGoldVec, coinSilverVec, coinBronzeVec;
	int randCoin[300];
	for (int i = 0; i < 300; i++)
	{
		randCoin[i] = (rand() % 410) * 40 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randCoin[i] == randCoin[j]) {
				randCoin[i] = (rand() % 410) * 40 + 250;
				j = i - 1;
			}
	}
	for (int i = 0; i < 100; i++)
	{
		coinGoldVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinGold"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i], rand() % 400)));
		coinSilverVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinSilver"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i + 50], rand() % 400)));
		coinBronzeVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("coinBronze"), sf::Vector2u(10, 1), 0.05f, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(randCoin[i + 100], rand() % 400)));
	}

	/******************************TEASURE CHEST******************************************/
	std::vector<Item> ChestVec;
	int randChest[30];
	for (int i = 0; i < 30; i++)
	{
		randChest[i] = (rand() % 250) * 70 + 250;
		for (int j = i - 1; j >= 0; j--)
			while (randChest[i] == randChest[j]) {
				randChest[i] = (rand() % 250) * 70 + 250;
				j = i - 1;
			}
		ChestVec.push_back(Item(ResourceManager::GetInstance()->RequestTexture("chestClosed"), sf::Vector2u(1, 1), 0.6f, sf::Vector2f(60.0f, 40.0f), sf::Vector2f(randChest[i], rand() % 400)));
	}

	/***********************************OPJECT*******************************************************/
	std::vector<Item> Boxs;
	for (int i = 0; i < 50; i++) {
		Boxs.push_back(Item(ResourceManager::GetInstance()->RequestTexture("crate"), sf::Vector2u(1, 1), 0.0f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(((rand() % 450) * 40) + 200, rand() % 540)));
	}
	std::vector<Opject> OpjectVec;
	for (int i = 0; i < 30; i++) {
		OpjectVec.push_back(Opject(3, sf::Vector2f(60.0f, 60.0f), sf::Vector2f(((rand() % 300) * 60) + 200, rand() % 540)));
		OpjectVec.push_back(Opject(4, sf::Vector2f(40.0f, 60.0f), sf::Vector2f(((rand() % 420) * 40) + 200, rand() % 540)));
	}

	/******************************platform Level 5******************************************/
	std::vector<Platform> platforms;

	float px = 0.0f, count = 0.0f, hole = 0.0f;
	for (int i = 0; i < 29; i++)
	{
		platforms.push_back(Platform(1, sf::Vector2f(640.0f, 64.0f), sf::Vector2f(320.0f + px + hole, 520.0f)));
		px += 600.0f;
		if (i % 4 == 0 && i != 0)
			hole += 200.0f;
	}
	for (int i = 0; i < 7; i++)
	{
		platforms.push_back(Platform(4, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(100.0f + count, 250.0f)));
		platforms.push_back(Platform(5, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(300.0f + count, 90.0f)));
		platforms.push_back(Platform(2, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(360.0f + count, 390.0f)));
		platforms.push_back(Platform(7, sf::Vector2f(420.0f, 38.5f), sf::Vector2f(750.0f + count, 380.0f)));
		platforms.push_back(Platform(2, sf::Vector2f(160.0f, 38.5f), sf::Vector2f(650.0f + count, 100.0f)));
		platforms.push_back(Platform(4, sf::Vector2f(260.0f, 38.5f), sf::Vector2f(1000.0f + count, 230.0f)));
		platforms.push_back(Platform(8, sf::Vector2f(470.0f, 38.5f), sf::Vector2f(1250.0f + count, 80.0f)));
		platforms.push_back(Platform(3, sf::Vector2f(210.0f, 38.5f), sf::Vector2f(1450.0f + count, 360.0f)));
		platforms.push_back(Platform(6, sf::Vector2f(370.0f, 38.5f), sf::Vector2f(1800.0f + count, 200.0f)));
		platforms.push_back(Platform(5, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2000.0f + count, 350.0f)));
		platforms.push_back(Platform(5, sf::Vector2f(310.0f, 38.5f), sf::Vector2f(2300.0f + count, 210.0f)));
		count += 2500;
	}
	

	/**********************************score coin************************************/
	int goldCoin = 100, silverCoin = 100, bronzeCoin = 100, chest = 30, level = 5;
	TextBar textBar(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, playerNum);
	/************************TextDisplay**************************/
	std::vector<TextDisplay> textArray;
	TextDisplay text_dm;

	sf::Font font;
	font.loadFromFile("Font/Font0.ttf");

	bool t = false, p = false, z = false, shootBoss = false, timeOut = false;
	float timer = 0, Chesttimer = 0.0f, bonusTime = 30.0f, y = 0;
	sf::Text textBobusTime;
	float deltaTime = 0.0f;
	sf::Clock clock, clockTime;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.key.code == sf::Keyboard::Escape)
				GameOver(window, 1);
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//ResizeVeiw(window, view);
				break;
			}
		}

		/************position*************/
		if (player.GetPosition().x + 25 > VIEW_WIDTH / 2)
			position.x = player.GetPosition().x + 25;
		else
			position.x = VIEW_WIDTH / 2;
		if (player.GetPosition().y + 25 < VIEW_HEIGHT / 2)
			position.y = player.GetPosition().y + 25;
		else
			position.y = VIEW_HEIGHT / 2;
		gameView.setCenter(position);

		/******************************CLOCK*********************************/
		timer += clockTime.restart().asSeconds();
		Chesttimer += clock.restart().asSeconds();
		/*********************Count Time************************************/	
		textBobusTime.setFont(font);
		textBobusTime.setCharacterSize(160);
		textBobusTime.setOrigin({ textBobusTime.getLocalBounds().width/2, textBobusTime.getLocalBounds().height });
		textBobusTime.setFillColor(sf::Color::White);
		textBobusTime.setOutlineThickness(3.0f);
		textBobusTime.setPosition(position.x, position.y - 80.0f - y);

		if (timer <= 3.0f) {
			textBobusTime.setString("BONUS TIME");
			player.UpdateBonusTime(deltaTime);
		}
		else if (timer <= 8) {
			textBobusTime.setString(std::to_string(int(9 - timer)));
			player.UpdateBonusTime(deltaTime);
		}
		else if (timer <= 9) {
			textBobusTime.setString("START");
			player.UpdateBonusTime(deltaTime);
		}
		else if (timer <= 39) {
			textBobusTime.setString(std::to_string(int(bonusTime - timer + 10)));
			y = 120.0f;
			textBobusTime.setCharacterSize(100);
			player.Update(deltaTime);
		}
		else if (timer <= 42) {
			textBobusTime.setString("TIME OUT");
			y = 0.0f;
			textBobusTime.setCharacterSize(160);
			player.UpdateBonusTime(deltaTime);
			sound.stop();
		}
		else
			LevelUp(window, 5);
		/**********************set condition***************************/
		player.Text.setString(std::to_string(heart));
		if (player.GetPosition().y > VIEW_HEIGHT) {
			player.setPos({ player.GetPosition().x - 200, 500 });
			heart -= 1;
			text_dm.text.setString("HEART -1");
			text_dm.text.setPosition(player.GetPosition().x, player.GetPosition().y - 30.f);
			textArray.push_back(text_dm);
		}
		for (int i = 0; i < textArray.size(); i++)
			if (textArray[i].destroy)
				textArray.erase(textArray.begin());

		/***************Update Item************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			coinGoldVec[i].Update(deltaTime);
		for (int i = 0; i < coinSilverVec.size(); i++)
			coinSilverVec[i].Update(deltaTime);
		for (int i = 0; i < coinBronzeVec.size(); i++)
			coinBronzeVec[i].Update(deltaTime);
		for (int i = 0; i < ChestVec.size(); i++)
			ChestVec[i].Update(deltaTime);
		for (int i = 0; i <Boxs.size(); i++)
			Boxs[i].Update(deltaTime);

		/***************************DEBUG Random ITEM*******************************************/
		for (Item& coinGold : coinGoldVec) {
			while (coinGold.GetPosition().y > 540.0f && coinGold.GetPosition().x < 25000.0f)
				coinGold.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinSilver : coinSilverVec) {
			while (coinSilver.GetPosition().y > 540.0f && coinSilver.GetPosition().x < 25000.0f)
				coinSilver.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& coinBronze : coinBronzeVec) {
			while (coinBronze.GetPosition().y > 540.0f && coinBronze.GetPosition().x < 25000.0f)
				coinBronze.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}
		for (Item& chest : ChestVec) {
			while (chest.GetPosition().y > 540.0f && chest.GetPosition().x < 25000.0f)
				chest.setPos(sf::Vector2f(rand() % 18000, rand() % 400));
		}

		/***************Oncollision****************************/
		sf::Vector2f direction;
		for (Platform& platform : platforms) {
			player.BulletIsCollisionWithPlatform(platform);
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);
			if (platform.GetCollider().CheckCollision(bigChest.GetCollider(), direction, 1.0f))
				bigChest.OnCollision(direction);
			for (Item& coinGold : coinGoldVec) {
				if (platform.GetClash().CheckClash(coinGold.GetClash(), direction, 1.0f))
					coinGold.OnCollision(direction);
			}
			for (Item& coinSilver : coinSilverVec) {
				if (platform.GetClash().CheckClash(coinSilver.GetClash(), direction, 1.0f))
					coinSilver.OnCollision(direction);
			}
			for (Item& coinBronze : coinBronzeVec) {
				if (platform.GetClash().CheckClash(coinBronze.GetClash(), direction, 1.0f))
					coinBronze.OnCollision(direction);
			}
			for (Item& chest : ChestVec) {
				if (platform.GetClash().CheckClash(chest.GetClash(), direction, 1.0f))
					chest.OnCollision(direction);
			}
			for (Item& box : Boxs) {
				if (platform.GetCollider().CheckCollision(box.GetCollider(), direction, 1.0f))
					box.OnCollision(direction);
			}
			for (Opject& opject : OpjectVec) {
				if (platform.GetCollider().CheckCollision(opject.GetCollider(), direction, 1.0f))
					opject.OnCollision(direction);
			}
		}
		for (Item& box : Boxs) {
			if (box.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
				player.OnCollision(direction);

			if (player.BulletIsCollisionWithBox(box)) {
				box.setPos({ 42356, 45623 });
			}
		}

		/**************************item logic & score item****************************/
		for (int i = 0; i < coinGoldVec.size(); i++)
			if (player.isCollisionWithItem(coinGoldVec[i]))
			{
				coinGoldVec[i].setPos({ 422234, 423432 });
				score += 3;
				goldCoin -= 1;
			}
		for (int i = 0; i < coinSilverVec.size(); i++)
			if (player.isCollisionWithItem(coinSilverVec[i]))
			{
				coinSilverVec[i].setPos({ 422234, 423432 });
				score += 2;
				silverCoin -= 1;
			}
		for (int i = 0; i < coinBronzeVec.size(); i++)
			if (player.isCollisionWithItem(coinBronzeVec[i]))
			{
				coinBronzeVec[i].setPos({ 422234, 423432 });
				score++;
				bronzeCoin -= 1;
			}
		for (Item& Chest : ChestVec)
			if (player.isCollisionWithItem(Chest))
			{
				Chesttimer = 0.f;
				ChestOpen.setPos(Chest.GetPosition());
				Chest.setPos({ 422234, 423432 });
				score += 5;
				chest -= 1;
			}
		if (Chesttimer > 0.0001)
			ChestOpen.setPos({ 422234, 423432 });

		/*****************************Show score***************************************/
		textBar.Update(score, heart, armor, goldCoin, silverCoin, bronzeCoin, chest, level, position);
			
		/***********************Update Effect*****************************/
		ChestOpen.Update(deltaTime, player);
		for (Opject& opject : OpjectVec)
			opject.Update(deltaTime);
	
		for (TextDisplay& text : textArray) {
			text.update();
		}
		/*********************set position bar*******************/
		if (heart <= 0) {
			sound.stop();
			GameOver(window, 5);
		}

		bg.Draw(window);
		window.setView(gameView);
		platform_water(window, 9);

		for (Opject& opject : OpjectVec)
			opject.Draw(window);
		for (Item& box : Boxs)
			box.Draw(window);
		for (Item& chest : ChestVec)
			chest.Draw(window);
		for (Item& coin : coinGoldVec)
			coin.Draw(window);
		for (Item& coin : coinSilverVec)
			coin.Draw(window);
		for (Item& coin : coinBronzeVec)
			coin.Draw(window);
		
		for (Platform& platform : platforms)
			platform.Draw(window);
		bigChest.Draw(window);
		player.Draw(window);
		for (TextDisplay& text : textArray)
			text.Draw(window);
		ChestOpen.Draw(window);
		textBar.Draw(window);
		window.draw(textBobusTime);
		Myname(window, sf::Vector2f(position.x, position.y + 230));
		window.display();
		window.clear();
	}
}

void Menu(sf::RenderWindow & window)
{
	/*sf::Music music;
	music.openFromFile("Sound/Lost-Jungle.ogg");
	music.setLoop(true);
	music.play();*/

	sf::SoundBuffer buffer;
	sf::Sound sound;
	buffer.loadFromFile("Sound/cackle3.ogg");
	sound.setBuffer(buffer);

	sf::RectangleShape menuBg, Mode[5], buttonMode, buttonMode1;
	menuBg.setSize(sf::Vector2f(960.0f, 540.0f));
	for (int i = 0; i<5; i++)
		Mode[i].setSize(sf::Vector2f(960.0f, 540.0f));
	menuBg.setTexture(ResourceManager::GetInstance()->RequestTexture("menuBg"));
	Mode[0].setTexture(ResourceManager::GetInstance()->RequestTexture("mode0"));
	Mode[1].setTexture(ResourceManager::GetInstance()->RequestTexture("mode1"));
	Mode[2].setTexture(ResourceManager::GetInstance()->RequestTexture("mode2"));
	Mode[3].setTexture(ResourceManager::GetInstance()->RequestTexture("mode3"));
	Mode[4].setTexture(ResourceManager::GetInstance()->RequestTexture("mode4"));

	sf::Vector2i mouse;

	score = 0, heart = 3, armor = 0;
	int mode = 0, count = 0;
	bool Pressed[5];
	//int play = 0;

	while (window.isOpen())
	{
		while (mode == 0)
		{
			mouse = sf::Mouse::getPosition(window);
			sf::Event menuEvent;
			while (window.pollEvent(menuEvent))
			{			
				switch (menuEvent.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					//ResizeVeiw(window, view);
					break;
				case sf::Event::MouseButtonPressed:
					if (menuEvent.mouseButton.button == sf::Mouse::Left)
					{
						if (mouse.x > window.getSize().x / 2.5f && mouse.x < window.getSize().x / 1.67f && mouse.y > window.getSize().y / 2.84f && mouse.y < window.getSize().y / 2.11f) {
							mode = 1;
							sound.play();
						}
						else if (mouse.x > window.getSize().x / 2.92f && mouse.x < window.getSize().x / 1.52f && mouse.y > window.getSize().y / 1.96f && mouse.y < window.getSize().y / 1.58f) {
							mode = 2;
							sound.play();
						}
						else if (mouse.x > window.getSize().x / 2.92f && mouse.x < window.getSize().x / 1.52f && mouse.y > window.getSize().y / 1.49f && mouse.y < window.getSize().y / 1.26f) {
							mode = 3;
							sound.play();
						}
						else if (mouse.x > window.getSize().x / 1.11f && mouse.x < window.getSize().x / 1.04f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f) {
							window.close();
							mode = 4;
							sound.play();
						}
					}
				}
			}

			window.clear();
			window.draw(menuBg);

			if (mouse.x > window.getSize().x / 2.5f && mouse.x < window.getSize().x / 1.67f && mouse.y > window.getSize().y / 2.84f && mouse.y < window.getSize().y / 2.11f) 
				window.draw(Mode[1]);
			else if (mouse.x > window.getSize().x / 2.92f && mouse.x < window.getSize().x / 1.52f && mouse.y > window.getSize().y / 1.96f && mouse.y < window.getSize().y / 1.58f)
				window.draw(Mode[2]);
			else if (mouse.x > window.getSize().x / 2.92f && mouse.x < window.getSize().x / 1.52f && mouse.y > window.getSize().y / 1.49f && mouse.y < window.getSize().y / 1.26f)
				window.draw(Mode[3]);
			else if (mouse.x > window.getSize().x / 1.11f && mouse.x < window.getSize().x / 1.04f && mouse.y > window.getSize().y / 1.2f && mouse.y < window.getSize().y / 1.06f)
				window.draw(Mode[4]);
			else
				window.draw(Mode[0]);

			//printf("mode = %d \n", mode);
			
			Myname(window, sf::Vector2f(480, 490));

			window.setView(window.getDefaultView());
			window.display();
			if (mode == 1)
			{
				ChoosePlayer(window);
			}
			else if (mode == 2)
			{
				HowToPlay(window);
			}
			else if (mode == 3)
			{
				Scoreboard(window);
			}
		}
	}
}

int CheckShootBoss(Player player, Boss boss)
{
	for (int i = 0; i < player.vbulletR.size(); i++)
		if (player.vbulletR[i].getGlobalBounds().intersects(boss.getGlobalBounds()))
			if (abs(player.vbulletR[i].getPosition().x - boss.GetPosition().x) < 40.0f)
			{
				player.vbulletR.erase(player.vbulletR.begin() + i);
				return 1;
			}
	for (int i = 0; i < player.vbulletL.size(); i++)
		if (player.vbulletL[i].getGlobalBounds().intersects(boss.getGlobalBounds()))
			if (abs(player.vbulletL[i].getPosition().x - boss.GetPosition().x) < 40.0f)
			{
				player.vbulletL.erase(player.vbulletL.begin() + i);
				return 2;
			}
	return 0;
}

void GameOver(sf::RenderWindow& window, int level)
{
	WriteScore();
	sf::SoundBuffer buffer[2];
	sf::Sound sound[2];
	buffer[0].loadFromFile("Sound/CARDDNGR.ogg");
	buffer[1].loadFromFile("Sound/cackle3.ogg");
	sound[0].setBuffer(buffer[0]);
	sound[1].setBuffer(buffer[1]);
	sound[0].play();

	sf::Font font;
	font.loadFromFile("Font/Font0.ttf");
	sf::Text textScore, textLose;
	std::ostringstream ssScore;
	textScore.setFont(font);
	textScore.setCharacterSize(60);
	textScore.setFillColor(sf::Color::Black);
	textScore.setOutlineThickness(3);
	textScore.setOutlineColor(sf::Color::White);

	textLose.setFont(font);
	textLose.setCharacterSize(70);
	textLose.setFillColor(sf::Color::White);
	textLose.setOutlineThickness(5);
	textLose.setString("YOU LOSE");
	textLose.setOrigin(sf::Vector2f(textLose.getGlobalBounds().width / 2, textLose.getGlobalBounds().height / 2));
	textLose.setPosition(sf::Vector2f(480, 200));

	ssScore << "Your Score : " << score;
	textScore.setString(ssScore.str());
	textScore.setOrigin(sf::Vector2f(textScore.getGlobalBounds().width/2, textScore.getGlobalBounds().height/2));
	textScore.setPosition(sf::Vector2f(480, 260));

	sf::RectangleShape Mode[2], bg;
	bg.setSize(sf::Vector2f(960.0f, 945.0f));
	bg.setPosition(0, -405.0f);
	if (level == 1)
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_1"));
	else if (level == 2)
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_2"));
	else if (level == 3)
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_3"));
	else if (level == 4)
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_4"));
	else if (level == 5)
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_5"));

	for (int i = 0; i < 2; i++)
		Mode[i].setSize(sf::Vector2f(960.0f, 540.0f));
	Mode[0].setTexture(ResourceManager::GetInstance()->RequestTexture("GameOver0"));
	Mode[1].setTexture(ResourceManager::GetInstance()->RequestTexture("GameOver1"));

	sf::Vector2i mouse;
	int mode = 0;

	while (mode == 0)
	{
		mouse = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			/*if (event.key.code == sf::Keyboard::Escape)
				Menu(window);*/
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//ResizeVeiw(window, view);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mouse.x > window.getSize().x / 2.32f && mouse.x < window.getSize().x / 1.75f && mouse.y > window.getSize().y / 1.53f && mouse.y < window.getSize().y / 1.29f)
					{
						mode = 1;
						sound[1].play();
					}
				}
			}
		}
		window.clear();
		window.draw(bg);
		if (mouse.x > window.getSize().x / 2.32f && mouse.x < window.getSize().x / 1.75f && mouse.y > window.getSize().y / 1.53f && mouse.y < window.getSize().y / 1.29f)
			window.draw(Mode[1]);
		else
			window.draw(Mode[0]);
		window.draw(textLose);
		window.draw(textScore);
		window.setView(window.getDefaultView());
		Myname(window, sf::Vector2f(480, 490));
		window.display();
		if (mode == 1)
			Scoreboard(window);
	}
}

void LevelUp(sf::RenderWindow & window, int level)
{
	if (level == 5)
	{
		WriteScore();
	}
	sf::SoundBuffer buffer[2];
	sf::Sound sound[2];
	buffer[0].loadFromFile("Sound/ARTHUR.ogg");
	buffer[1].loadFromFile("Sound/cackle3.ogg");
	sound[0].setBuffer(buffer[0]);
	sound[1].setBuffer(buffer[1]);
	sound[0].play();
	
	sf::Font font;
	font.loadFromFile("Font/Font0.ttf");
	sf::Text textScore, textReward;
	std::ostringstream ssScore;
	textScore.setFont(font);
	textScore.setCharacterSize(60);
	textScore.setFillColor(sf::Color::Black);
	textScore.setOutlineThickness(3);
	textScore.setOutlineColor(sf::Color::White);

	textReward.setFont(font);
	textReward.setCharacterSize(40);
	textReward.setOutlineThickness(3);
	textReward.setOutlineColor(sf::Color::Red);

	ssScore << "Your Score : " << score;
	textScore.setString(ssScore.str());
	textScore.setOrigin(sf::Vector2f(textScore.getLocalBounds().width / 2, textScore.getLocalBounds().height / 2));
	textScore.setPosition(sf::Vector2f(480, 220));

	sf::RectangleShape Mode[2], bg;
	bg.setSize(sf::Vector2f(960.0f, 945.0f));
	bg.setPosition(0, -405.0f);
	if (level == 1) {
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_1"));
		heart += 1;
		textReward.setString("Reward : Heart = +1");
	}
	else if (level == 2) {
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_2"));
		heart += 2;
		textReward.setString("Reward : Heart = +2");
	}
	else if (level == 3) {
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_3"));
		heart += 3;
		textReward.setString("Reward : Heart = +3");
	}
	else if (level == 4) {
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_4"));
		score += 100;
		textReward.setString("Reward : Score = +100");
	}
	else if (level == 5)
		bg.setTexture(ResourceManager::GetInstance()->RequestTexture("bg_5"));

	textReward.setOrigin(sf::Vector2f(textReward.getLocalBounds().width / 2, textReward.getLocalBounds().height / 2));
	textReward.setPosition(sf::Vector2f(480, 280));

	for (int i = 0; i < 2; i++)
		Mode[i].setSize(sf::Vector2f(960.0f, 540.0f));
	if (level == 5) {
		Mode[0].setTexture(ResourceManager::GetInstance()->RequestTexture("YouWin0"));
		Mode[1].setTexture(ResourceManager::GetInstance()->RequestTexture("YouWin1"));
	}
	else {
		Mode[0].setTexture(ResourceManager::GetInstance()->RequestTexture("LevelUp0"));
		Mode[1].setTexture(ResourceManager::GetInstance()->RequestTexture("LevelUp1"));
	}

	sf::Vector2i mouse;
	int mode = 0;

	while (mode == 0)
	{
		mouse = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			/*if (event.key.code == sf::Keyboard::Escape)
				Menu(window);*/
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//ResizeVeiw(window, view);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mouse.x > window.getSize().x / 2.47f && mouse.x < window.getSize().x / 1.67f && mouse.y > window.getSize().y / 1.53f && mouse.y < window.getSize().y / 1.29f)
					{
						mode = 1;
						sound[1].play();
					}
				}
			}
		}
		window.clear();
		window.draw(bg);
		if (mouse.x > window.getSize().x / 2.47f && mouse.x < window.getSize().x / 1.67f && mouse.y > window.getSize().y / 1.53f && mouse.y < window.getSize().y / 1.29f)
			window.draw(Mode[1]);
		else
			window.draw(Mode[0]);
		window.draw(textScore);
		window.draw(textReward);
		window.setView(window.getDefaultView());
		Myname(window, sf::Vector2f(480, 490));
		window.display();
		if (mode == 1)
		{
			if (level == 1)
				GameLevel_2(window);
			else if (level == 2)
				GameLevel_3(window);
			else if (level == 3)
				GameLevel_4(window);
			else if (level == 4)
				GameBonus(window);
			else
				Scoreboard(window);
		}
	}

}
