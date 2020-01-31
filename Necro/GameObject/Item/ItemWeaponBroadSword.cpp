#include "stdafx.h"
#include "ItemWeaponBroadSword.h"


ItemWeaponBroadSword::ItemWeaponBroadSword(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemWeapon(name, pos, size)
{
	GameData::WeaponInfo temp;
	temp.Damage = 1;
	temp.Range = { 3,1 };
	temp.Type = Broadsword;
	temp.Imagekey = "Broadsword";
	temp.EffactImagekey = "Swipe_Broadsword";
	SetItemData(temp);
}


ItemWeaponBroadSword::~ItemWeaponBroadSword()
{
}
