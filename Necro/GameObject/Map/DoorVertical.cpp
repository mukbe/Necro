#include "stdafx.h"
#include "DoorVertical.h"

#include "./GameObject/Map/TileNode.h"


DoorVertical::DoorVertical(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:WallBase(name, pos, size)
{
}

DoorVertical::~DoorVertical()
{
}

void DoorVertical::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
	life = 1;
	type = WallDestructibleShovel;
	textureKey = "DoorVertical";
}

void DoorVertical::Release()
{
	WallBase::Release();
}

void DoorVertical::ControlUpdate()
{
	WallBase::ControlUpdate();
}

void DoorVertical::MissControlUpdate()
{
	WallBase::MissControlUpdate();
}

void DoorVertical::Update(float tick)
{
	WallBase::Update(tick);
}

void DoorVertical::Render()
{
	WallBase::Render();
}

inline void DoorVertical::ImguiRender()
{
	WallBase::ImguiRender();
}

void DoorVertical::Show()
{
	WallBase::Show();
}

void DoorVertical::Hide()
{
	WallBase::Hide();
}

void DoorVertical::Active()
{
	WallBase::Active();
}

void DoorVertical::ProcessDestroy()
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