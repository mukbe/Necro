#pragma once

#include "ItemWeapon.h"

class ItemWeaponSpear : public ItemWeapon
{
public:
	ItemWeaponSpear(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemWeaponSpear();
};

