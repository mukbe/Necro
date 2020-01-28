#pragma once
#include "Monster.h"
class RedDragon : public Monster
{
public:
	RedDragon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~RedDragon();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void ImguiRender();

	virtual void MoveAndCheck();
};

