#include "stdafx.h"
#include "GreenDragon.h"



GreenDragon::GreenDragon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: Monster(name, pos, size)
{
	FrameCount = 0;
	frameX = 0;
	frameY = 0;
	x = pos.x;
	y = pos.y;
	tilesize = size.x;
	startPos = pos;
	endPos = { pos.x + 52.f, pos.y + 52.f };
	speed = D3DXVECTOR2(tilesize, tilesize);
	monsterBeat = 2;
}


GreenDragon::~GreenDragon()
{
}

void GreenDragon::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void GreenDragon::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void GreenDragon::Update(float tick)
{
	Monster::Update(tick);
	SettingCenterXY(tilesize);

	FrameCount++;
	if (FrameCount == 10)
	{
		frameX++;
		FrameCount = 0;
		if (frameX > 1)
		{

			frameX = 0;
		}
	}
}

void GreenDragon::PostUpdate()
{
}

void GreenDragon::Render()
{
	_ImageManager->FindTexture("greendragon")->FrameRender(rc, nullptr, frameX, frameY);
}

void GreenDragon::ImguiRender()
{
}

void GreenDragon::MoveAndCheck()
{
}
