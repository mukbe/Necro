#include "stdafx.h"
#include "Coin.h"
#include "UIBase.h"


Coin::Coin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_Coin", ResourcePath + L"UI/COIN.png");
}


Coin::~Coin()
{
}

void Coin::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Coin::ControlUpdate()
{
}

void Coin::Update(float tick)
{
}

void Coin::Render()
{
	//카메라 설정 
	p2DRenderer->SetCamera(false);
	_ImageManager->Render("UI_Coin", rc, nullptr);
	
}
