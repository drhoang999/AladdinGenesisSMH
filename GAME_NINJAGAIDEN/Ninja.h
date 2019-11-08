#ifndef __NINJA_H__
#define __NINJA_H__
#include "GameObject.h"
#include "debug.h"
//#define NINJA_POSITION_DEFAULT  0.0f, 150.0f
#define NINJA_POSITION_DEFAULT  0.0f,1020.0f


#define NINJA_BBOX_WIDTH 50
#define NINJA_BBOX_HEIGHT 74
#define NINJA_BBOX_SITTING_HEIGHT 74
#define NINJA_BBOX_JUMPING_HEIGHT 74

#define PULL_UP_NINJA_AFTER_SITTING 2.0f // Kéo NINJA lên 18px sau khi ngồi rồi đứng dậy, tránh overlaping do BBOX bottom thu lại khi ngồi

#define NINJA_VJUMP 0.40f //0.4
#define NINJA_VJUMP_HURTING 0.5f // nhảy lúc bị đau
#define PULL_UP_NINJA_AFTER_JUMPING 2.0f // Kéo NINJA lên 18px sau khi nhảy, tránh overlaping do BBOX bottom thu lại khi nhảy

#define NINJA_GRAVITY 0.005f 
#define NINJA_GRAVITY_JUMPING 0.001f 
#define NINJA_GRAVITY_HURTING 0.003f

#define NINJA_WALKING_SPEED 0.15f //0.2f 

#define NINJA_STATE_IDLE 1
#define NINJA_STATE_WALKING 1

#define NINJA_ANI_WALKING_BEGIN 5
#define NINJA_ANI_WALKING_END 7

#define NINJA_ANI_IDLE 1

#define NINJA_ANI_JUMPING_BEGIN 16
#define NINJA_ANI_JUMPING_END 19

#define NINJA_ANI_SITTING 9
#define NINJA_DEADTH 19



/*Ani đang ngồi đánh*/
#define NINJA_ANI_SITTING_ATTACKING_BEGIN 10
#define NINJA_ANI_SITTING_ATTACKING_END 12

/*Ani đang đứng đánh*/
#define NINJA_ANI_STANDING_ATTACKING_BEGIN 2
#define NINJA_ANI_STANDING_ATTACKING_END 4


/* Time Ani attack */
#define NINJA_TIME_WAIT_ANI_ATTACKING 120// thời gian thời của mỗi frame khi tấn công


#define NINJA_ANI_HURTING 19


#define NINJA_ANI_CLIMB 24

#define NINJA_ANI_CLIMB_GO_UP_BEGIN 24
#define NINJA_ANI_CLIMB_GO_UP_END 25

#define TIME_FREEZE_MAX 500


#define NINJA_DEFAULT_HEALTH 16
#define NINJA_DEFAULT_STRENGTH 0
#define NINJA_DEFAULT_SCORE 0
#define NINJA_DEFAULT_LIVES 2
#define NINJA_DEFAULT_RESTORE 6

#define NINJA_UNTOUCHABLE_TIME 1000 

class Ninja : public GameObject
{
private:
	D3DXVECTOR2 PositionBackup;
	DWORD untouchable_start;
	Camera * camera;
public:
	bool isUp;
	bool isAttacking;
	bool isHurting;
	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isFall;
	bool isClimbing;
	//DWORD timeWait;

	//DWORD TimeWaitedAfterDeath;
public: 
	Ninja(Camera* camera);
	~Ninja();
	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetBoundingBoxBrick(float &left, float &top, float &right, float &bottom);
	void Go(float Vx = NINJA_WALKING_SPEED);
	void Stop();
	void Right();
	void Left();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	void Init(); // khởi tạo lại các trạng thái, HeartCollect, Heath, Lives, Score
	void Reset(); // khởi tạo lại các trạng thái.
	
	
	
};


#endif
