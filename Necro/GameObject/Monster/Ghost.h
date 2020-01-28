#pragma once
#include "Monster.h"

class TileManager;
class Monster;

class Ghost : public Monster
{
public:
	Ghost(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Ghost();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void ImguiRender();

	virtual void MoveAndCheck();

};

