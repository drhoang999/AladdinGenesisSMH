#include "FontNumber.h"



FontNumber::FontNumber()
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::FONTNUMBER);
	_sprite = new CSprite(_texture, 0);
}


FontNumber::~FontNumber()
{
	SAFE_DELETE(_sprite);
}

void FontNumber::Draw(float x, float y, const string& s)
{
	int num = 0;
	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= '0' && s[i] <= '9')
		{
			num = (int) s[i];
			_sprite->SelectFrame(num -48);
		}

		_sprite->Draw(x + i * _texture->GetFrameWidth(), y);
	}
}
