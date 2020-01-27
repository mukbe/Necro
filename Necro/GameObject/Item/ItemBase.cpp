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

void ItemBase::ControlUpdate()
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
