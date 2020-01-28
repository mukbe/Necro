#include "stdafx.h"
#include "Minotaur.h"



Minotaur::Minotaur(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
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


Minotaur::~Minotaur()
{
}

void Minotaur::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void Minotaur::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void Minotaur::Update(float tick)
{
	Monster::Update(tick);
	SettingCenterXY(tilesize);

	FrameCount++;
	if (FrameCount == 10)
	{
		frameX++;
		FrameCount = 0;
		if (frameX > 8)
		{

			frameX = 0;
		}
	}
}

void Minotaur::PostUpdate()
{
}

void Minotaur::Render()
{
	_ImageManager->FindTexture("minotaur")->FrameRender(rc, nullptr, frameX, frameY);
}

void Minotaur::ImguiRender()
{
}

void Minotaur::MoveAndCheck()
{
}
