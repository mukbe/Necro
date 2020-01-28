#pragma once
#include "WallBase.h"

class StoneWall : public WallBase
{
public:
	StoneWall(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~StoneWall();

	virtual void Init();
};