
#include "SharpTrap.h"


SharpTrap::SharpTrap(int direction, float X, float Y, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	this->status = status;
	BackupX = x;
	backupY = y;
	this->outing = false;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::SHARP_TRAP);
	sprite = new CSprite(texture, 300);

	type = eType::SHARP_TRAP;

}

SharpTrap::~SharpTrap()
{
}

void SharpTrap::SetStatus(int s)
{
	Enemy::SetStatus(s);

}


void SharpTrap::Update(DWORD dt, float xAladdin, float yAladdin, int dAladdin, vector<LPGAMEOBJECT>* coObjects)
{

	int index = sprite->GetCurrentFrame();
	DebugOut(L"\nDIRECTION = %d\n", index);
	if (index == 0 || index == 1 || index == 2) {
		outing = false;
	}
	else {
		outing = true;
	}

	Enemy::Update(dt);

	sprite->Update(dt); // update frame ani
}

void SharpTrap::Render(Camera* camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x + 100, pos.y + 100);
	else
		sprite->DrawFlipX(pos.x, pos.y);

}

void SharpTrap::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom, int id)
{
	if (id == -1 && this->id != 262) //id 262 không có bên trái
	{
		left = x - COIN_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - COIN_ACTIVE_BBOX_HEIGHT;
		bottom = y + COIN_ACTIVE_BBOX_HEIGHT;
	}
	else if (this->id != 261) //id 261 không có bên phải
	{
		right = x + COIN_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - COIN_ACTIVE_BBOX_HEIGHT;
		bottom = y + COIN_ACTIVE_BBOX_HEIGHT;
	}
}

void SharpTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 15;
	top = y - 1;
	right = x + 40;
	bottom = y + 40;
}

void SharpTrap::RenderActiveBoundingBox(Camera* camera)
{
	float l, t, r, b;
	GetActiveBoundingBox(l, t, r, b, -1);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (LONG)r - (LONG)l;
	rect.bottom = (LONG)b - (LONG)t;

	D3DXVECTOR2 pos = camera->Transform(l, t);

	Game::GetInstance()->Draw(
		pos.x,
		pos.y,
		TextureManager::GetInstance()->GetTexture(eType::RENDERBBOX)->Texture,
		rect.left,
		rect.top,
		rect.right,
		rect.bottom,
		(this->type == eType::OBJECT_CLIMB || this->type == eType::OBJECT_CLIMBUP) ? 200 : 100);
}

