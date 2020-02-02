#include "stdafx.h"
#include "GravelWall.h"


GravelWall::GravelWall(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:WallBase(name, pos, size)
{
}

GravelWall::~GravelWall()
{
}

void GravelWall::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
	life = 2;
	type = WallDestructiblePick;
	textureKey = "GravelWallFine";
}

void GravelWall::Release()
{
	WallBase::Release();
}

void GravelWall::ControlUpdate()
{
	WallBase::ControlUpdate();
}

void GravelWall::MissControlUpdate()
{
	WallBase::MissControlUpdate();
}

void GravelWall::Update(float tick)
{
	WallBase::Update(tick);
}

void GravelWall::Render()
{
	WallBase::Render();
}

inline void GravelWall::ImguiRender()
{
	WallBase::ImguiRender();
}

void GravelWall::Show()
{
	WallBase::Show();
}

void GravelWall::Hide()
{
	WallBase::Hide();
}

void GravelWall::Active()
{
	WallBase::Active();
}

void GravelWall::ProcessDestroy()
{
	WallBase::ProcessDestroy();
	if (life < 2)
	{
		textureKey = "GravelWallDamaged";
	}
}
