#include "stdafx.h"
#include "ItemWeapon.h"

ItemWeapon::ItemWeapon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name, pos, size)
{
	bShow = false;

	//아이템 정보 보내보기 
	AddCallback("SendDaggerDate", [&](TagMessage msg)
	{
		//데미지 // 러프로 인벤토리 해야함. // 범위 
	});
	AddCallback("SendBroadswordDate", [&](TagMessage)
	{ 
		// 데미지  // 범위 // 1인 공격
	});
	AddCallback("SendSpearDate", [&](TagMessage) 
	{
		// 데미지 // 범위 // 1인 공격 
	});

}

ItemWeapon::~ItemWeapon()
{
}

void ItemWeapon::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void ItemWeapon::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ItemWeapon::ControlUpdate()
{
}

void ItemWeapon::Update()
{
}

void ItemWeapon::Render()
{
	_ImageManager->FindTexture("Broadsword")->FrameRender(rc, nullptr, 0, (UINT)bShow);
	_ImageManager->FindTexture("Dagger")->FrameRender(rc, nullptr, 0, (UINT)bShow);
	_ImageManager->FindTexture("Spear")->FrameRender(rc, nullptr,0,(UINT)bShow);
}

void ItemWeapon::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}
