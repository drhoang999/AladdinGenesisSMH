#include "SceneGame.h"
#include <stdlib.h>
#include <ctime>
#include "Coin.h"
#include "FatGuard.h"
#include "SharpTrap.h"

SceneGame::SceneGame()
{
	LoadResources();

}

SceneGame::~SceneGame()
{
	SAFE_DELETE(TileMap);
	
}

void SceneGame::KeyState(BYTE * state)
{



	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		if (aladdin->GetDirection() == 1)
		{
			aladdin->Right();
			aladdin->Go();
		}
		else if (aladdin->GetDirection() == -1)
		{
			aladdin->Right();
			aladdin->Go(0.09f);
		}
		else
		{
			aladdin->Right();
			aladdin->Go();
		}		
	}
	else
	{
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			if (aladdin->GetDirection() == -1)
			{
				aladdin->Left();
				aladdin->Go();
			}
			else if (aladdin->GetDirection() == 1)
			{
				aladdin->Left();
				aladdin->Go(0.09f);
			}
			else
			{
				aladdin->Left();
				aladdin->Go();
			}										
		}
		else
		{
			aladdin->Stop();														
		}

	}if (Game::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		
			aladdin->Jump();
		
	}
	
		
	
	
	

	
}

void SceneGame::OnKeyDown(int KeyCode)
{


}

void SceneGame::OnKeyUp(int KeyCode)
{


}

void SceneGame::LoadResources()
{
	TextureManager * textureManager = TextureManager::GetInstance();


	gameTime = new GameTime();
	TileMap = new Map();

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	aladdin = new Aladdin(camera);
	grid = new Grid(2272, 1120);


	InitGame();
}

void SceneGame::InitGame(eType map)
{
	LoadMap(map);
	

	gameTime->SetTime(0); // đếm lại từ 0


}


void SceneGame::ResetResource()
{

	grid->ReloadGrid();

	listObj.clear();
	listUnit.clear();
	camera->SetAllowFollowAladdin(true);
	isGameOver = false;
	remainTime = 0;
	count = 1;
	ReplayMusicGame(StateCurrent);
}


