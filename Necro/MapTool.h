#pragma once
#include "TileHelper.h"

class TileManager;
class TileNode;

enum PalleteType
{
	PalleteTypeStart = 0,
	Terrain,
	Object,
	PalleteTypeEnd
};

enum BrushType
{
	BrushTypeStart = 0,
	Brush,
	Eraser,
	BrushTypeEnd
};

class MapTool : public GameObject
{
public:
	MapTool(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~MapTool();

	virtual void Init();
	virtual void ControllUpdate();
	virtual void Update(float tick);

	virtual void Render();
	virtual void ImguiRender();

	TileNode* isInCollision();

private:
	TileManager* map;
	TileManager* pallete;

	PalleteType palleteType;
	BrushType brushType;

	TileNode* selectedNode;

	vector<GameObject*> myObjects;

	int MapSize[2];
	int oldMapSize[2];
};

