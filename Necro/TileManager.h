#pragma once
#include "TileHelper.h"


class TileNode;

struct tagPickInfo
{
	AttributeType type;
	POINT index;
};

struct tagPalleteInfo
{
	enum PalleteType
	{
		PalleteTypeStart = 0,
		Terrain,
		Object,
		PalleteTypeEnd
	};

	PalleteType type;
};

struct tagBrushInfo
{
	enum BrushType
	{
		BrushTypeStart = 0,
		Brush,
		Eraser,
		BrushTypeEnd
	};
	
	BrushType type;
};

class TileManager
{
public:
	TileManager(POINT sizeOfMap, D3DXVECTOR2 sizeOfTile, D3DXVECTOR2 pivotPos);
	~TileManager();

	void Release();
	
	void Update(float tick);

	void CreateMap();

	void UpdatePickInfo(AttributeType inputType, POINT inputIndex);

	TileNode* Tile(POINT index);
	TileNode* Tile(int x, int y);

private:
	unordered_map<string, vector<TileNode*>> mapTiles;
	typedef unordered_map<string, vector<TileNode*>>::iterator MapIter;

	typedef vector<TileNode*> vecTiles;
	typedef vector<TileNode*>::iterator VecIter;

	vecTiles mapVector;

	tagPickInfo pick;
	tagBrushInfo brush;
	tagPalleteInfo pallete;
};

