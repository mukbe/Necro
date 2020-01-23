#pragma once
#include "Monster.h"

class TileManager;
class Monster;

enum Monster1State
{
	Monster1IDEL,
	Monster1LEFT,
	Monster1RIGHT,
	Monster1TOP,
	Monster1BOTTOM
};
class BlueSlime : public Monster
{
public:
	BlueSlime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~BlueSlime();

public:
	
	virtual void Init();
	virtual void Release();
	
	virtual void Update(float tick);
	virtual void PostUpdate();

	virtual void Render();
	virtual void ImguiRender();
	//virtual void SettingCenterXY(float tilesize);
	virtual void MoveAndCheck();
	
	
	private:
	
	Monster1State mosterstate;
	


};

