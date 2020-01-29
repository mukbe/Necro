#include "stdafx.h"
#include "ItemBase.h"
#include "./GameObject/Map/TileNode.h" // Ÿ������ �������� �ø��� ���ؼ� 


ItemBase::ItemBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{

	this->name = name;									// ��� ��ӹ޴� Ŭ���� ������ �ϴ°ͺ��� ���⼭ ó��  �ؿ� �ݹ� ���� ����
	AddCallback("Show", [&](TagMessage msg) {			// �÷��̾� �þ߿� ���� �������� ������ �� 
		bShow = true;									
	});													
	AddCallback("Hide", [&](TagMessage msg) {			// �þ߰� �־��� �Ⱥ��϶� 
		bShow = false;									
	});										

	// ������ �Ծ��� �� 
	AddCallback("EatItem", [&](TagMessage msg) {
		
		if (!IsActive())
		{
			LOG->Print("This Object is inactive");
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
