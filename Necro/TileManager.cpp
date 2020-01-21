#include "TileManager.h"
#include "TileNode.h"

POINT TileManager::mapSize = { 0,0 };
D3DXVECTOR2 TileManager::tileSize = { 0.f,0.f };
D3DXVECTOR2 TileManager::pivotPos = { 0.f,0.f };

void TileManager::SetMapInfo(POINT tileMax, D3DXVECTOR2 size, D3DXVECTOR2 mapPivot)
{
	mapSize = tileMax;
	tileSize = size;
	pivotPos = mapPivot;
}
void TileManager::SetTexture(string name, wstring path, UINT x, UINT y)
{
	if (path.empty())
	{
		/*_ImageManager->DeleteTexture("DefaultMap");
		_ImageManager->AddFrameTexture("DefaultMap", ResourcePath + L"DefaultTileMap.png", 2, 2);*/
		
		imageKey = "DefaultMap";

		return;
	}
	//_ImageManager->DeleteTexture("DefaultMap");
	//_ImageManager->AddFrameTexture("DefaultMap", path, x, y);

}


TileManager::TileManager()
{
}

TileManager::~TileManager()
{
}

void TileManager::Release()
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
