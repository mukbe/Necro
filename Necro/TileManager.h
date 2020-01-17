#pragma once
#include "TileHelper.h"


class TileNode;

class TileManager
{
public:
	TileManager(POINT sizeOfMap, D3DXVECTOR2 sizeOfTile, D3DXVECTOR2 pivotPos);
	~TileManager();

	void Release();
	
	void CreateMap();

	TileNode* Tile(POINT index);

private:
	unordered_map<string, vector<TileNode*>> mapTiles;
	typedef unordered_map<string, TileNode*>::iterator MapIter;
	typedef vector<TileNode*> vecTiles;
	typedef vector<TileNode*>::iterator VecIter;
};

