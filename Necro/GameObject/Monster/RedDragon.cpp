#include "stdafx.h"
#include "RedDragon.h"



RedDragon::RedDragon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
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

	life = 6;

	AddCallback("RedDragon", [&](TagMessage msg)
	{



		ProcessDestroy();
		_ObjectPool->DeletaObject(this);

	});
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

void RedDragon::PostUpdate()
{
}

void RedDragon::Render()
{
	
	_ImageManager->FindTexture("reddragon")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, frameY);
}

void RedDragon::ImguiRender()
{
}

