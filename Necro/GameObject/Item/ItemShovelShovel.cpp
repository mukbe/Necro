#include "stdafx.h"
#include "ItemShovelShovel.h"



ItemShovelShovel::ItemShovelShovel(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: ItemShovel(name, pos, size)
{
	GameData::ShovelInfo temp;
	temp.Damge = 1;
	temp.Type = WShovel;
	temp.Imagekey = "Shovel";
	SetItemDate(temp);

}


ItemShovelShovel::~ItemShovelShovel()
{
}
