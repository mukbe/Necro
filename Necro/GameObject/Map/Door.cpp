#include "stdafx.h"
#include "Door.h"

#include "./GameObject/Map/TileNode.h"


Door::Door(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:WallBase(name, pos, size)
{
}

Door::~Door()
{
}

void Door::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
	life = 1;
	type = WallDestructibleShovel;
	textureKey = "Door";
}

void Door::Release()
{
	WallBase::Release();
}

void Door::ControlUpdate()
{
	WallBase::ControlUpdate();
}

void Door::MissControlUpdate()
{
	WallBase::MissControlUpdate();
}

void Door::Update(float tick)
{
	WallBase::Update(tick);
}

void Door::Render()
{
	WallBase::Render();
}

inline void Door::ImguiRender()
{
	WallBase::ImguiRender();
}

void Door::Show()
{
	WallBase::Show();
}

void Door::Hide()
{
	WallBase::Hide();
}

void Door::Active()
{
	WallBase::Active();
}

void Door::ProcessDestroy()
{
	life--;
	if (life <= 0)
	{
		CAMERA->Shake();
		SOUNDMANAGER->Play("DoorOpen");
		myTile->SetAttribute(ObjNone);
		this->SetActive(false);
	}
}