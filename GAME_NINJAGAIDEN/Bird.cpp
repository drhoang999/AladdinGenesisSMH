
#include "Bird.h"



Bird::Bird(int direction, float X, float Y, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	this->status = status;
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::BIRD);
	sprite = new CSprite(texture, 100);


	type = eType::BIRD;
	vx = BIRD_SPEED_X * this->direction;
	vy = 0;
	start = 0;
	xStart = x;
	flying = true;
}

Bird::~Bird()
{
}

void Bird::SetStatus(int s)
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
		vx = BIRD_SPEED_X * direction;
		flying = true;
		break;
	default:
		break;
	}
}


void Bird::Update(DWORD dt, float xAladdin, float yAladdin, int dAladdin, vector<LPGAMEOBJECT>* coObjects)
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
				vx = BIRD_SPEED_X * direction;
				start = 0;
			}
			else
				vy = BIRD_SPEED_Y;
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
			vy = -BIRD_SPEED_Y;
		}
		else if (delta < 0) //Aladdin đang thấp hơn bird
		{
			vy = BIRD_SPEED_Y;
		}
		else
			follow = false;

	}
	else // bay ngang
	{
		DebugOut(L"\nDIRECTION = %d\n", int(direction));
		vy = 0;
		delta = abs(xAladdin - xStart) + 200;
		if (abs(x - xStart) > delta)
		{
			xStart = x;
			vy = 0;
			vx = 0;
			direction *= -1;
			vx = BIRD_SPEED_X * direction;
			start = 0;
			if (((int)this->y - (int)yAladdin) != 0) //ninja đã thay đổi y, cần bay theo
			{
				backupNinjaY = yAladdin; //phòng trường hợp bird đang bay xuống thì ninja lại nhảy nên yBird ko thể dừng
				follow = true;
			}
		}
	}

	sprite->Update(dt); // update frame ani
}

void Bird::Render(Camera * camera)
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

void Bird::GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id)
{
	if (id == -1 && this->id != 262) //id 262 không có bên trái
	{
		left = x - BIRD_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - BIRD_ACTIVE_BBOX_HEIGHT;
		bottom = y + BIRD_ACTIVE_BBOX_HEIGHT;
	}
	else if (this->id != 261) //id 261 không có bên phải
	{
		right = x + BIRD_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - BIRD_ACTIVE_BBOX_HEIGHT;
		bottom = y + BIRD_ACTIVE_BBOX_HEIGHT;
	}
}

void Bird::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 15;
	top = y - 1;
	right = x + 40;
	bottom = y + 40;
}

void Bird::RenderActiveBoundingBox(Camera * camera)
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

