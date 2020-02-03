#include "stdafx.h"
#include "BlueSlime.h"



BlueSlime::BlueSlime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: Monster(name, pos, size)
{
	
	
	FrameCount = 0;
	frameX = 0;
	frameY = 0;
	position = pos;
	this->size = size;
	startPos = pos;
	endPos = { position.x , position.y - 52.f };
	monsterBeat = 2;
	
	life = 2;

	
}


BlueSlime::~BlueSlime()
{
}


void BlueSlime::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void BlueSlime::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);

}



void BlueSlime::Update(float tick)
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

	clocking();
}

void BlueSlime::PostUpdate()
{
}

void BlueSlime::Render()
{
	_ImageManager->FindTexture("blueslime")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, frameY);
	
}

void BlueSlime::ImguiRender()
{
}


