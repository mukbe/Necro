#include "stdafx.h"
#include "StoneWall.h"


StoneWall::StoneWall(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:WallBase(name, pos, size)
{
}

StoneWall::~StoneWall()
{
}

void StoneWall::Init()
{
	life = 1;
	type = WallDestructablePick;
	textureKey = "StoneWall";
}
