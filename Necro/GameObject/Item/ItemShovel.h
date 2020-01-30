#pragma once
#include "./GameObject/Item/ItemBase.h"
class ItemShovel : public ItemBase
{
public:
	ItemShovel(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemShovel();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void Render();
	void Init(POINT tileIndex);
	virtual void EatItem();
private:

	GameData::ShovelInfo info;


};

