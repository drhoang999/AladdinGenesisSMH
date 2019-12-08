#include "TextureManager.h"

TextureManager* TextureManager::__Instance = NULL;

TextureManager * TextureManager::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new TextureManager();
	return __Instance;
}

void TextureManager::AddTexture(eType type, CTexture *texture)
{
	_ArrTextures[type] = texture;
}

CTexture * TextureManager::GetTexture(eType type)
{
	return _ArrTextures[type];
}

void TextureManager::LoadResource()
{

	//player

	AddTexture(eType::ALADDIN, new CTexture("Resources/aladdin/Aladdin.png", 13, 2, 26));
	AddTexture(eType::ALADDIN_CUT, new CTexture("Resources/aladdin/Aladdin-cut.png", 4, 1, 4));
	AddTexture(eType::ALADDIN_JUMP, new CTexture("Resources/aladdin/Aladdin-jump.png", 10, 1, 10));
	//AddTexture(eType::ALADDIN_WAIT, new CTexture("Resources/aladdin/Aladdin-wait1.png", 17, 2, 34));


	//map
	AddTexture(eType::MAP1, new CTexture("Resources/map/TileMap.png", 69, 35, 2415));

	//enemy
	AddTexture(eType::BIRD, new CTexture("Resources/enemy/bird.png", 2, 1, 2));

	//coin
	AddTexture(eType::COIN, new CTexture("Resources/enemy/coin.png", 2, 1, 2));

	//fat guard
	AddTexture(eType::FAT_GUARD, new CTexture("Resources/enemy/FatGuard.PNG", 6, 1, 6));
	
	//sharp trap
	AddTexture(eType::SHARP_TRAP, new CTexture("Resources/enemy/sharp_trap.png", 5, 1, 5));

	//Rock
	AddTexture(eType::ROCK, new CTexture("Resources/enemy/rock.png", 5, 1, 5));

	//floor
	AddTexture(eType::FLOOR, new CTexture("Resources/enemy/floor.png", 1, 1, 1));

	//pendulum
	AddTexture(eType::PENDULUM, new CTexture("Resources/enemy/pendulum.png", 15, 1, 15));

	//bat
	AddTexture(eType::BAT, new CTexture("Resources/enemy/bird.png", 2, 1, 2));


}

TextureManager::TextureManager()
{
	LoadResource();
}


TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}
