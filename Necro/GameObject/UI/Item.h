#pragma once
#include <map>
class Item 
{
public:
	Item(string name,D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Item();




	////공격력이 될 놈들
	//int NomalWeapon;
	//int BroadSword ;

	map<string,Item*> mapWeapon;

};

