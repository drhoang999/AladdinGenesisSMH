#ifndef __SCENEGAME_H__
#define __SCENEGAME_H__

#include "Scene.h"
#include "Camera.h"
#include "Sprite.h"
//#include "Ninja.h" 
#include "Aladdin.h"
#include "Camera.h"
#include "Map.h"
#include "GameTime.h"
#include "Grid.h"
#include "Bird.h"
#include "Coin.h"

#define GAME_TIME_MAX 150





#define TIME_FOR_DEATH 4000

class SceneGame : public Scene
{
private:

	
	Map * TileMap;
	Camera *camera;
	Aladdin * aladdin;

	vector<LPGAMEOBJECT> listObj;
	vector<Unit*> listUnit;
	Grid *grid;
	

	
	GameTime * gameTime;
	int StateCurrent;

	eType mapCurrent;
	int timeFreeze = 5000;
	DWORD timeBeginFreeze;
	
	bool isGameOver;
	DWORD EndTime;
	float remainTime;

	int count;
public:
	SceneGame();
	~SceneGame();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();

	void InitGame(eType map = MAP1); // khởi tạo lại như chơi từ đầu
	void ResetResource(); // reset lai resource khi simon mất 1 mạng



	void Update(DWORD dt);
	void UpdateGrid();
	void Render();
	void SetInactiveEnemy();

	void LoadMap(eType);



	void CheckCollision(DWORD dt);
	void CheckCollisonOfAladdin(DWORD dt);
	void CheckDropItem();
	void CollisionWithItems(DWORD dt);

	void ReplayMusicGame(int map);
};
#endif