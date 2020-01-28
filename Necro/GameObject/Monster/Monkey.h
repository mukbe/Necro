#pragma once
#include "Monster.h"
class Monkey : public Monster
{
public:
	Monkey(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Monkey();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void ImguiRender();

	virtual void MoveAndCheck();


};

