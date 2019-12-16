#pragma once

#include "Aladdin.h"
#include "Sprite.h"
#include "FontNumber.h"
#include "Texture.h"
#include "define.h"

#include "TextureManager.h"

class AladdinHead
{
private:

	int life;

	CSprite* _sprite;
	CTexture* _texture;
	string FillNumber(string s, UINT MaxNumber);
	FontNumber* _text;

public:
	//AladdinHead();
	AladdinHead(int setLife);
	~AladdinHead();
	void Draw(float x, float y);
};
