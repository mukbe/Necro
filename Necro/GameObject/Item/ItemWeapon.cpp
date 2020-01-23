#include "stdafx.h"
#include "ItemWeapon.h"

ItemWeapon::ItemWeapon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name, pos, size)
{
	bShow = false;

	//������ ���� �������� 
	AddCallback("Dagger", [&](TagMessage msg)
	{
		//������ // ������ �κ��丮 �ؾ���. // ���� 
	});
	AddCallback("BrodSword", [&](TagMessage)
	{ 
		// ������  // ���� // 1�� ����
	});
	AddCallback("Spear", [&](TagMessage) 
	{
		// ������ // ���� // 1�� ���� 
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
	_ImageManager->FindTexture("Dagger")->FrameRender(rc, nullptr, 0, (UINT)bShow);
	_ImageManager->FindTexture("Spear")->FrameRender(rc, nullptr,0,(UINT)bShow);
	_ImageManager->FindTexture("BrodSword")->FrameRender(rc, nullptr, 0, 0, (UINT)bShow);
}

void ItemWeapon::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}
