#include "stdafx.h"
#include "Minotaur.h"



Minotaur::Minotaur(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: Monster(name, pos, size)
{
	FrameCount = 0;
	frameX = 0;
	frameY = 0;
	position = pos;
	this->size = size;
	startPos = pos;
	endPos = { position.x + 52.f, position.y };
	
	monsterBeat = 1;
	life = 3;

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
	_ImageManager->FindTexture("minotaur")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, (UINT)!bShow);
}

void Minotaur::ImguiRender()
{
}

void Minotaur::MoveAndCheck()
{
}
