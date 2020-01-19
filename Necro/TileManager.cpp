#include "TileManager.h"
#include "TileNode.h"

TileManager::TileManager(POINT sizeOfMap, D3DXVECTOR2 sizeOfTile, D3DXVECTOR2 pivotPos)
{
	_mapSize = sizeOfMap;
	_tileSize = sizeOfTile;
	_tilePivotPos = pivotPos;

	_ImageManager->AddFrameTexture("testTile", ResourcePath + L"DefaultTileMap.png", 2, 2);

	mapTiles.insert(make_pair("Map", mapVector));
	mapTiles.insert(make_pair("Object", mapVector));

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
	if (Keyboard::Get()->Down(VK_LBUTTON))
	{
		MapIter mapIter = mapTiles.begin(), mapEnd = mapTiles.end();
		for (; mapIter != mapEnd; ++mapIter)
		{
			VecIter vecIter = (*mapIter).second.begin(), vecEnd = (*mapIter).second.end();
			for (; vecIter != vecEnd; ++vecIter)
			{
				//if (Math::IsPointInAABB((*vecIter)->GetRect(), Mouse::Get()->GetPosition())) {}
				if (Math::IsPointInAABB((*vecIter)->GetRect(), (D3DXVECTOR2)Mouse::Get()->GetPosition()))
				{
					if ((*mapIter).first == "Map")
					{

					}
					else if ((*mapIter).first == "Object")
					{

					}
				}
			}
		}
	}
}

void TileManager::CreateMap()
{
	for (int i = 0; i < _mapSize.x * _mapSize.y; ++i)
	{
		float x = (i % _mapSize.x) * (_tileSize.x / 2.f) + _tilePivotPos.x;
		float y = (i / _mapSize.x) * (_tileSize.y / 2.f) + _tilePivotPos.y;

		TileNode* newTile = _ObjectPool->CreateObject<TileNode>("", D3DXVECTOR2(x, y), D3DXVECTOR2(_tileSize.x, _tileSize.y));
		
		newTile->Init("testTile");

		mapTiles["Map"].push_back(newTile);
	}
}

void TileManager::UpdatePickInfo(AttributeType inputType, POINT inputIndex)
{
	pick.type = inputType;
	pick.index = inputIndex;
}

TileNode* TileManager::Tile(POINT index)
{
	return mapTiles["Map"][index.y * _mapSize.x + index.x];
}

TileNode * TileManager::Tile(int x, int y)
{
	return mapTiles["Map"][y * _mapSize.x + x];
}
