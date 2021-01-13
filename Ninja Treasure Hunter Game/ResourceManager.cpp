#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
	LoadTexture("Texture/Player/Player2.png", "player1");
	LoadTexture("Texture/Player/Player3.png", "player2");
	LoadTexture("Texture/Player/PlayerDie1.png", "player1_die");
	LoadTexture("Texture/Player/PlayerDie2.png", "player2_die");
	LoadTexture("Texture/Zombie/zombie0.png", "zombie0");
	LoadTexture("Texture/Zombie/zombie0_die.png", "zombie0_die");
	LoadTexture("Texture/Zombie/zombie1.png", "zombie1");
	LoadTexture("Texture/Zombie/zombie2.png", "zombie2");
	LoadTexture("Texture/Zombie/zombie3.png", "zombie3");
	LoadTexture("Texture/Zombie/zombie4.png", "zombie4");
	LoadTexture("Texture/Zombie/zombie1_die.png", "zombie1_die");
	LoadTexture("Texture/Zombie/zombie2_die.png", "zombie2_die");
	LoadTexture("Texture/Zombie/zombie3_die.png", "zombie3_die");
	LoadTexture("Texture/Zombie/zombie4_die.png", "zombie4_die");

	LoadTexture("Texture/Zombie/boss1.png", "boss1");
	LoadTexture("Texture/Zombie/boss2.png", "boss2");
	LoadTexture("Texture/Zombie/boss3.png", "boss3");
	LoadTexture("Texture/Zombie/boss4.png", "boss4");
	LoadTexture("Texture/Zombie/boss1_die.png", "boss1_die");
	LoadTexture("Texture/Zombie/boss2_die.png", "boss2_die");
	LoadTexture("Texture/Zombie/boss3_die.png", "boss3_die");
	LoadTexture("Texture/Zombie/boss4_die.png", "boss4_die");

	LoadTexture("texture/Item/coin_gold.png", "coinGold");
	LoadTexture("texture/Item/coin_silver.png", "coinSilver");
	LoadTexture("texture/Item/coin_bronze.png", "coinBronze");
	LoadTexture("texture/Item/chest_closed.png", "chestClosed");
	LoadTexture("texture/Item/chest.png", "chest");
	LoadTexture("Texture/item/Heart.png", "heart");
	LoadTexture("Texture/item/Armor.png", "armor");
	
	LoadTexture("Texture/Background/Background1.png", "bg_1");
	LoadTexture("Texture/Background/Background2.png", "bg_2");
	LoadTexture("Texture/Background/Background3.png", "bg_3");
	LoadTexture("Texture/Background/Background4.png", "bg_4");
	LoadTexture("Texture/Background/Background7.png", "bg_5");
	LoadTexture("Texture/Menu/Menu_bg3.png", "menuBg");
	LoadTexture("Texture/Menu/Menu_Button0.png", "mode0");
	LoadTexture("Texture/Menu/Menu_Button1.png", "mode1");
	LoadTexture("Texture/Menu/Menu_Button2.png", "mode2");
	LoadTexture("Texture/Menu/Menu_Button3.png", "mode3");
	LoadTexture("Texture/Menu/Menu_Button4.png", "mode4");
	LoadTexture("Texture/Menu/Menu_bg5.png", "HowToPlayBg");
	LoadTexture("Texture/Menu/How_to_play01.png", "How_to_play01");
	LoadTexture("Texture/Menu/How_to_play11.png", "How_to_play11");
	LoadTexture("Texture/Menu/How_to_play02.png", "How_to_play02");
	LoadTexture("Texture/Menu/How_to_play12.png", "How_to_play12");
	LoadTexture("Texture/Menu/Exit_Button0.png", "Exit0");
	LoadTexture("Texture/Menu/Exit_Button1.png", "Exit1");
	LoadTexture("Texture/Menu/Scoreboard_bg.png", "ScoreboardBg");
	LoadTexture("Texture/Menu/Enter_Name_bg.png", "EnterNameBg");
	LoadTexture("Texture/Menu/EnterName0.png", "EnterName0");
	LoadTexture("Texture/Menu/EnterName1.png", "EnterName1");
	LoadTexture("Texture/Menu/GameOver0.png", "GameOver0");
	LoadTexture("Texture/Menu/GameOver1.png", "GameOver1");
	LoadTexture("Texture/Menu/LevelUp0.png", "LevelUp0");
	LoadTexture("Texture/Menu/LevelUp1.png", "LevelUp1");
	LoadTexture("Texture/Menu/YouWin0.png", "YouWin0");
	LoadTexture("Texture/Menu/YouWin1.png", "YouWin1");
	LoadTexture("Texture/Menu/ChoosePlayer0.png", "ChoosePlayer0");
	LoadTexture("Texture/Menu/ChoosePlayer1.png", "ChoosePlayer1");
	LoadTexture("Texture/Menu/ChoosePlayer2.png", "ChoosePlayer2");

	LoadTexture("texture/Item/Bar1.png", "Bar1");
	LoadTexture("texture/Item/Bar2.png", "Bar2");

	LoadTexture("Texture/Platform/platform1_1.png", "platform1");
	LoadTexture("Texture/Platform/platform1_2.png", "platform2");
	LoadTexture("Texture/Platform/platform1_3.png", "platform3");
	LoadTexture("Texture/Platform/platform1_4.png", "platform4");
	LoadTexture("Texture/Platform/platform1_5.png", "platform5");
	LoadTexture("Texture/Platform/platform1_6.png", "platform6");
	LoadTexture("Texture/Platform/platform1_7.png", "platform7");
	LoadTexture("Texture/Platform/platform1_8.png", "platform8");
	LoadTexture("Texture/Platform/water.png", "water");
	LoadTexture("Texture/Platform/platform2_1.png", "platform2_1");
	LoadTexture("Texture/Platform/platform2_2.png", "platform2_2");
	LoadTexture("Texture/Platform/platform2_3.png", "platform2_3");
	LoadTexture("Texture/Platform/platform2_4.png", "platform2_4");
	LoadTexture("Texture/Platform/platform2_5.png", "platform2_5");
	LoadTexture("Texture/Platform/platform2_6.png", "platform2_6");
	LoadTexture("Texture/Platform/platform2_7.png", "platform2_7");
	LoadTexture("Texture/Platform/platform2_8.png", "platform2_8");

	LoadTexture("Texture/Platform/platform3_1.png", "platform3_1");
	LoadTexture("Texture/Platform/platform3_2.png", "platform3_2");
	LoadTexture("Texture/Platform/platform3_3.png", "platform3_3");
	LoadTexture("Texture/Platform/platform3_4.png", "platform3_4");
	LoadTexture("Texture/Platform/platform3_5.png", "platform3_5");
	LoadTexture("Texture/Platform/platform3_6.png", "platform3_6");
	LoadTexture("Texture/Platform/platform3_7.png", "platform3_7");
	LoadTexture("Texture/Platform/platform3_8.png", "platform3_8");
	LoadTexture("Texture/Platform/Crystal.png", "crystal");

	LoadTexture("Texture/Platform/platform4_1.png", "platform4_1");
	LoadTexture("Texture/Platform/platform4_2.png", "platform4_2");
	LoadTexture("Texture/Platform/platform4_3.png", "platform4_3");
	LoadTexture("Texture/Platform/platform4_4.png", "platform4_4");
	LoadTexture("Texture/Platform/platform4_5.png", "platform4_5");
	LoadTexture("Texture/Platform/platform4_6.png", "platform4_6");
	LoadTexture("Texture/Platform/platform4_7.png", "platform4_7");
	LoadTexture("Texture/Platform/platform4_8.png", "platform4_8");

	LoadTexture("Texture/Platform/Objects2/Bush (2).png", "bush");
	LoadTexture("Texture/Platform/Objects2/ArrowSign.png", "arrow");
	LoadTexture("Texture/Platform/Objects2/TombStone (2).png", "stone");
	LoadTexture("Texture/Platform/Objects2/Tree.png", "tree");
	LoadTexture("Texture/Platform/Objects2/Skeleton.png", "skeleton");
	LoadTexture("Texture/Platform/Objects2/Crate.png", "crate");

	LoadTexture("Texture/item/stone_pink.png", "stone_pink");
	LoadTexture("Texture/item/stone_yellow.png", "stone_yellow");
	LoadTexture("Texture/item/stone_green.png", "stone_green");
	LoadTexture("Texture/item/stone_blue.png", "stone_blue");
	

	LoadTexture("texture/Item/boom3.png", "boom");
}

void ResourceManager::LoadTexture(std::string path, std::string name)
{
	sf::Texture* t = new sf::Texture();
	t->loadFromFile(path);

	textures[name] = t;
}


void ResourceManager::Cleanup()
{
	for (auto item : textures)
	{
		delete item.second;
		item.second = nullptr;
	}
}

ResourceManager::~ResourceManager()
{
}

sf::Texture * ResourceManager::RequestTexture(std::string name)
{
	if (textures[name]) return textures[name];

	return nullptr;
}
