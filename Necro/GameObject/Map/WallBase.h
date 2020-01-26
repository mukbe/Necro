#pragma once
#include "./TileHelper.h"

class TileNode;

enum WallType
{
	WallTypeBegin = 0,
	WallDestructableShovel,
	WallDestructablePick,
	WallUndestructable,
	WallTypeEnd
};

class WallBase : public GameObject
{
public:
	WallBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~WallBase();

	virtual void Init();
	virtual void Release();
	
	virtual void ControlUpdate();
	virtual void MissControlUpdate();
	
	virtual void Update(float tick);

	virtual void Render();
	
	virtual void ImguiRender() {}

	virtual void SetTextureInfo(string textureStringKey = "DefaultWall", POINT textureFrameIndex = { 0,0 }, WallType inputType = WallDestructableShovel)
	{
		textureKey = textureStringKey;
		textureFrame = textureFrameIndex;
		type = inputType;
	}
	virtual void SetType(WallType inputType){ type = inputType; }

	virtual WallType GetType() { return type; }

	virtual void ProcessDestroy();

private:
	string textureKey;
	POINT textureFrame;
	WallType type;
	
	int life;
	
	POINT myIndex;
	TileNode* myTile;

	bool haveIShowIcon;
	float IconLifeTime;
};

