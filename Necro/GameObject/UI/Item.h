#pragma once
#include <map>
class Item 
{
public:
	Item(string name,D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Item();




	////���ݷ��� �� ���
	//int NomalWeapon;
	//int BroadSword ;

	map<string,Item*> mapWeapon;

};

