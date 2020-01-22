#include "stdafx.h"
#include "Coin.h"
#include "UIBase.h"


Coin::Coin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
}


Coin::~Coin()
{
}


void Coin::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);

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

CoinCount::CoinCount(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Coin(name, pos, size)
{
	

}

CoinCount::~CoinCount()
{
}

void CoinCount::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
}

void CoinCount::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void CoinCount::Update(float tick)
{
}

void CoinCount::Render()
{
	p2DRenderer->SetCamera(false);
	_ImageManager->Render("UI_CoinX", rc, nullptr);
}
