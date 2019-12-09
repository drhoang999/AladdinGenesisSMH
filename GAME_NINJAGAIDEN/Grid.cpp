#include "Grid.h"
#include "define.h"
#include "Bird.h"
#include "Coin.h"
#include "Camera.h"
#include "FatGuard.h"
#include "SharpTrap.h"
#include "Floor.h"
#include "Rock.h"
#include "Pendulum.h"
#include "Bat.h"
Unit::Unit(Grid * grid, LPGAMEOBJECT obj, float x, float y)
{
	this->grid = grid;
	this->obj = obj;
	this->x = x;
	this->y = y;

	this->prev = NULL;
	this->next = NULL;

	grid->Add(this);
}

void Unit::Move(float x, float y)
{
	grid->Move(this, x, y);
}
Grid::Grid(int mapWidth, int mapHeight, int cellWidth, int cellHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;

	numCol = mapWidth / cellWidth; 
	numRow = mapHeight / cellHeight;

	cells.resize(numRow);

	for (int i = 0; i < numRow; i++)
		cells[i].resize(numCol);

	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numCol; j++)
			cells[i][j] = NULL;
}

Grid::~Grid()
{
	
}

void Grid::SetFile(char * str)
{
	filepath = str;
}

void Grid::ReloadGrid()
{
	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numCol; j++)
			cells[i][j] = NULL;
	int id, type, direction, w, h, status, n;
	float x, y, borderL, borderR;

	ifstream inp(filepath, ios::in);
	inp >> n;
	for (int i = 0; i < n; i++)
	{
		inp >> id >> type >> direction >> x >> y >> w >> h >> borderL >> borderR >> status;
		Insert(id, type, direction, x, y, w, h, borderL, borderR, status);
	}
	inp.close();
}

GameObject * Grid::GetNewObject(int id, int direction, int type, float x, float y, int w, int h, float bl, float br, int st)
{
	switch (type)
	{
	case eType::BIRD:
		return new Bird(direction, x, y, st);
	case eType::COIN:
		return new Coin(direction, x, y, st);
	case eType::FAT_GUARD:
		return new FatGuard(direction, x, y, st);
	case eType::SHARP_TRAP:
		return new SharpTrap(direction, x, y, st);
	case eType::FLOOR:
		return new Floor(direction, x, y, st);
	case eType::ROCK:
		return new Rock(direction, x, y, st);
	case eType::PENDULUM:
		return new Pendulum(direction, x, y, st);
	case eType::BAT:
		return new Bat(direction, x, y, st);
}
	return NULL;
}

void Grid::GetListObject(vector<Unit*>& listUnit, Camera * camera)
{
	//lấy cell mà camera đang focus tới
	int start_col = (int)(camera->GetXCam() / cellWidth); 
	int end_col = ceil((camera->GetXCam() + SCREEN_WIDTH) / cellWidth); 

	for (int i = 0; i < numRow; i++)
		for (int j = start_col; j < end_col; j++)
		{
			Unit * unit = cells[i][j];//lấy Unit của cell hiện tại 

			while (unit != NULL)
			{
				if (true)
					listUnit.push_back(unit); //push_back lấy đối tượng ra

				unit = unit->next;
			}
		}
}

void Grid::Insert(int id, int type, int direction, float x, float y, int w, int h, float bl, float br, int st)
{


	GameObject * obj = GetNewObject(id, direction, type, x, y, w, h, bl, br, st);
	if (obj == NULL)
		return;
	obj->SetId(id);
	obj->SetDirection(direction);
	Unit *unit = new Unit(this, obj, x, y);
}
void Grid::Add(Unit *unit)
{
	int row = (int)(unit->y / cellHeight);
	int col = (int)(unit->x / cellWidth);

	// thêm vào đầu cell - add head
	unit->prev = NULL;
	unit->next = cells[row][col];
	cells[row][col] = unit;

	if (unit->next != NULL)
		unit->next->prev = unit;
}

void Grid::Move(Unit *unit, float x, float y)
{
	// lấy chỉ số cell cũ
	int old_row = (int)(unit->y / cellHeight);
	int old_col = (int)(unit->x / cellWidth);

	// lấy chỉ số cell mới
	int new_row = (int)(y / cellHeight);
	int new_col = (int)(x / cellWidth);

	// nếu object ra khỏi vùng viewport -> không cần cập nhật
	if (new_row < 0 || new_row >= numRow || new_col < 0 || new_col >= numCol)
		return;

	// cập nhật toạ độ mới
	unit->x = x;
	unit->y = y;

	// cell không thay đổi
	if (old_row == new_row && old_col == new_col)
		return;

	// huỷ liên kết với cell cũ
	if (unit->prev != NULL)
	{
		unit->prev->next = unit->next;
	}

	if (unit->next != NULL)
	{
		unit->next->prev = unit->prev;
	}

	if (cells[old_row][old_col] == unit)
	{
		cells[old_row][old_col] = unit->next;
	}

	// thêm vào cell mới
	Add(unit);
}