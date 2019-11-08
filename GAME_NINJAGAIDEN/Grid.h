#ifndef __GRID_H__
#define	__GRID_H__

#include "Game.h" 
#include "Sprite.h"  
#include "GameObject.h"


using namespace std;

#define GRID_CELL_WIDTH 284 
#define GRID_CELL_HEIGHT 140

class Unit
{
	friend class Grid;
private:
	Grid *grid;
	LPGAMEOBJECT obj;
	float x;
	float y;
	Unit *prev;
	Unit *next;

public:
	Unit(Grid * grid, LPGAMEOBJECT obj, float x, float y);
	void Move(float x, float y);
	LPGAMEOBJECT GetObj() { return this->obj; }
};

class Grid
{
private:
	int mapWidth;
	int mapHeight;

	int cellWidth; //chiều rộng 1 ô
	int cellHeight; //chiều cao 1 ô 

	int numCol; //số cột
	int numRow; //số hàng

	vector<vector<Unit*>> cells; //mảng 2 chiều để quản lý cấc cells
	char * filepath; //file txt để đọc các đọc các object

public:
	Grid(int map_width, int map_height, int cell_width = GRID_CELL_WIDTH, int cell_height = GRID_CELL_HEIGHT);
	~Grid();

	void SetFile(char * str); // Đọc các object từ file
	void ReloadGrid();


	GameObject * GetNewObject(int id, int direction, int type, float x, float y, int w, int h, float bl, float br, int st); //khởi tạo đối tượng theo loại 
	void Insert(int id, int type, int direction, float x, float y, int w, int h, float bl, float br, int st); //Thêm object vào cells
	void GetListObject(vector<Unit*>& listUnits, Camera * camera);  // lấy các đối tượng trong mảng
	void Add(Unit  *unit);
	void Move(Unit * unit, float x, float y);
};

#endif