void SceneGame::Update(DWORD dt)
{
	
	if (isGameOver)
		return;

	listObj.clear();
	listUnit.clear();
	// lay obj co trong vung camera thong qua unit
	grid->GetListObject(listUnit, camera);

	for (UINT i = 0; i < listUnit.size(); i++)
	{
		LPGAMEOBJECT obj = listUnit[i]->GetObj();
		listObj.push_back(obj);		
	}
	

	aladdin->Update(dt, &listObj);
	
	
	if (camera->AllowFollowAladdin())
	 	camera->SetPosition(aladdin->GetX() - SCREEN_WIDTH / 2 , aladdin->GetY()-SCREEN_HEIGHT/2); // gắn tọa độ nhân vật vào camera
	

	camera->Update(dt);

	gameTime->Update(dt);


	DWORD now = GetTickCount();
	
	//DebugOut(L"now = %d \ttimeBegin = %d\n", now, timeBeginFreeze);


	for (UINT i = 0; i < listObj.size(); i++)
	{

		
		LPGAMEOBJECT obj = listObj[i];
		if (dynamic_cast<Bird*>(listObj[i]))
		{
			Bird* bird = dynamic_cast<Bird*>(listObj[i]);
			bird->Update(dt, aladdin->GetX(), aladdin->GetY(), aladdin->GetDirection(), &listObj);
		
		
		}
		else if (dynamic_cast<Coin*>(listObj[i])) {
			Coin* coin = dynamic_cast<Coin*>(listObj[i]);
			coin->Update(dt, aladdin->GetX(), aladdin->GetY(), aladdin->GetDirection(), &listObj);

		}
		else if (dynamic_cast<FatGuard*>(listObj[i])) {
			FatGuard* coin = dynamic_cast<FatGuard*>(listObj[i]);
			coin->Update(dt, aladdin->GetX(), aladdin->GetY(), aladdin->GetDirection(), &listObj);

		}
		else if (dynamic_cast<SharpTrap*>(listObj[i])) {
			SharpTrap* coin = dynamic_cast<SharpTrap*>(listObj[i]);
			coin->Update(dt, aladdin->GetX(), aladdin->GetY(), aladdin->GetDirection(), &listObj);

		}
		else
			obj->Update(dt, &listObj);
	}

	UpdateGrid();
	SetInactiveEnemy();
	CheckCollision(dt);
		
		

	

}
void SceneGame::CheckDropItem()
{
	
}
void SceneGame::SetInactiveEnemy()
{
	
}
void SceneGame::UpdateGrid()
{
	for (int i = 0; i < listUnit.size(); i++)
	{
		LPGAMEOBJECT obj = listUnit[i]->GetObj();

		//if (obj->IsEnable() == false)
		//	continue;

		float newPos_x, newPos_y;
		obj->GetPosition(newPos_x, newPos_y);
		listUnit[i]->Move(newPos_x, newPos_y);
	}
}
void SceneGame::Render()
{

	if (!isGameOver)
	{
		TileMap->DrawMap(camera, 255, 255, 255);

		for (UINT i = 0; i < listObj.size(); i++)
		{
			listObj[i]->Render(camera);
		}

		
		if (!aladdin->isFall)
			aladdin->Render(camera);

		if (remainTime > 0)
		{
			//DebugOut(L"if 1\tisDeath = %d\t remain = %f\n", boss->GetIsDeath() == true ? 1 : 0, remainTime);
			/*board->Render(ninja, 3, StateCurrent, remainTime, boss);*/

		}
		if (remainTime == 0)
		{
			//DebugOut(L" if 2\t isDeath = %d\t remain = %d\n", boss->GetIsDeath() == true ? 1 : 0, remainTime);
			/*board->Render(ninja, 3, StateCurrent, GAME_TIME_MAX - gameTime->GetTime(), boss);*/

		}
		else if (remainTime <= -1)
		{
			/*sound->StopAll();*/
			TileMap->DrawMap(camera, 0, 0, 0);
			/*Text.Draw(200, 200, "GAME CLEAR");*/
		}

	}
	else
	{
		
		if (GetTickCount() - EndTime < 4000)
		{
			switch (count++)
			{
			case 1:
				TileMap->DrawMap(camera, 243, 0, 200);
				break;
			case 2:
				TileMap->DrawMap(camera, 233, 86, 60);
				break;
			case 3:
				TileMap->DrawMap(camera, 255, 125, 34);
				break;
			case 4:
				count = 1;			
				TileMap->DrawMap(camera, 255, 255, 255);
				break;
			default:
				TileMap->DrawMap(camera, 255, 255, 255);
				break;
			}
			for (UINT i = 0; i < listObj.size(); i++)
			{
				listObj[i]->Render(camera);
			}


			
			aladdin->Render(camera);

	
		}
		else
		{
			TileMap->DrawMap(camera, 0, 0, 0);
		}
		for (UINT i = 0; i < listObj.size(); i++)
		{
			listObj[i]->Render(camera);
		}
	}




}


void SceneGame::LoadMap(eType x)
{
	mapCurrent = x;

	switch (x)
	{
	case eType::MAP1:
		grid->SetFile("Resources/map/readObjectMap1.txt");
		TileMap->LoadMap(eType::MAP1);

		
		camera->SetAllowFollowAladdin(true);

		camera->SetBoundary(0.0f, (float)(TileMap->GetMapWidth() - camera->GetWidth()),0.0f,(float)(TileMap->GetMapHeight())-camera->GetHeight()+30); // set biên camera dựa vào kích thước map		

		camera->SetPosition(0, 0);


		camera->SetAllowFollowAladdin(true);

		
		aladdin->SetPosition(ALADDIN_POSITION_DEFAULT);
		StateCurrent = 1;
		break;	
	}

	ResetResource();
}

void SceneGame::CheckCollision(DWORD dt)
{
	CheckCollisonOfAladdin(dt); // kiểm tra va chạm của aladđin

}

void SceneGame::CheckCollisonOfAladdin(DWORD dt)
{
	aladdin->CollisionWithEnemy(&listObj);
}

void SceneGame::CollisionWithItems(DWORD dt)
{
	
}
void SceneGame::ReplayMusicGame(int map)
{	

}

