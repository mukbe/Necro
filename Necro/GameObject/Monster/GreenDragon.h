#pragma once
#include "Monster.h"
class GreenDragon : public Monster
{
public:
	GreenDragon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~GreenDragon();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void ImguiRender();

	
};

