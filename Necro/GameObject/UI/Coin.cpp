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
	//PushCoin(_GameData->GetCoin());
	PushCoin(1234567890);
	font = _ImageManager->FindTexture("NumberFontUI");
	axe = _ImageManager->FindTexture("UI_x");
}

void Coin::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Coin::ControlUpdate()
{
	PushCoin(_GameData->GetCoin());

}

void Coin::Update(float tick)
{
}

void Coin::Render()
{
	_ImageManager->Render("UI_Coin", rc, nullptr);
	
	D3DXVECTOR2 start = position + D3DXVECTOR2(35, 0);

	axe->Render(FloatRect(start, 15, Pivot::TOP), nullptr, 0.8f);

	start = position + D3DXVECTOR2(50, 0);
	D3DXVECTOR2 offset = D3DXVECTOR2(font->GetFrameSize().x * 3.f, 0);
	for (int t = 0; t < coin.size(); t++)
	{
		FloatRect rc(start + offset *(coin.size() - 1 - t), font->GetFrameSize() * 3.f, Pivot::CENTER);
		font->FrameRender(rc, nullptr, coin[t], 0);
	}

}

void Coin::PushCoin(UINT val)
{
	coin.clear();

	UINT temp = val;
	while (temp != 0)
	{
		UINT rest = temp % 10;
		coin.push_back(rest);
		temp *= 0.1f;
	}
	if (coin.empty())
		coin.push_back(0);

}

