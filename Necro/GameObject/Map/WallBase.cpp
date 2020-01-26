#include "stdafx.h"
#include "WallBase.h"
#include "./GameObject/Map/TileNode.h"


WallBase::WallBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	D3DXVECTOR2 tempPivot = _GameWorld->GetTileManager()->GetPivotPos();
	D3DXVECTOR2 tempTileSize = _GameWorld->GetTileManager()->GetTileSize();

	myIndex = PosToIndex(pos, tempTileSize, tempPivot);
	myTile = _GameWorld->GetTileManager()->Tile(myIndex);
	
	AddCallback("ShovelHit", [&](TagMessage msg) {
		if (type == WallDestructableShovel)
		{

		}
	});
	AddCallback("PickHit", [&](TagMessage msg) {
		if (type == WallDestructablePick)
		{

		}
	});
}

WallBase::~WallBase()
{
}

void WallBase::Init()
{
	switch (type)
	{
	case WallDestructableShovel:
		myTile->SetAttribute(ObjDestructable);
		break;
	case WallDestructablePick:
		myTile->SetAttribute(ObjDestructable);
		break;
	case WallUndestructable:
		myTile->SetAttribute(ObjStatic);
		break;
	default:
		break;
	}
}

void WallBase::Release()
{
}

void WallBase::ControlUpdate()
{
}

void WallBase::MissControlUpdate()
{
}

void WallBase::Update(float tick)
{
}

void WallBase::Render()
{
}

void WallBase::SetTextureInfo(string textureStringKey, POINT textureFrameIndex, WallType inputType)
{
	textureKey = textureStringKey;
	textureFrame = textureFrameIndex;
	type = inputType;
}
