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

	AddTexture(eType::ALADDIN, new CTexture("Resources/Aladdin.png", 13, 2, 26));

	//map
	AddTexture(eType::MAP1, new CTexture("Resources/map/Background_map_1.png", 69, 35, 2415));

	//enemy
	AddTexture(eType::BIRD, new CTexture("Resources/enemy/bird.png", 2, 1, 2));

	//coin
	AddTexture(eType::COIN, new CTexture("Resources/enemy/coin.png", 2, 1, 2));

	//fat guard
	AddTexture(eType::FAT_GUARD, new CTexture("Resources/enemy/FatGuard.PNG", 6, 1, 6));
	
	//sharp trap
	AddTexture(eType::SHARP_TRAP, new CTexture("Resources/enemy/sharp_trap.png", 5, 1, 5));

}

TextureManager::TextureManager()
{
	LoadResource();
}


TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}
