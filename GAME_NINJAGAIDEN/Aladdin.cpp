#include "Aladdin.h"

Aladdin::Aladdin(Camera* camera)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::ALADDIN);
	sprite = new CSprite(texture, 150);
	type = eType::ALADDIN;
	this->camera = camera;
	isFall = false;
	Init();
}

Aladdin::~Aladdin()
{

}

void Aladdin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (direction == 1)
	{

		left = x + 15;
		top = y - 1;
		right = x + ALADDIN_BBOX_WIDTH - 15;
		bottom = y + ALADDIN_BBOX_HEIGHT;
	}
	else
	{
		left = x + 15;
		top = y - 1;
		right = x + ALADDIN_BBOX_WIDTH - 15;
		bottom = y + ALADDIN_BBOX_HEIGHT;
	}
}

void Aladdin::Go(float Vx)
{

	vx = Vx * direction;
	isWalking = 1;
	isHurting = 0;
	SetPosition(x + direction * 5, y);

}

void Aladdin::Jump()
{
	if (isJumping == true)
		return;


	backupY = y;
	isJumDown = false;
	isJumping = 1;




	//if (isOnStair == true)
	//	return;

	//if (isSit == true)
	//	return;

	//if (isHurting)
	//	return;

	isJumping = true;


}

void Aladdin::Cut()
{
	isCut = true;
}

void Aladdin::Throw()
{
	isThrow = true;
}

void Aladdin::JumpDown()
{

	if (isJumping) {



		if (y != 0 && backupY - y > 90) {
			isJumDown = true;
		}
		if (y != 0 && backupY < y) {

			isJumping = false;
			SetPosition(x, 1020);
		}

		if (isJumDown) {
			SetPosition(x, y + 5);

		}
		else {

			SetPosition(x, y - 5);
		}
	}


	vy = ALADDIN_JUMP_SPEED * direction;
}

void Aladdin::Stop()
{
	SetTexture(TextureManager::GetInstance()->GetTexture(eType::ALADDIN));
	if (isHurting)
		return;
	vx = 0;
	isWalking = 0;
	isCut = 0;
	isSit = 0;
	isThrow = 0;
}

void Aladdin::ResetSit()
{

}

void Aladdin::Right()
{

	SetDirection(1);
}

void Aladdin::Left()
{

	direction = -1;
}

void Aladdin::Sit()
{
	if (!isSit) endSit = false;
	isSit = true;

}

void Aladdin::Stand()
{
	isSit = false;
}

void Aladdin::SetHurt(int t)
{
	if (isHurting == true)
	{
		return;

	}

	isWalking = 0;
	isHurting = 1;
	ResetSit();

	StartUntouchable();

}

void Aladdin::SetJump()
{
}

void Aladdin::GetBoundingBoxBrick(float& left, float& top, float& right, float& bottom)
{
	if (direction == 1)
	{
		left = x + 20;
		top = y + 60;
		right = left + ALADDIN_BBOX_WIDTH - 24;
		bottom = y + ALADDIN_BBOX_HEIGHT;
	}
	else
	{
		left = x + 35;
		top = y + 10;
		right = x + 10 + ALADDIN_BBOX_WIDTH;
		bottom = y + ALADDIN_BBOX_HEIGHT;
	}
}





