﻿#ifndef __COIN_H__
#define __COIN_H__


#define COIN_SPEED_X 0.3f
#define COIN_SPEED_Y 0.15f
#define COIN_GRAVITY 0.005f
#define COIN_ACTIVE_BBOX_WIDTH 200
#define COIN_ACTIVE_BBOX_HEIGHT 300
#define TIME_WAIT 40

#include "Enemy.h"
#include "debug.h"

class Coin : public Enemy
{
	float backupNinjaY = 0;

public:
	bool flying;
	bool follow;
	int start;
	float xStart = 0;
	float delta = 0;
	Coin(int direction, float X, float Y, int status);
	virtual ~Coin();

	void Update(DWORD dt, float xNinja, float yNinja, int dNinja, vector<LPGAMEOBJECT>* coObjects = NULL); //update hoạt động của bird như bay ngang, theo alađin ...
	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom, int id);
	virtual void SetStatus(int s);

	void RenderActiveBoundingBox(Camera* camera);
};


#endif  

