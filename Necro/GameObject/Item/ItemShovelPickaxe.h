#pragma once

#include "ItemShovel.h"

class ItemShovelPickaxe : public ItemShovel
{
public:
	ItemShovelPickaxe(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemShovelPickaxe();
};