void Aladdin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (x < camera->GetBoundaryLeft() - 16) {
		x = camera->GetBoundaryLeft() - 16;


	}
	if (x + ALADDIN_BBOX_WIDTH > camera->GetBoundaryRight() + SCREEN_WIDTH)
		x = (float)(camera->GetBoundaryRight() + SCREEN_WIDTH - ALADDIN_BBOX_WIDTH);
	/* Không cho lọt khỏi camera */


	int index = sprite->GetCurrentFrame();

	JumpDown();
	/*if (isJumping) {

		dx = vx * dt;
		dy = vy * dt;
		vy += ALADDIN_GRAVITY_JUMPING * dt;



		if (index < ALADDIN_ANI_JUMP_BEGIN || index >= ALADDIN_ANI_JUMP_END)
			sprite->SelectFrame(ALADDIN_ANI_JUMP_BEGIN);
		sprite->Update(dt);


		if (y != 0 && backupY - y > 90) {
			isJumDown = true;
		}
		if (y != 0 && backupY < y) {

			SetPosition(x, y - direction * 5);
		}

		if (isJumDown) {
			SetPosition(x, y + 5);

		}
		else {

			SetPosition(x, y - 5);
		}

		vy = ALADDIN_JUMP_SPEED * direction;

	}

*/
	if (isJumping) {

		if (index < ALADDIN_ANI_JUMP_BEGIN || index >= ALADDIN_ANI_JUMP_END)
			sprite->SelectFrame(ALADDIN_ANI_JUMP_BEGIN);
		sprite->Update(dt);

	}
	else
		if (isSit == true)
		{


			if (isCut == true) {
				if (index < ALADDIN_ANI_CUT_SIT_BEGIN || index >= ALADDIN_ANI_CUT_SIT_END)
					sprite->SelectFrame(ALADDIN_ANI_CUT_SIT_BEGIN);
				sprite->Update(dt);
			}
			else


				if (index == ALADDIN_ANI_SIT_END)
					endSit = true;
				else
					if (index < ALADDIN_ANI_SIT_BEGIN || index >= ALADDIN_ANI_SIT_END)
						sprite->SelectFrame(ALADDIN_ANI_SIT_BEGIN);


			if (!endSit)sprite->Update(dt);


		}
		else if (isCut == true)
		{
			if (index < ALADDIN_ANI_CUT_BEGIN || index >= ALADDIN_ANI_CUT_END)
				sprite->SelectFrame(ALADDIN_ANI_CUT_BEGIN);
			sprite->Update(dt);

		}
		else if (isThrow == true)
		{
			if (index < ALADDIN_ANI_CUT_BEGIN || index >= ALADDIN_ANI_CUT_END)
				sprite->SelectFrame(ALADDIN_ANI_CUT_BEGIN);
			sprite->Update(dt);

		}
		else if (isWalking == true) // đang di chuyển
		{
			if (index < ALADDIN_ANI_WALKING_BEGIN || index >= ALADDIN_ANI_WALKING_END)
				sprite->SelectFrame(ALADDIN_ANI_WALKING_BEGIN);

			//cập nhật frame mới
			sprite->Update(dt); // dt này được cập nhật khi gọi update; 

		}
		else
		{
			//if(index == ALADDIN_ANI_JUGGLE_DOWN_END)
			//	sprite->SelectFrame(ALADDIN_ANI_JUGGLE_BEGIN);

			//if (index < ALADDIN_ANI_JUGGLE_DOWN_BEGIN || index >= ALADDIN_ANI_JUGGLE_DOWN_END)
			//	sprite->SelectFrame(ALADDIN_ANI_JUGGLE_DOWN_BEGIN);


			sprite->SelectFrame(ALADDIN_ANI_IDLE);


		}


	if (isHurting)
	{
		//sprite->SelectFrame(ALADDIN_ANI_HURTING);

	}
	else
		vy += ALADDIN_GRAVITY * dt;
	GameObject::Update(dt);
	float l, r, t, b;

	GetBoundingBox(l, t, r, b);
}





void Aladdin::Render(Camera* camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);

	int alpha = 255;

	if (direction == 1)
		sprite->Draw(pos.x, pos.y, alpha);
	else
		sprite->DrawFlipX(pos.x, pos.y, alpha);

}



void Aladdin::CollisionWithEnemy(const vector<LPGAMEOBJECT>* coObjects)
{

	if (GetTickCount() - untouchable_start > ALADDIN_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = false;
	}
	if (untouchable == false)
	{
		vector<LPGAMEOBJECT> listEnemy;

		listEnemy.clear();
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if ((dynamic_cast<Enemy*>(coObjects->at(i))))
			{
				if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() != INACTIVE)
					listEnemy.push_back(coObjects->at(i));
			}

		}

		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			if (listEnemy[i]->isCollitionObjectWithObject(this))
			{
				SetHurt(listEnemy[i]->GetType() == 0);
			}
		}
	}
}

void Aladdin::Init()
{
	Reset();
}

void Aladdin::Reset()
{
	direction = 1;
	isWalking = 0;

	isHurting = 0;

	vx = 0;
	vy = 0;

	isFall = false;

}

bool Aladdin::CheckAABBActiveArea(float l, float t, float r, float b)
{
	float aladdin_l, aladdin_t, aladdin_r, aladdin_b;
	this->GetBoundingBox(aladdin_l, aladdin_t, aladdin_r, aladdin_b);

	if (Game::GetInstance()->checkAABB(aladdin_l, aladdin_t, aladdin_r, aladdin_b, l, t, r, b))
		return true;

	return false;
}

void Aladdin::StartUntouchable()
{
	untouchable = true;
	untouchable_start = GetTickCount();
}


