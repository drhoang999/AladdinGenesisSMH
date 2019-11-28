#include "Map.h"



Map::Map()
{

}


Map::~Map()
{
	SAFE_DELETE(sprite);
}

void Map::LoadMap(eType type)
{
	switch (type)
	{
	case eType::MAP1:
		ReadMapTXT("Resources/map/Background_map_1.txt");
		break;
		
	}
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new CSprite(texture, 100);

}

void Map::ReadMapTXT(char * filename)
{
	ifstream inp(filename, ios::in);
	inp >> RowMap >> ColumnMap >> ColumnTile >> RowTile >> TotalTiles >> HeightBoard;
	for (int i = 0; i < RowMap; i++)
		for (int j = 0; j < ColumnMap; j++)
			inp >> TileMap[i][j];
	inp.close();
	
}

void Map::DrawMap(Camera *camera, int R, int G, int B)
{
	int row = (int)(camera->GetYCam()) / texture->GetFrameHeight();
	int column = (int)(camera->GetXCam()) / texture->GetFrameHeight();

	float x = -(float)((int)(camera->GetXCam()) % texture->GetFrameHeight());
	float y = -(float)((int)(camera->GetYCam()) % texture->GetFrameHeight());

	for (int i = 0; i < SCREEN_HEIGHT / texture->GetFrameHeight() + 1; i++)
		for (int j = 0; j < SCREEN_WIDTH / texture->GetFrameWidth() + 1; j++)
		{
			if (!(row + i < 0 || row + i >= RowMap || j + column < 0 || j + column > ColumnMap))
				sprite->DrawFrame(TileMap[row + i][column + j], x + texture->GetFrameWidth()*j, y + texture->GetFrameHeight()*i + HeightBoard, 255, R, G, B);
		}

}

int Map::GetMapWidth()
{
	return ColumnMap * texture->GetFrameWidth();
}

int Map::GetMapHeight()
{
	return RowMap * texture->GetFrameHeight();
}
