#include "stdafx.h"
#include "Diamond.h"
#include "UIBase.h"

Diamond::Diamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
}

Diamond::~Diamond()
{
}

void Diamond::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	
#ifdef DEBUGMODE
	PushCount(1234567890);
#else
	PushCount(_GameData->GetDia());
#endif // DEBUGMODE

	font = _ImageManager->FindTexture("NumberFontUI");
	axe = _ImageManager->FindTexture("UI_x");

}

void Diamond::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Diamond::ControlUpdate()
{
	PushCount(_GameData->GetDia());
}

void Diamond::Update(float tick)
{
	UIBase::Update(tick);
	if (bMove == false)
	{
		itemTex.reset();
	}

}

void Diamond::Render()
{
	UIBase::Render();

	_ImageManager->FrameRender("Diamond", rc, nullptr);

	D3DXVECTOR2 start = position + D3DXVECTOR2(35, 0);

	axe->Render(FloatRect(start, 15, Pivot::TOP), nullptr, 0.8f);

	start = position + D3DXVECTOR2(50, 0);
	D3DXVECTOR2 offset = D3DXVECTOR2(font->GetFrameSize().x * 3.f, 0);
	for (int t = 0; t < count.size(); t++)
	{
		FloatRect rc(start + offset * (count.size() - 1 - t), font->GetFrameSize() * 3.f, Pivot::CENTER);
		font->FrameRender(rc, nullptr, count[t], 0);
	}

}

void Diamond::EatItem(string key)
{
	string temp = key.substr(2, key.size()-7);
	itemTex = _ImageManager->FindTexture(temp);
}

void Diamond::PushCount(UINT val)
{
	count.clear();

	UINT temp = val;
	while (temp != 0)
	{
		UINT rest = temp % 10;
		count.push_back(rest);
		temp *= 0.1f;
	}
	if (count.empty())
		count.push_back(0);

}


