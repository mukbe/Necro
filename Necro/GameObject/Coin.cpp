#include "stdafx.h"
#include "Coin.h"
#include "UIBase.h"


Coin::Coin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_Coin", ResourcePath + L"UI/COIN.png");
}


Coin::~Coin()
{
}

void Coin::Release()
{
}

void Coin::ControlUpdate()
{
}

void Coin::Update(float tick)
{
}

void Coin::Render()
{
	_ImageManager->Render("UI_Coin", FloatRect({ 1200,50}, { 50,50 }, Pivot::CENTER), nullptr);
}
