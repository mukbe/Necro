#include "stdafx.h"
#include "GoldWall.h"


GoldWall::GoldWall(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:WallBase(name, pos, size)
{
}

GoldWall::~GoldWall()
{
}

void GoldWall::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
	life = 4;
	type = WallDestructiblePick;
	textureKey = "BlackWall";
	
}

void GoldWall::Release()
{
	WallBase::Release();
}

void GoldWall::ControlUpdate()
{
	WallBase::ControlUpdate();
}

void GoldWall::MissControlUpdate()
{
	WallBase::MissControlUpdate();
}

void GoldWall::Update(float tick)
{
	WallBase::Update(tick);
}

void GoldWall::Render()
{
	WallBase::Render();
}

inline void GoldWall::ImguiRender()
{
	WallBase::ImguiRender();
}

void GoldWall::Show()
{
	WallBase::Show();
}

void GoldWall::Hide()
{
	WallBase::Hide();
}

void GoldWall::Active()
{
	WallBase::Active();
}

void GoldWall::SetActiveTexture()
{
	textureKey = "GoldWallFine";
}

void GoldWall::ProcessDestroy()
{
	WallBase::ProcessDestroy();
	if (life < 2)
	{
		textureKey = "GoldWallDamaged";
	}
}
