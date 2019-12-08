#ifndef __FLOOR_H__
#define __FLOOR_H__


#define SIZE_X 0.3f

#include "Enemy.h"
#include "debug.h"
#include "Aladdin.h"

class Floor : public Enemy
{
	Aladdin* aladdin;
public:

	Floor(int direction, float X, float Y, int sizeX);
	virtual ~Floor();

	void Update(DWORD dt, Aladdin* aladdin);
	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom, int id);
	virtual void SetStatus(int s);

	void RenderActiveBoundingBox(Camera* camera);
};


#endif  

