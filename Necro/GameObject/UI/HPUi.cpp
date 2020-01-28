#include "stdafx.h"
#include "HPUi.h"
#include "UIBase.h"

HPUi::HPUi(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	hold = 0; //bool = false;
	frameTime = 0.f;
}

HPUi::~HPUi()
{
}

void HPUi::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	
}

void HPUi::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void HPUi::ControlUpdate()
{
	hold = true;  //키 입력을 받았을 때 true 값을 받고 
}

void HPUi::Update(float tick)
{
	if (hold) // 참일 때 
	{
		frameTime += tick; 
		if (frameTime >= holdTime)
		{
			frameTime -= holdTime;
			hold = false;
		}
	}
}

void HPUi::Render()
{
	p2DRenderer->SetCamera(false);

	_ImageManager->FrameRender("HpTemp", rc, nullptr,(UINT)hold,0);
	
}
