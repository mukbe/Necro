#include "stdafx.h"
#include "Bat.h"

#include "./GameObject/Map/TileNode.h"

Bat::Bat(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Monster(name,pos,size)
{
	
	FrameCount = 0;
	frameX = 0;
	
	position = pos;
	this->size = size;
	startPos = pos;
	endPos = { position.x + 52.f, position.y };
	
	monsterBeat = 2;
	
	
	life = 1;


}


Bat::~Bat()
{
}

void Bat::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void Bat::Release()
{

	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);

}



void Bat::Update(float tick)
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

void Bat::PostUpdate()
{
}

void Bat::Render()
{
	
	_ImageManager->FindTexture("bat")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, frameY);
}

void Bat::ImguiRender()
{
}


