#include "stdafx.h"
#include "Heart.h"



Heart::Heart(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddFrameTexture("HeartTemp", ResourcePath + L"UI/TempHeart.png", 2, 1);

	hold = 0;
	frameTime = 0.f;
	_RenderPool->Request(this, RenderManager::Layer::UI);
	AddCallback("OnBeat", [&](TagMessage msg) {
		hold = true;
	});


}


Heart::~Heart()
{
}

void Heart::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Heart::ControlUpdate()
{
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
	p2DRenderer->SetCamera(false);
	_ImageManager->FrameRender("HeartTemp", rc, nullptr, (UINT)hold, 0);
}
