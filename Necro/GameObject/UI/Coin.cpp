#include "stdafx.h"
#include "Coin.h"



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
	_ImageManager->Render("UI_Coin", rc, nullptr);

}

