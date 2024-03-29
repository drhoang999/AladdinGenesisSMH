﻿#include "Game.h"
#include "GameObject.h"



GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	direction = 1;
	isAlready = false;
	BackupX = x;
	
}

void GameObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + texture->GetFrameWidth();
	bottom = top + texture->GetFrameHeight();
}

void GameObject::GetBoundingBoxBrick(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + texture->GetFrameWidth();
	bottom = top + texture->GetFrameHeight();
}

void GameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}







void GameObject::SetDirection(int d)
{
	direction = d;
}

int GameObject::GetDirection()
{
	return direction;
}

void GameObject::SetId(int ID)
{
	this->id = ID;
}
int GameObject::GetId()
{
	return id;
}

void GameObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void GameObject::SetSpeed(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}

void GameObject::GetPosition(float & x, float & y)
{
	x = this->x; y = this->y;
}

void GameObject::GetSpeed(float & vx, float & vy)
{
	vx = this->vx;
	vy = this->vy;
}

float GameObject::GetX()
{
	return x;
}

float GameObject::GetY()
{
	return y;
}

float GameObject::GetVx()
{
	return vx;
}

float GameObject::GetVy()
{
	return vy;
}

void GameObject::SetX(float X)
{
	x = X;
}

void GameObject::SetY(float Y)
{
	y = Y;
}

void GameObject::SetVx(float VX)
{
	vx = VX;
}

void GameObject::SetVy(float VY)
{
	vy = VY;
}


int GameObject::GetHeight()
{
	return texture->GetFrameHeight();
}

int GameObject::GetWidth()
{
	if (texture == nullptr)
		OutputDebugStringW(L"null texture");
	return texture->GetFrameWidth();
}



eType GameObject::GetType()
{
	return type;
}


void GameObject::RenderBoundingBox(Camera * camera)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
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
//
LPCOLLISIONEVENT GameObject::SweptAABBEx(GameObject * coO, int flag)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	//get bounding box with brick
	if (flag == 1)
		GetBoundingBoxBrick(ml, mt, mr, mb);
	else
		GetBoundingBox(ml, mt, mr, mb);

	Game::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CollisionEvent * e = new CollisionEvent(t, nx, ny, coO);
	return e;
}
void GameObject::CalcPotentialCollisions(vector<GameObject*>* coObjects, vector<LPCOLLISIONEVENT>& coEvents, int flag)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i), flag);

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
	
		else
			delete e;

	}


	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);

}

void GameObject::FilterCollision(vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coEventsResult, float & min_tx, float & min_ty, float & nx, float & ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t <= min_tx && c->nx != 0)
		{
			min_tx = c->t;
			nx = c->nx;
			min_ix = i;
		}

		if (c->t <= min_ty && c->ny != 0)
		{
			min_ty = c->t;
			ny = c->ny;
			min_iy = i;
		}
	}

	if (min_ix >= 0)
		coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0)
		coEventsResult.push_back(coEvents[min_iy]);
}

bool GameObject::isCollitionObjectWithObject(GameObject * obj)	// kiểm tra bằng AABB và Sweept AABB
{
	if (checkAABB(obj)) // kiểm tra va chạm bằng AABB trước
		return true;

	LPCOLLISIONEVENT e = SweptAABBEx(obj, 0); // kt va chạm giữa 2 object bằng sweptAABB
	bool res = e->t > 0 && e->t <= 1.0f; // ĐK va chạm
	SAFE_DELETE(e);
	return res;
}

bool GameObject::checkAABB(GameObject * obj)
{
	float l, t, r, b;
	float l1, t1, r1, b1;
	this->GetBoundingBox(l, t, r, b);
	obj->GetBoundingBox(l1, t1, r1, b1);

	if (Game::GetInstance()->checkAABB(l1, t1, r1, b1, l, t, r, b))
		return true;

	return false;
}





void GameObject::SetTexture(CTexture * tex)
{
	texture = tex;
	sprite->texture = tex;
}

CSprite * GameObject::GetSprite()
{
	return sprite;
}

GameObject::~GameObject()
{
	/*SAFE_DELETE(texture);*/
	// ko xóa texture vì đây là texture dùng chung được quản lí bởi TextureManager
	SAFE_DELETE(sprite);
}



