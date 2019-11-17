﻿#ifndef __ALADDIN_H__
#define __ALADDIN_H__
#include "GameObject.h"
#include "debug.h"
#include "Enemy.h"
#include "Bird.h"

#define ALADDIN_POSITION_DEFAULT  -0.0f,1020.0f


#define ALADDIN_BBOX_WIDTH 60
#define ALADDIN_BBOX_HEIGHT 74
#define ALADDIN_BBOX_SITTING_HEIGHT 74
#define ALADDIN_BBOX_JUMPING_HEIGHT 74


#define ALADDIN_GRAVITY 0.005f 

#define ALADDIN_WALKING_SPEED 0.15f //0.2f 

#define ALADDIN_JUMP_SPEED 0.05f //0.2f 

#define ALADDIN_STATE_IDLE 1
#define ALADDIN_STATE_WALKING 1

#define ALADDIN_ANI_WALKING_BEGIN 0
#define ALADDIN_ANI_WALKING_END 12

#define ALADDIN_ANI_IDLE 0

#define ALADDIN_UNTOUCHABLE_TIME 1000 
#define ALADDIN_ANI_HURTING 16
class Aladdin : public GameObject
{
private:
	D3DXVECTOR2 PositionBackup;
	DWORD untouchable_start;
	Camera * camera;

	bool isGetNewStage;

	bool untouchable;
public:
	bool isHurting;
	bool isWalking;
	bool isFall;
	bool isJumping;
	bool isJumDown;
	

	
public:
	Aladdin(Camera* camera);
	~Aladdin();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetBoundingBoxBrick(float &left, float &top, float &right, float &bottom);
	void Go(float Vx = ALADDIN_WALKING_SPEED);
	void Stop();
	void Jump();
	void JumpDown();
	void ResetSit();
	void Right();
	void Left();
	void SetHurt(int t);
	void SetJump();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

	void CollisionWithEnemy(const vector<LPGAMEOBJECT> *coObjects = NULL);
	void Init(); // khởi tạo lại các trạng thái
	void Reset(); // khởi tạo lại các trạng thái.
	bool CheckAABBActiveArea(float l, float t, float r, float b);
	void StartUntouchable();



};


#endif