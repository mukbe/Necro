#pragma once
#include "Monster.h"
class TileManager;
class Monster;
#define MAPSIZE 20


//friend class StateBase;
//friend class StateIDLE;
//friend class StateOneStep;


enum MonsterState 
{
	MonsterIDEL,
	MonsterLEFT,
	MonsterRIGHT,
	MonsterTOP,
	MonsterBOTTOM

};



class GreenSlime : public Monster
{


public:
	GreenSlime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~GreenSlime();
	
	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);
	virtual void PostUpdate();
	virtual void Render();
	virtual void ImguiRender();
	//virtual void SettingCenterXY(float tilesize);
	virtual void MoveAndCheck();
	

private:
	
	MonsterState mosterstate;
	/*int FrameCount;
	int frameX;
	int frameY;
	float tilesize;
	float x;
	float y;
	D3DXVECTOR2 speed;
	int tileX, tileY;*/
};