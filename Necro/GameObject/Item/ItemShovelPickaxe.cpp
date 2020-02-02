#include "stdafx.h"
#include "ItemShovelPickaxe.h"




ItemShovelPickaxe::ItemShovelPickaxe(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: ItemShovel(name, pos, size)
{
	GameData::ShovelInfo temp;
	temp.Damge = 1;
	temp.Type = WPickaxe;
	temp.Imagekey = "Pickaxe";
	SetItemDate(temp);


}

ItemShovelPickaxe::~ItemShovelPickaxe()
{
} 
