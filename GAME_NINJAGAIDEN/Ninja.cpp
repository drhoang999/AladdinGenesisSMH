#include "Ninja.h"





Ninja::Ninja(Camera * camera)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::NINJA);
	sprite = new CSprite(texture, 100);
	type = eType::NINJA;
	/*sound = Sound::GetInstance();*/
	/*Health = 10;*/
	//Lives = 5;
	this->camera = camera;
	/*subWeapon.push_back(new Katana());*/
	//isGetNewStage = false;
	isFall = false;
	//Init();
}

Ninja::~Ninja()
{
}

void Ninja::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (direction == 1)
	{
		if (isSitting == true)
		{
			left = x + 12;
			top = y + 20;
			right = x + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_SITTING_HEIGHT - 3;
		}
		else
		{
			left = x + 12;
			top = y + 10;
			right = left + NINJA_BBOX_WIDTH - 10;
			bottom = y + NINJA_BBOX_HEIGHT;

			if (isJumping)
			{
				//top = y + 30;
				bottom = y + NINJA_BBOX_JUMPING_HEIGHT;
			}
			if (isClimbing)
			{
				left = x + 12;
				top = y + 10;
				right = left + NINJA_BBOX_WIDTH - 15;
				bottom = y + NINJA_BBOX_HEIGHT;
			}
		}
	}
	else
	{
		if (isSitting == true)
		{
			left = x + 20;
			top = y + 20;
			right = x + 12 + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_SITTING_HEIGHT - 3;
		}
		else
		{
			left = x + 30;
			top = y + 10;
			right = x + 10 + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_HEIGHT;

			if (isJumping)
			{
				bottom = y + NINJA_BBOX_JUMPING_HEIGHT;

			}
			if (isClimbing)
			{
				left = x + 30;
				top = y + 10;
				right = x + 12 + NINJA_BBOX_WIDTH;
				bottom = y + NINJA_BBOX_HEIGHT;
			}
		}
	}
}

void Ninja::Go(float Vx)
{
	vx = Vx * direction;
	isWalking = 1;
	SetPosition(x + direction * 5,y);
}

void Ninja::Stop()
{
	//if (isAttacking == true)
		//return;

	if (isHurting)
		return;

	vx = 0;
	//DebugOut(L"[STOP] Set vx = %f \n", vx);


	isWalking = 0;
	if (isSitting == true)
	{
		isSitting = 0;
		y = y - PULL_UP_NINJA_AFTER_SITTING;
	}
}

void Ninja::Right()
{
	isSitting = false;
	SetDirection(1);
}

void Ninja::Left()
{
	isSitting = false;
	direction = -1;
}

void Ninja::GetBoundingBoxBrick(float & left, float & top, float & right, float & bottom)
{
	if (direction == 1)
	{
		if (isSitting == true)
		{
			left = x + 12;
			top = y + 60;
			right = x + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_SITTING_HEIGHT - 3;
		}
		else
		{
			left = x + 20;
			top = y + 60;
			right = left + NINJA_BBOX_WIDTH - 24;
			bottom = y + NINJA_BBOX_HEIGHT;

			if (isJumping)
			{
				//top = y + 30;
				bottom = y + NINJA_BBOX_JUMPING_HEIGHT;

			}
			if (isClimbing)
			{
				left = x + 20;
				top = y + 10;
				right = left + NINJA_BBOX_WIDTH - 30;
				bottom = y + NINJA_BBOX_HEIGHT;
			}
		}
	}
	else
	{
		if (isSitting == true)
		{
			left = x + 20;
			top = y + 20;
			right = x + 12 + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_SITTING_HEIGHT - 3;
		}
		else
		{
			left = x + 35;
			top = y + 10;
			right = x + 10 + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_HEIGHT;

			if (isJumping)
			{
				bottom = y + NINJA_BBOX_JUMPING_HEIGHT;

			}
			if (isClimbing)
			{
				left = x + 50;
				top = y + 10;
				right = x + 12 + NINJA_BBOX_WIDTH;
				bottom = y + NINJA_BBOX_HEIGHT;
			}
		}
	}
}





