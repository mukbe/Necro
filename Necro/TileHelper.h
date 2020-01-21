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

static const POINT defaultMapSize = { 10,10 };
static const D3DXVECTOR2 defaultTileSize = { 52.f, 52.f };