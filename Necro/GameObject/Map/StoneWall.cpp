#include "stdafx.h"
#include "StoneWall.h"


StoneWall::StoneWall(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:WallBase(name, pos, size)
{
}

StoneWall::~StoneWall()
{
}

void StoneWall::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
	life = 1;
	type = WallDestructablePick;
	textureKey = "StoneWall";
}

void StoneWall::Release()
{
	WallBase::Release();
}

void StoneWall::ControlUpdate()
{
	WallBase::ControlUpdate();
}

void StoneWall::MissControlUpdate()
{
	WallBase::MissControlUpdate();
}

void StoneWall::Update(float tick)
{
	WallBase::Update(tick);
}

void StoneWall::Render()
{
	WallBase::Render();
}

inline void StoneWall::ImguiRender() 
{
	WallBase::ImguiRender();
}

void StoneWall::Show()
{
	WallBase::Show();
}

void StoneWall::Hide()
{
	WallBase::Hide();
}

void StoneWall::Active()
{
	WallBase::Active();
}
