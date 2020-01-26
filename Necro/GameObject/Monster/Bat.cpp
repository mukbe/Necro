#include "stdafx.h"
#include "Bat.h"
//#include "TileManager.h"
//#include "TileNode.h"




Bat::Bat(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
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
	endPos = { x + 52.f, y };
	speed = D3DXVECTOR2(tilesize, tilesize);
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
	SettingCenterXY(tilesize);

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

void Bat::PostUpdate()
{
}

void Bat::Render()
{
	_ImageManager->FindTexture("bat")->FrameRender(rc, nullptr, frameX, frameY);
}

void Bat::ImguiRender()
{
}



void Bat::MoveAndCheck()
{
}
