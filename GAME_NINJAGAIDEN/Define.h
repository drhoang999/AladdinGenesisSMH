#ifndef _DEFINE_H__
#define _DEFINE_H__


#include <fstream> 
#include <string>
#include <stdio.h>
#include <Windows.h>  
#include <iostream>
#include <map>
#include <algorithm>
#include <d3dx9.h>
#include <stdlib.h>
#include <iomanip>
#include <d3d9.h>
#include <vector>
#include <iostream>



using namespace std;


#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 

#define SCREEN_WIDTH 340
#define SCREEN_HEIGHT 250

#define IS_DEBUG_RENDER_BBOX isDebug_RenderBBox

#define MAX_FRAME_RATE 90

#define COLOR_BACKGROUND_DEFAULT D3DCOLOR_XRGB(0, 0, 0) // Màu đen
#define COLOR_1 D3DCOLOR_XRGB(243, 0, 200) // Màu đen
#define COLOR_2 D3DCOLOR_XRGB(0, 3, 189) // Màu đen
#define COLOR_3 D3DCOLOR_XRGB(255, 125, 34) // Màu đen
#define COLOR_4 D3DCOLOR_XRGB(193, 47, 0) // Màu đen



#define TIME_LIMIT_WAIT_RESET_GAME 300 // Thời gian chờ vẽ màn màu đen khi reset game

#define INACTIVE					1
#define ACTIVE						2
#define DEATH						3

extern D3DCOLOR D3DCOLOR_BACKGROUND; // màu nền game
extern D3DCOLOR C_1;
extern D3DCOLOR C_2;
extern D3DCOLOR C_3;
extern D3DCOLOR C_4;
extern  vector<D3DCOLOR> listColorScreen;

extern int isDebug_Untouchable;
extern int isDebug_RenderBBox;


// ID của Sprite, object
enum eType
{

	ALADDIN = 1,
	ALADDIN_CUT = 2,
	BIRD = 10,
	COIN = 11,
	FAT_GUARD = 12,
	SHARP_TRAP = 13,
	FLOOR = 14,
	ROCK = 15,
	PENDULUM = 16,
	BAT = 17,

	//map
	MAP1 = 100,
	//others
	RENDERBBOX = 110,
	OBJECT_CLIMB = 112,
	OBJECT_CLIMBUP = 113,



};





typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)





#define GAMEOVER_SELECT_CONTINUE 0
#define GAMEOVER_SELECT_END 1




#ifndef CHECK_OBJECT_IN_CAMERA // Kiểm tra GameObject có nằm trong camera ko?
#define CHECK_OBJECT_IN_CAMERA(obj) \
checkObjectInCamera(obj->GetX(), obj->GetY(), (float)obj->GetWidth(),  (float)obj->GetHeight())
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

#endif 