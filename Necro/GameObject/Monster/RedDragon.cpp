#include "stdafx.h"
#include "RedDragon.h"



RedDragon::RedDragon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
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


RedDragon::~RedDragon()
{
}

void RedDragon::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void RedDragon::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void RedDragon::Update(float tick)
{
	Monster::Update(tick);
	SettingCenterXY(tilesize);

	FrameCount++;
	if (FrameCount == 10)
	{
		frameX++;
		FrameCount = 0;
		if (frameX > 6)
		{

			frameX = 0;
		}
	}
}

void RedDragon::PostUpdate()
{
}

void RedDragon::Render()
{
	_ImageManager->FindTexture("reddragon")->FrameRender(rc, nullptr, frameX, frameY);
}

void RedDragon::ImguiRender()
{
}

void RedDragon::MoveAndCheck()
{
}
