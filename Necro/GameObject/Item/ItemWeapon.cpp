#include "stdafx.h"
#include "ItemWeapon.h"

ItemWeapon::ItemWeapon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name, pos, size)
{
	bShow = false;

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
	Log_ErrorAssert(info.Imagekey == "");
	if (info.Imagekey == "")return;
	_ImageManager->FindTexture(info.Imagekey)->FrameRender(rc, nullptr, 0, (UINT)bShow);
}

void ItemWeapon::EatItem()
{
	//_GameData->ChangeWeapon(info);
}

void ItemWeapon::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}
