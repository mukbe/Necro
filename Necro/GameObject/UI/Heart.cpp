#include "stdafx.h"
#include "Heart.h"



Heart::Heart(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{

	hold = 0;
	frameTime = 0.f;

}


Heart::~Heart()
{
}

void Heart::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
}

void Heart::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Heart::ControlUpdate()
{
	hold = true;
}

void Heart::Update(float tick)
{
	if (hold)
	{
		frameTime += tick;
		if (frameTime >= holdTime)
		{
			frameTime -= holdTime;
			hold = false;
		}
	}
}

void Heart::Render()
{
	_ImageManager->FrameRender("HeartTemp", rc, nullptr, (UINT)hold, 0);
}
