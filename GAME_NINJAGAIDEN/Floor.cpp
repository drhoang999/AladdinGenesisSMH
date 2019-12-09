
#include "Floor.h"


Floor::Floor(int direction, float X, float Y, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	this->status = status;
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::FLOOR);
	sprite = new CSprite(texture, 100);

	D3DXMATRIX* pTransform2 = new D3DXMATRIX();
	D3DXMatrixScaling(pTransform2, 2.0f, 2.0f, 0.0f);
	

	type = eType::FLOOR;

}

Floor::~Floor()
{
}

void Floor::SetStatus(int s)
{
	Enemy::SetStatus(s);

		x = BackupX;
		y = backupY;

}


void Floor::Update(DWORD dt, Aladdin* aladdin)
{

	Enemy::Update(dt);

	this->aladdin = aladdin;
	//DebugOut(L"Aladdin = %f \t floor = %d\n", this->aladdin->GetY(), this->GetSprite()->GetRectFrame(0).right);
	if (this->aladdin->GetX() >= this->x-50 && this->aladdin->GetX() <= this->GetX()+70 && this->aladdin->GetY() >= this->y - 60 && this->aladdin->isJumping) {
		this->aladdin->SetY(this->y - 60);
	}
	
	//DebugOut(L"now = %d \ttimeBegin = %d\n",, .0);

	sprite->Update(dt); // update frame ani
}

void Floor::Render(Camera* camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);
	
		sprite->Draw(pos.x, pos.y);


}

void Floor::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom, int id)
{
	
		right = x + 10;
		left = right - 20;
		top = y - 10;
		bottom = y + 10;
	
}

void Floor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 15;
	top = y - 1;
	right = x + 40;
	bottom = y + 2;
}

void Floor::RenderActiveBoundingBox(Camera* camera)
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

