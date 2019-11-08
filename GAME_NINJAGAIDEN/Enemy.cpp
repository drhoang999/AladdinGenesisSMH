#include "Enemy.h"

void Enemy::SetStatus(int s)
{
	status = s;
}

int Enemy::GetStatus()
{
	return status;
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	GameObject::Update(dt, coObject);
}

