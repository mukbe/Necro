#include "stdafx.h"
#include "ItemWeaponDagger.h"


ItemWeaponDagger::ItemWeaponDagger(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemWeapon(name, pos, size)
{
	GameData::WeaponInfo temp;
	temp.Damage = 1;
	temp.Range = { 1,1 };
	temp.Type = WDagger;
	temp.Imagekey = "Dagger";
	temp.EffactImagekey = "Swipe_Dagger";
	SetItemData(temp);
}


ItemWeaponDagger::~ItemWeaponDagger()
{
}
