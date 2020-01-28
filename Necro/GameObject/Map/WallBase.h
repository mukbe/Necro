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

	virtual void SetTransformInfo()
	{
		D3DXVECTOR2 tempPivot = _GameWorld->GetTileManager()->GetPivotPos();
		D3DXVECTOR2 tempTileSize = _GameWorld->GetTileManager()->GetTileSize();
		
		myIndex = PosToIndex(this->Transform().GetPos(), tempTileSize, tempPivot);
		myTile = _GameWorld->GetTileManager()->Tile(myIndex);

		SetTileAttribute();
	}
	virtual void SetTransformInfo(int x, int y)
	{
		D3DXVECTOR2 tempPivot = _GameWorld->GetTileManager()->GetPivotPos();
		D3DXVECTOR2 tempTileSize = _GameWorld->GetTileManager()->GetTileSize();

		myIndex = { x,y };
		this->Transform().SetPos(IndexToPos(myIndex, tempTileSize, tempPivot));
		myTile = _GameWorld->GetTileManager()->Tile(myIndex);

		SetTileAttribute();
	}
	virtual void SetTransformInfo(TileNode* tile, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 pivot)
	{
		D3DXVECTOR2 tempPivot = pivot;
		D3DXVECTOR2 tempTileSize = size;

		myIndex = PosToIndex(pos, tempTileSize, tempPivot);
		myTile = tile;

		SetTileAttribute();
	}

	virtual void SetTextureInfo(string textureStringKey = "DefaultWall", POINT textureFrameIndex = { 0,0 })
	{
		textureKey = textureStringKey;
		textureFrame = textureFrameIndex;
	}

	virtual void SetTextureKey(string textureStringKey) { textureKey = textureStringKey; }
	virtual void SetTextureFrame(POINT texturFrameIndex) { textureFrame = texturFrameIndex; }

	virtual void SetTileAttribute();


	virtual void SetType(WallType inputType){ type = inputType; }

	virtual WallType GetType() { return type; }

	virtual void ProcessDestroy();

protected:
	string textureKey;
	POINT textureFrame;
	WallType type;
	
	int life;
	
	POINT myIndex;
	TileNode* myTile;

	bool haveIShowIcon;
	float IconLifeTime;
};

