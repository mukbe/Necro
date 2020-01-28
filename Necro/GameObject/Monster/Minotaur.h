#pragma once
#include "Monster.h"
class Minotaur : public Monster
{
public:
	Minotaur(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Minotaur();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void ImguiRender();

	virtual void MoveAndCheck();

};

