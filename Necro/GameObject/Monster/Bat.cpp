#include "stdafx.h"
#include "Bat.h"
#include "TileManager.h"
#include "TileNode.h"




Bat::Bat(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Monster(name,pos,size)
{

	_RenderPool->Request(this, RenderManager::Layer::Object);
	FrameCount = 0;
	frameX = 0;
	frameY = 0;
	x = pos.x;
	y = pos.y;
	tilesize = size.x;
	startPos = pos;
	endPos = { pos.x + 52.f, pos.y + 52.f };
	speed = D3DXVECTOR2(tilesize, tilesize);

}


Bat::~Bat()
{
}

void Bat::Init()
{
}

void Bat::Release()
{
}

void Bat::ControlUpdate()
{
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
	p2DRenderer->SetCamera(true);
	_ImageManager->FindTexture("bat")->FrameRender(rc, nullptr, frameX, frameY);
}

void Bat::ImguiRender()
{
}



void Bat::MoveAndCheck()
{
}
