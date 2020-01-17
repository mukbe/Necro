#pragma once
#include "stdafx.h"

enum AttributeType
{
	AttributeTypeStart = 0,
	ObjNone,
	ObjStatic,
	ObjDestructable,
	AttributeTypeEnd
};

static D3DXVECTOR2 _tilePivotPos;
static POINT _mapSize;
static D3DXVECTOR2 _tileSize;