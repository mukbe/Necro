#include "stdafx.h"
#include "GreenDragon.h"



GreenDragon::GreenDragon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: Monster(name, pos, size)
{
	FrameCount = 0;
	frameX = 0;
	frameY = 0;
	position = pos;
	this->size = size;
	startPos = pos;
	endPos = { position.x + 52.f, position.y + 52.f };
	
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
	

	FrameCount++;
	if (FrameCount == 10)
	{
		frameX++;
		FrameCount = 0;
		if (frameX > 3)
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
	
	_ImageManager->FindTexture("greendragon")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, frameY);
}

void GreenDragon::ImguiRender()
{
}

