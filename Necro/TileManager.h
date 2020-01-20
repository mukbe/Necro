#pragma once
#include "TileHelper.h"


class TileNode;


class TileManager
{
public:
	TileManager(POINT sizeOfMap = { 0,0 }, D3DXVECTOR2 sizeOfTile = { 0.f, 0.f }, D3DXVECTOR2 pivot = { 0,0 });
	~TileManager();

	void Release();
	
	void Update(float tick);

	void CreateMap();

	void ReleaseMap();

	TileNode* Tile(POINT index);
	TileNode* Tile(int x, int y);

	vector<TileNode*> GetArray();

	POINT GetMapSize() { return mapSize; }
	D3DXVECTOR2 GetTileSize() { return tileSize; }
	D3DXVECTOR2 GetPivotPos() { return pivotPos; }

	void SetMapSize(POINT input) 
	{
		ReleaseMap();
		mapSize = input; 
		CreateMap();
	}
	void SetTileSize(D3DXVECTOR2 input) 
	{
		ReleaseMap();
		tileSize = input; 
		CreateMap();
	}
	void SetPivotPos(D3DXVECTOR2 input) 
	{ 
		ReleaseMap();
		pivotPos = input; 
		CreateMap();
	}



private:
	vector<TileNode*> mapTiles;
	typedef vector<TileNode*>::iterator VecIter;

	POINT mapSize;
	D3DXVECTOR2 tileSize;
	D3DXVECTOR2 pivotPos;
};

