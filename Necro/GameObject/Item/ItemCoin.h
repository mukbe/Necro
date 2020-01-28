#pragma once
#include "./GameObject/Item/ItemBase.h"

class ItemCoin : public ItemBase
{
public:
	ItemCoin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemCoin();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();

	virtual void Init(POINT tileIndex);

	virtual void EatItem();

private:
	UINT hasCoin;

};

