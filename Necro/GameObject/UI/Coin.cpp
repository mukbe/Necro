#include "stdafx.h"
#include "Coin.h"



Coin::Coin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	//hold = 0;
	//frameTime = 0.f;
}


Coin::~Coin()
{
}


void Coin::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_Coin", ResourcePath + L"UI/UI_Coin.png");
	
}

void Coin::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Coin::ControlUpdate()
{
	//hold = true;
}

void Coin::Update(float tick)
{
	/*if (hold)
	{
		frameTime += tick;
		if (frameTime >= holdTime)
		{
			frameTime -= holdTime;
			hold = false;
		}
	}*/
}

void Coin::Render()
{
	//카메라 설정 
	_ImageManager->Render("UI_Coin", rc, nullptr);
	_ImageManager->FrameRender("Field_coin", rc, nullptr, 0, 0); //(UINT)hold);

	

}

//
//// 코인 동전 카운팅 
//CoinCount::CoinCount(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
//	:Coin(name, pos, size)
//{
//}
//CoinCount::~CoinCount()
//{
//}
//void CoinCount::Init()
//{
//	_RenderPool->Request(this, RenderManager::Layer::UI);
//	//_ImageManager->AddTexture("UI_x", ResourcePath + L"Font/UI_x.png");
//}
//void CoinCount::Release()
//{
//	_RenderPool->Remove(this, RenderManager::Layer::UI);
//}
//void CoinCount::Update(float tick)
//{
//}
//void CoinCount::Render()
//{
//	p2DRenderer->SetCamera(false);
//	//_ImageManager->Render("UI_x", rc, nullptr);
//}
