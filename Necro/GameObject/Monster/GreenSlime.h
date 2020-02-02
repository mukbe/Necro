#pragma once
#include "Monster.h"
class TileManager;
class Monster;







class GreenSlime : public Monster
{


public:
	GreenSlime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~GreenSlime();
	
	virtual void Init();
	virtual void Release();
	
	virtual void Update(float tick);
	virtual void PostUpdate();
	virtual void Render();
	virtual void ImguiRender();
	
	

private:
	
	shared_ptr<Texture> tex;
};