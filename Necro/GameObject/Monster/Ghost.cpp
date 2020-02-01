#include "stdafx.h"
#include "Ghost.h"



Ghost::Ghost(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
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

	life = 1;

	
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
	_ImageManager->FindTexture("ghost")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, frameY);
}

void Ghost::ImguiRender()
{
}

