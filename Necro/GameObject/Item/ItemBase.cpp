#include "stdafx.h"
#include "ItemBase.h"
#include "./GameObject/Map/TileNode.h" // Ÿ������ �������� �ø��� ���ؼ� 

// �÷��̾� ���� �׸��ڶ� �̹��� Ȯ�� �ϱ� 
// �� ���̽� Ȯ���ϸ� �� Ű���̶� ��� ����� 
// �ε����� �� �������� ������ִ°�

 
ItemBase::ItemBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: GameObject(name, pos, size)
{

	this->name = name;									// ��� ��ӹ޴� Ŭ���� ������ �ϴ°ͺ��� ���⼭ ó��  �ؿ� �ݹ� ���� ����
	SetCost(0);


	// ������ �Ծ��� �� 
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
	if (cost != 0)
	{
		shared_ptr<Texture> font = _ImageManager->FindTexture("NumberFontUI");
		D3DXVECTOR2 offset = D3DXVECTOR2(font->GetFrameSize().x * 1.75f, 0);

		D3DXVECTOR2 start = position - (int)(text.size() / 2) * offset;


		for (int t = 0; t < text.size(); t++)
		{
			FloatRect rc(start + offset * (text.size() - 1 - t) + D3DXVECTOR2(0,30.f), font->GetFrameSize() * 1.75f, Pivot::CENTER);
			font->FrameRender(rc, nullptr, text[t], 0);
		}
	}

		
}

void ItemBase::Init(POINT tileIndex)
{
	position = _TileMap->Tile(tileIndex)->GetPos();							// Ÿ����ġ ����!  
	rc.Update(position, TileManager::tileSize * 0.85f, Pivot::CENTER);		// Ÿ����ġ�� ��Ʈ , ������ , �׸� ��ġ 	

}

void ItemBase::EatItem()
{
	// ���� ���� �� 
	LOG->Warning(__FILE__, __LINE__, "������ �Ծ��µ� ������ ���ؼ� �ߴ� ���� ");
}

void ItemBase::Show()
{
	bShow = false;
}

void ItemBase::Hide()
{
	bShow = true;
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
