﻿#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__


#include "define.h"
#include "Sprite.h"
#include "Texture.h"
#include "Camera.h" 
#include "TextureManager.h"

using namespace std;


class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;

struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class GameObject
{

protected:
	/*DWORD LastTimeAttacked;*/ // thời điểm bị tấn công cuối cùng
	/*int Health;*/
	int id;
	int direction;	// hướng -1 : trái, 1: phải
	eType type; // Loại Object

	float x;
	float y;

	float dx;
	float dy;

	float vx;
	float vy;



	DWORD dt;

	CTexture * texture;
	CSprite * sprite;


public:
	GameObject();
	virtual ~GameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetBoundingBoxBrick(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera) = 0;

	float BackupX;
	float backupY;
	int backupDirection;
	bool isAlready;
	
	
	
	void SetDirection(int d);
	int GetDirection();
	void SetId(int ID);
	int GetId();


	void SetPosition(float x, float y);
	void SetSpeed(float vx, float vy);
	void GetPosition(float &x, float &y);
	void GetSpeed(float &vx, float &vy);

	float GetX();
	float GetY();
	float GetVx();
	float GetVy();
	void SetX(float X);
	void SetY(float Y);
	void SetVx(float VX);
	void SetVy(float VY);
	int GetHeight();
	int GetWidth();
	eType GetType();

	void RenderBoundingBox(Camera * camera);
	LPCOLLISIONEVENT SweptAABBEx(GameObject * coO, int flag);
	void CalcPotentialCollisions(vector<GameObject*> *coObjects, vector<LPCOLLISIONEVENT> &coEvents, int flag);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	bool isCollitionObjectWithObject(GameObject *obj); 	// kiểm tra bằng AABB và Sweept AABB
	bool checkAABB(GameObject *obj);


	

	void SetTexture(CTexture * tex);
	CSprite * GetSprite();
};


#endif 