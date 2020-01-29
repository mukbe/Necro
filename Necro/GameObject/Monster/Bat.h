#pragma once
#include "Monster.h"
class TileManager;
class Monster;
class Bat : public Monster
{
public:
	Bat(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Bat();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void PostUpdate();
	virtual void Render();
	virtual void ImguiRender();
	
	
private:
	
	//MonsterState mosterstate;

};

