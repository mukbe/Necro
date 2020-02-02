#include "stdafx.h"
#include "ItemWeaponSpear.h"


ItemWeaponSpear::ItemWeaponSpear(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemWeapon(name, pos, size)
{
	GameData::WeaponInfo temp;
	temp.Damage = 1;
	temp.Range = { 2,0 };
	temp.Type = WSpear;
	temp.Imagekey = "Spear";
	temp.EffactImagekey = "Swipe_Spear";
	SetItemData(temp);
}


ItemWeaponSpear::~ItemWeaponSpear()
{
}
