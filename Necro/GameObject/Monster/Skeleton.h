#pragma once
#include "Monster.h"
class TileManager;
class Monster;

class Skeleton : public Monster
{
public:
	Skeleton(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Skeleton();

	virtual void Init();
	virtual void Release();
	
	virtual void Update(float tick);
	virtual void PostUpdate();
	virtual void Render();
	virtual void ImguiRender();
	

private:


};

