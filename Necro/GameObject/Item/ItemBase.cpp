#include "stdafx.h"
#include "ItemBase.h"
#include "./GameObject/Map/TileNode.h" // 타일위에 아이템을 올리기 위해서 


ItemBase::ItemBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{

	this->name = name;									// 모든 상속받는 클래스 일일히 하는것보단 여기서 처리  밑에 콜백 또한 같음
	AddCallback("Show", [&](TagMessage msg) {			// 플레이어 시야에 따라 아이템이 보여질 때 
		bShow = true;									
	});													
	AddCallback("Hide", [&](TagMessage msg) {			// 시야가 멀어져 안보일때 
		bShow = false;									
	});										

	// 아이템 먹었을 때 
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
	position = _TileMap->Tile(tileIndex)->GetPos();							// 타일위치 검출!  
	rc.Update(position, TileManager::tileSize * 0.85f, Pivot::CENTER);		// 타일위치에 렉트 , 사이즈 , 그릴 위치 
	
}

void ItemBase::EatItem()
{
	// 오류 떴을 때 
	LOG->Warning(__FILE__, __LINE__, "아이템 먹었는데 재정의 안해서 뜨는 오류 ");
}
