#include "stdafx.h"
#include "Skeleton.h"

//#include "TileManager.h"
//#include "TileNode.h"

#include "./Systems/Manage/TileManager.h""
#include "./GameObject/Map/TileNode.h"



Skeleton::Skeleton(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Monster(name,pos,size)
{
	//_RenderPool->Request(this, RenderManager::Layer::Object);
	FrameCount = 0;
	frameX = 0;
	frameY = 0;
	position = pos;
	this->size = size;
	startPos = pos;
	endPos = { position.x ,position.y };
	
	monsterBeat = 2;
	
}


Skeleton::~Skeleton()
{
}

void Skeleton::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void Skeleton::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}



void Skeleton::Update(float tick)
{
	Monster::Update(tick);
	

	FrameCount++;
	if (FrameCount == 10)
	{
		frameX++;
		FrameCount = 0;
		if (frameX > 7)
		{

			frameX = 0;
		}
	}

}

void Skeleton::PostUpdate()
{
}

void Skeleton::Render()
{
	
	_ImageManager->FindTexture("skeleton")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, frameY);
}

void Skeleton::ImguiRender()
{
}

