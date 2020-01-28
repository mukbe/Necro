#include "stdafx.h"
#include "Ghost.h"



Ghost::Ghost(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
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


Ghost::~Ghost()
{

}

void Ghost::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void Ghost::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void Ghost::Update(float tick)
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

void Ghost::PostUpdate()
{
}

void Ghost::Render()
{
	_ImageManager->FindTexture("ghost")->FrameRender(rc, nullptr, frameX, frameY);
}

void Ghost::ImguiRender()
{
}

void Ghost::MoveAndCheck()
{
}
