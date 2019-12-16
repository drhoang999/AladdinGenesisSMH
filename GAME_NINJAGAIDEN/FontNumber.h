#pragma once

#include "Sprite.h"
#include "Texture.h"
#include "define.h"

#include "TextureManager.h"

class FontNumber
{
private:
	CSprite* _sprite;
	CTexture* _texture;

public:
	FontNumber();
	~FontNumber();
	void Draw(float x, float y, const string& s);
};





 



