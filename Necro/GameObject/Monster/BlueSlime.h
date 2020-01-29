#pragma once
#include "Monster.h"

class TileManager;
class Monster;


class BlueSlime : public Monster
{
public:
	BlueSlime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~BlueSlime();


	virtual void Init();
	virtual void Release();
	
	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void ImguiRender();
	
	


};

