#include "TileManager.h"
#include "TileNode.h"

TileManager::TileManager(POINT sizeOfMap, D3DXVECTOR2 sizeOfTile, D3DXVECTOR2 pivot)
	:mapSize(sizeOfMap), tileSize(sizeOfTile), pivotPos(pivot)
{
	CreateMap();
}

TileManager::~TileManager()
{
}

void TileManager::Release()
{
}

void TileManager::Update(float tick)
{
}

void TileManager::CreateMap()
{
	for (int i = 0; i < mapSize.x * mapSize.y; ++i)
	{
		float x = (i % mapSize.x) * (tileSize.x ) + pivotPos.x;
		float y = (i / mapSize.x) * (tileSize.y ) + pivotPos.y;

		TileNode* newTile = _ObjectPool->CreateObject<TileNode>("", D3DXVECTOR2(x, y), D3DXVECTOR2(tileSize.x, tileSize.y));
		
		newTile->Init("DefaultMap");

		newTile->SetPivotPos(pivotPos);

		mapTiles.push_back(newTile);
	}
}

void TileManager::ReleaseMap()
{
	if (mapTiles.size() > 0)
	{
		for (int i = 0; i < mapTiles.size(); ++i)
		{
			_ObjectPool->DeletaObject(mapTiles[i]);

			//VecIter iter = mapTiles.begin() + i;
			//(*iter)->Release();
			//mapTiles.erase(iter);
			//--i;
		}
		mapTiles.clear();
	}
}



TileNode* TileManager::Tile(POINT index)
{
	return mapTiles[index.y * mapSize.x + index.x];
}

TileNode * TileManager::Tile(int x, int y)
{
	return mapTiles[y * mapSize.x + x];
}

vector<TileNode*> TileManager::GetArray()
{
	return mapTiles;
}