void Ninja::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (Health <= 0)
		return;
	if (x < camera->GetBoundaryLeft() - 16)
		x = camera->GetBoundaryLeft() - 16;
	if (x + NINJA_BBOX_WIDTH > camera->GetBoundaryRight() + SCREEN_WIDTH)
		x = (float)(camera->GetBoundaryRight() + SCREEN_WIDTH - NINJA_BBOX_WIDTH);
	/* Không cho lọt khỏi camera */
	int index = sprite->GetCurrentFrame();

	if (isClimbing)
	{
		if (isUp)
		{
			if (index < NINJA_ANI_CLIMB_GO_UP_BEGIN) // nếu ani chưa đúng
			{
				sprite->SelectFrame(NINJA_ANI_CLIMB_GO_UP_BEGIN); // set lại ani bắt đầu
				sprite->timeAccumulated = dt;
			}
			else
			{
				/* Update ani bình thường */
				sprite->timeAccumulated += dt;
				if (sprite->timeAccumulated >= 100)
				{
					sprite->timeAccumulated -= 100;
					sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
				}
				/* Update ani bình thường */

				if (sprite->GetCurrentFrame() > NINJA_ANI_CLIMB_GO_UP_END) // đã đi vượt qua frame cuối
				{
					isUp = false;
					sprite->SelectFrame(NINJA_ANI_CLIMB_GO_UP_BEGIN);
				}
			}
			y += vy;


		}
		else
			sprite->SelectFrame(NINJA_ANI_CLIMB);

	}
	else
	{
		if (isSitting == true)
		{
			if (isAttacking)
			{
				if (index < NINJA_ANI_SITTING_ATTACKING_BEGIN) // nếu ani chưa đúng
				{
					sprite->SelectFrame(NINJA_ANI_SITTING_ATTACKING_BEGIN); // set lại ani bắt đầu
					sprite->timeAccumulated = dt;
				}
				else
				{
					/* Update ani bình thường */
					sprite->timeAccumulated += dt;
					if (sprite->timeAccumulated >= NINJA_TIME_WAIT_ANI_ATTACKING)
					{
						sprite->timeAccumulated -= NINJA_TIME_WAIT_ANI_ATTACKING;
						sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
					}
					/* Update ani bình thường */

					if (sprite->GetCurrentFrame() > NINJA_ANI_SITTING_ATTACKING_END) // đã đi vượt qua frame cuối
					{
						isAttacking = false;
						sprite->SelectFrame(NINJA_ANI_SITTING);
					}
				}
			}
			else
				sprite->SelectFrame(NINJA_ANI_SITTING);
		}
		else
		{
			if (isAttacking == true)
			{

				///* Xử lí ani đứng đánh */
				if (index < NINJA_ANI_STANDING_ATTACKING_BEGIN) // nếu ani chưa đúng
				{
					sprite->SelectFrame(NINJA_ANI_STANDING_ATTACKING_BEGIN); // set lại ani bắt đầu
					sprite->timeAccumulated = dt;
				}
				else
				{
					/* Update ani bình thường */
					sprite->timeAccumulated += dt;
					if (sprite->timeAccumulated >= NINJA_TIME_WAIT_ANI_ATTACKING)
					{
						sprite->timeAccumulated -= NINJA_TIME_WAIT_ANI_ATTACKING;
						sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
					}
					/* Update ani bình thường */

					if (sprite->GetCurrentFrame() > NINJA_ANI_STANDING_ATTACKING_END) // đã đi vượt qua frame cuối
					{
						//mapWeapon[TypeWeaponCollect]->Start(this->x, this->y);

						isAttacking = false;
						sprite->SelectFrame(NINJA_ANI_IDLE);
					}
				}
				// Xử lí ani đứNG

			}
			else
			{
				if (isWalking == true) // đang di chuyển
				{
					if (isJumping == false) // ko nhảy
					{
						if (index < NINJA_ANI_WALKING_BEGIN || index >= NINJA_ANI_WALKING_END)
							sprite->SelectFrame(NINJA_ANI_WALKING_BEGIN);

						//cập nhật frame mới
						sprite->Update(dt); // dt này được cập nhật khi gọi update; 
					}
					else
					{
						if (index < NINJA_ANI_JUMPING_BEGIN || index >= NINJA_ANI_JUMPING_END)
							sprite->SelectFrame(NINJA_ANI_JUMPING_BEGIN);

						//cập nhật frame mới
						sprite->Update(dt); // dt này được cập nhật khi gọi update; 
					}

				}
				else
					if (isJumping == true) // nếu ko đi mà chỉ nhảy
					{
						if (index < NINJA_ANI_JUMPING_BEGIN || index >= NINJA_ANI_JUMPING_END)
							sprite->SelectFrame(NINJA_ANI_JUMPING_BEGIN);

						//cập nhật frame mới
						sprite->Update(dt);
					}
					else
					{
						sprite->SelectFrame(NINJA_ANI_IDLE);

					}
			}
		}


		/* Update về sprite */
		if (isSitting) //đảm bảo ninja không rớt
			vy = 0;
		GameObject::Update(dt);
		//if(isWalking == true)
		//	x += dx;
		if (isJumping)
		{
			dx = vx * dt;
			dy = vy * dt;
			vy += NINJA_GRAVITY_JUMPING * dt;
			//if (y >= 250)
			//{
			//	y = 250;
			//	isJumping = false;
			//}
		}
		else
		{

			//DebugOut(L"isHurt = %d ---- untouchable = %d\n",isHurting == true? 1:0, untouchable == true? 1: 0);
			if (isHurting)
			{
				sprite->SelectFrame(NINJA_ANI_HURTING);
				//DebugOut(L"IS HURTING ON\n");
				vy += NINJA_GRAVITY_HURTING * dt;
			}
			else
				vy += NINJA_GRAVITY * dt;
		}
		//CollisionWithObjHidden(coObjects);
		float l, r, t, b;
		GetBoundingBox(l, t, r, b);
		//DebugOut(L"BAN DAU left = %f\tright = %f\t top=%f\tbottom = %f\n", l, r, t, b);
		
	}
	

	
}

void Ninja::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);

	int alpha = 255;

	if (direction == 1) // hướng phải
		sprite->Draw(pos.x, pos.y, alpha);
	else
		sprite->DrawFlipX(pos.x, pos.y, alpha);

	//for (auto& obj : mapWeapon)
	//{
	//	if(obj.second->GetFinish() == false)
	//		obj.second->Render(camera);

	//}

	

	
}

void Ninja::Init()
{
	Health = NINJA_DEFAULT_HEALTH; // Ninja dính 16 phát là chết
	/*Lives = NINJA_DEFAULT_LIVES;
	strength = NINJA_DEFAULT_STRENGTH;
	score = NINJA_DEFAULT_SCORE;*/

	Reset();
}

void Ninja::Reset()
{
	direction = 1;

	isSitting = 0;
	isJumping = 0;
	isWalking = 0;
	isAttacking = 0;

	isHurting = 0;

	vx = 0;
	vy = 0;
	//isFreeze = 0;
	//TimeFreeze = 0;

	//isDeadth = false;
	isFall = false;
	isClimbing = false;
	//isClimbUp = false;
	//score = 0;

	//TypeWeaponCollect = eType::NON_WEAPON_COLLECT;
}


