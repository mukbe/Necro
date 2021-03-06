#include "stdafx.h"
#include "ItemBase.h"
#include "./GameObject/Map/TileNode.h" // 타일위에 아이템을 올리기 위해서 

ItemBase::ItemBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: GameObject(name, pos, size)
{

	this->name = name;									// 모든 상속받는 클래스 일일히 하는것보단 여기서 처리  밑에 콜백 또한 같음
	SetCost(0);


	// 아이템 먹었을 때 
	AddCallback("EatItem", [&](TagMessage msg) {
		
		if (!IsActive())
		{
			LOG->Print("This Object is inactive");
			return;
		}
		if (!CanBuyItem())
		{
			LOG->Error(__FILE__, __LINE__, "Not Enough Money, Plz Check 'CanBuyItem' on Player");
			return;
		}
		EatItem();
	});
	
}

ItemBase::~ItemBase()
{
}

void ItemBase::Init()
{
}

void ItemBase::Release()
{
}

void ItemBase::Update(float tick)
{
}

void ItemBase::Render()
{
	if (cost != 0 && bShow != false)
	{
		shared_ptr<Texture> font = _ImageManager->FindTexture("NumberFontUI");
		D3DXVECTOR2 offset = D3DXVECTOR2(font->GetFrameSize().x * 1.75f, 0);

		D3DXVECTOR2 start = position - (int)(text.size() / 2) * offset;


		for (int t = 0; t < text.size(); t++)
		{
			FloatRect rc(start + offset * (text.size() - 1 - t) + D3DXVECTOR2(0,50.f), font->GetFrameSize() * 1.75f, Pivot::CENTER);
			font->FrameRender(rc, nullptr, text[t], 0);
		}

	}

}

void ItemBase::Init(POINT tileIndex)
{
	position = _TileMap->Tile(tileIndex)->GetPos();							// 타일위치 검출!  
	rc.Update(position , TileManager::tileSize * 0.85f, Pivot::CENTER);		// 타일위치에 렉트 , 사이즈 , 그릴 위치 
}

void ItemBase::EatItem()
{
	// 오류 떴을 때 
	LOG->Warning(__FILE__, __LINE__, "아이템 먹었는데 재정의 안해서 뜨는 오류 ");
}

void ItemBase::Show()
{
	bShow = true;
}

void ItemBase::Hide()
{
	bShow = false;
}

void ItemBase::Active()
{
	bActive = true;
}
void ItemBase::SetCost(UINT val)
{
	cost = val;
	PushCount(cost);
}

bool ItemBase::CanBuyItem()
{
	return	(cost <= _GameData->GetCoin());
}

void ItemBase::PushCount(UINT val)
{
	text.clear();

	UINT temp = val;
	while (temp != 0)
	{
		UINT rest = temp % 10;
		text.push_back(rest);
		temp *= 0.1f;
	}
	if (text.empty())
		text.push_back(0);

}
