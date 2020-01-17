#pragma once
#include "stdafx.h"

enum AttributeType
{
	ObjNone,
	ObjStatic,
	ObjDestructable
};

static const POINTFLOAT tilePivotPos = { 0.f,0.f };
static POINT mapSize = { 10, 10 };
static POINTFLOAT tileSize = { 20.f,20.f };