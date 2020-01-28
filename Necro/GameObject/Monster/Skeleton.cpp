#include "stdafx.h"
#include "Skeleton.h"
//#include "TileManager.h"
//#include "TileNode.h"


Skeleton::Skeleton(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Monster(name,pos,size)
{
	//_RenderPool->Request(this, RenderManager::Layer::Object);
	FrameCount = 0;
	frameX = 0;
	frameY = 0;
	x = pos.x;
	y = pos.y;
	tilesize = size.x;
	startPos = pos;
	endPos = { x , y };
	speed = D3DXVECTOR2(tilesize, tilesize);
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
	SettingCenterXY(tilesize);

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
	_ImageManager->FindTexture("skeleton")->FrameRender(rc, nullptr, frameX, frameY);
}

void Skeleton::ImguiRender()
{
}

void Skeleton::MoveAndCheck()
{
}
