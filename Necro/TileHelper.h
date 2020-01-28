#pragma once
#include "stdafx.h"

enum AttributeType
{
	AttributeTypeStart = 0,
	ObjNone,					//암것도 없는 타일
	ObjStatic,					//막힌 타일, 파괴 불가
	ObjDestructable,			//막힌 타일, 파괴 가능
	AttributeTypeEnd
};

enum ObjectType
{
	ObjectTypeBegin = 0,
	ObjectAll,
	ObjectTerrain,
	ObjectPlayer,
	ObjectMonster,
	ObjectItem,
	ObjectNPC,
	ObjectWall,
	ObjectTypeEnd
};

enum BrushType
{
	BrushTypeStart = 0,
	Brush,
	Eraser,
	BrushTypeEnd
};

enum PalleteType
{
	PalleteTypeStart = 0,
	Terrain,
	Object,
	PalleteTypeEnd
};


static const POINT defaultMapSize = { 10,10 };
static const D3DXVECTOR2 defaultTileSize = { 52.f, 52.f };


static D3DXVECTOR2 IndexToPos(const POINT index, const D3DXVECTOR2 tileSize, const D3DXVECTOR2 pivotPos)
{
	float x = index.x * tileSize.x + /*(tileSize.x / 2.f)*/ + pivotPos.x;
	float y = index.y * tileSize.y + /*(tileSize.y / 2.f)*/ + pivotPos.y;

	return D3DXVECTOR2(x,y);
}

static POINT PosToIndex(const D3DXVECTOR2 pos, const D3DXVECTOR2 tileSize, const D3DXVECTOR2 pivotPos)
{
	float x = ((pos.x - pivotPos.x) / tileSize.x) * 2.f;
	float y = ((pos.y - pivotPos.y) / tileSize.y) * 2.f;

	return {(int)x, (int)y};
}