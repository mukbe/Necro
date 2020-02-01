#pragma once

#include "ItemWeapon.h"

class ItemWeaponDagger : public ItemWeapon
{
public:
	ItemWeaponDagger(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemWeaponDagger();
};

