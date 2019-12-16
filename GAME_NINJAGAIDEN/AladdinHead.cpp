#include "AladdinHead.h"


string AladdinHead::FillNumber(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}



AladdinHead::AladdinHead(int setLife)
{
	life = setLife;
	_texture = TextureManager::GetInstance()->GetTexture(eType::ALADDIN_HEAD);
	_sprite = new CSprite(_texture, 0);
}


AladdinHead::~AladdinHead()
{
	SAFE_DELETE(_sprite);
}

void AladdinHead::Draw(float x, float y)
{	
	_sprite->Draw(x + 0 * _texture->GetFrameWidth(), y);
	//_text->Draw(x+200, y, FillNumber(std::to_string(life), 6));
}
