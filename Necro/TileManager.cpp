#include "TileManager.h"
#include "TileNode.h"

TileManager::TileManager(POINT sizeOfMap, D3DXVECTOR2 sizeOfTile, D3DXVECTOR2 pivotPos)
{
	_mapSize = sizeOfMap;
	_tileSize = sizeOfTile;
	_tilePivotPos = pivotPos;

	_ImageManager->AddFrameTexture("testTile", ResourcePath + L"DefaultTileMap.png", 2, 2);

	mapTiles.insert(make_pair("Map", (*new vecTiles)));
	CreateMap();
}

TileManager::~TileManager()
{
}

void TileManager::Release()
{
}

void TileManager::CreateMap()
{
	for (int i = 0; i < _mapSize.x * _mapSize.y; ++i)
	{
		TileNode* newTile = _ObjectPool->CreateObject<TileNode>("", D3DXVECTOR2(_tilePivotPos.x + i * (_tileSize.x / 2.f)
			, _tilePivotPos.y + i * (_tileSize.y / 2.f)), D3DXVECTOR2(_tileSize.x, _tileSize.y));
		
		newTile->Init("testTile");

		mapTiles["Map"].push_back(newTile);
	}
}

TileNode* TileManager::Tile(POINT index)
{
	return mapTiles["Map"][index.y * _mapSize.x + index.x];
}
