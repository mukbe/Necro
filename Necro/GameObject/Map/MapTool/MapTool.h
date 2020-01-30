#pragma once
#include "TileHelper.h"

class TileManager;
class TileNode;
class Pallete;



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

	void SetTexture(string input) {}

	TileNode* isInCollision();

	void ProcessSetMap(TileNode* targetNode);

	void Select(GameObject* input) { selectedObject = input; }
	void DeSelect() { selectedObject = nullptr; }

private:
	TileManager* map;
	Pallete* pallete;

	ObjectType palleteType;
	BrushType brushType;

	TileNode* selectedNode;

	vector<GameObject*> myObjects;

	int MapSize[2];
	int oldMapSize[2];

	GameObject* selectedObject;
};

