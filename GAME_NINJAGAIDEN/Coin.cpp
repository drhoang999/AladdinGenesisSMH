﻿
#include "Coin.h"


Coin::Coin(int direction, float X, float Y, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	this->status = status;
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::COIN);
	sprite = new CSprite(texture, 100);


	type = eType::COIN;
	vx = COIN_SPEED_X * this->direction;
	vy = 0;
	start = 0;
	xStart = x;
	flying = true;
}

Coin::~Coin()
{
}

void Coin::SetStatus(int s)
{
	Enemy::SetStatus(s);

	switch (this->status)
	{
	case ACTIVE:
		break;
	case DEATH:

		break;
	case INACTIVE:
		x = BackupX;
		y = backupY;
		direction = backupDirection;
		vx = COIN_SPEED_X * direction;
		flying = true;
		break;
	default:
		break;
	}
}


void Coin::Update(DWORD dt, float xAladdin, float yAladdin, int dAladdin, vector<LPGAMEOBJECT>* coObjects)
{

	if (status == INACTIVE)
	{
		return;
	}

	Enemy::Update(dt);

	if (start++ >= TIME_WAIT)
	{
		x += dx;
		y += dy;
	}

	if (flying) // đang bay từ trên xuống
	{
		if (yAladdin != -1) //Aladdin không đang nhảy
		{
			int n = (int)this->y - (int)yAladdin;
			if (n >= 0) // dừng bird
			{
				flying = false;
				xStart = x;
				vy = 0;
				vx = 0;
				direction = (this->x < xAladdin ? 1 : -1);
				vx = COIN_SPEED_X * direction;
				start = 0;
			}
			else
				vy = COIN_SPEED_Y;
		}

	}
	else if (follow)
	{
		int delta;
		if (yAladdin != -1)
			delta = (int)this->y - (int)yAladdin;
		else
			delta = (int)this->y - (int)backupNinjaY;

		if (delta > 2) //trừ thêm tí, ninja hiện đang cao hơn bird
		{
			vy = -COIN_SPEED_Y;
		}
		else if (delta < 0) //Aladdin đang thấp hơn bird
		{
			vy = COIN_SPEED_Y;
		}
		else
			follow = false;

	}
	else // bay ngang
	{
		DebugOut(L"\nDIRECTIONxxx = %d\n", int(direction));
		vy = 0;
		delta = abs(xAladdin - xStart) + 200;
		if (abs(x - xStart) > delta)
		{
			xStart = x;
			vy = 0;
			vx = 0;
			direction *= -1;
			vx = COIN_SPEED_X * direction;
			start = 0;
			if (((int)this->y - (int)yAladdin) != 0) //ninja đã thay đổi y, cần bay theo
			{
				backupNinjaY = yAladdin; //phòng trường hợp bird đang bay xuống thì ninja lại nhảy nên yCoin ko thể dừng
				follow = true;
			}
		}
	}

	sprite->Update(dt); // update frame ani
}

void Coin::Render(Camera* camera)
{
	if (this->status == INACTIVE)
	{
		return;
	}
	
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);



}

void Coin::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom, int id)
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

void Coin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 15;
	top = y - 1;
	right = x + 40;
	bottom = y + 40;
}

void Coin::RenderActiveBoundingBox(Camera* camera)
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

