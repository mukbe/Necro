#include "stdafx.h"
#include "Monkey.h"



Monkey::Monkey(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
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


Monkey::~Monkey()
{

}

void Monkey::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void Monkey::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void Monkey::Update(float tick)
{
	Monster::Update(tick);
	SettingCenterXY(tilesize);

	FrameCount++;
	if (FrameCount == 10)
	{
		frameX++;
		FrameCount = 0;
		if (frameX > 5)
		{

			frameX = 0;
		}
	}
}

void Monkey::PostUpdate()
{
}

void Monkey::Render()
{
	_ImageManager->FindTexture("monkey")->FrameRender(rc, nullptr, frameX, frameY);
}

void Monkey::ImguiRender()
{
}

void Monkey::MoveAndCheck()
{
}
