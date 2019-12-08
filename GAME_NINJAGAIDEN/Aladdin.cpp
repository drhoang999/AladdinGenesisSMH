#include "Aladdin.h"

Aladdin::Aladdin(Camera * camera)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::ALADDIN);
	sprite = new CSprite(texture, 100);
	sprite_cut = new CSprite(TextureManager::GetInstance()->GetTexture(eType::ALADDIN_CUT), 100);
	type = eType::ALADDIN;
	this->camera = camera;	
	isFall = false;
	Init();
}

Aladdin::~Aladdin()
{

}

void Aladdin::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (direction == 1)
	{
		
			left = x + 12;
			top = y + 10;
			right = left + ALADDIN_BBOX_WIDTH - 10;
			bottom = y + ALADDIN_BBOX_HEIGHT;	
	}
	else
	{	
			left = x + 30;
			top = y + 10;
			right = x + 10 + ALADDIN_BBOX_WIDTH;
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
	
	if (!isJumping) {
		backupY = y;
		isJumDown = false;
		isHurting = 1;
		isJumping = 1;

	}
	

}

void Aladdin::Cut()
{
	isCut = true;
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

void Aladdin::GetBoundingBoxBrick(float & left, float & top, float & right, float & bottom)
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
		
	
	
	if (isCut == true)
	{
		
		SetTexture(TextureManager::GetInstance()->GetTexture(eType::ALADDIN_CUT));
		sprite_cut->Update(dt);
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
		SetTexture(TextureManager::GetInstance()->GetTexture(eType::ALADDIN));
		sprite->SelectFrame(ALADDIN_ANI_IDLE);

	}


	if (isHurting)
	{
		sprite->SelectFrame(ALADDIN_ANI_HURTING);
		
	}
	else
		vy += ALADDIN_GRAVITY * dt;
	GameObject::Update(dt);
	float l, r, t, b;

	GetBoundingBox(l, t, r, b);	
}





void Aladdin::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);

	int alpha = 255;

	if (direction == 1) // hướng phải
	{
		if (isCut) {
			sprite_cut->Draw(pos.x, pos.y, alpha);
		}
		else {
			sprite->Draw(pos.x, pos.y, alpha);
		}

	}
	else
	{
		if (isCut) {
			sprite_cut->DrawFlipX(pos.x, pos.y, alpha);
		} else {
			sprite->DrawFlipX(pos.x, pos.y, alpha);
		}
		
	}

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
			if ((dynamic_cast<Enemy*>(coObjects->at(i)) ))
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


