#pragma once
#include "./GameObject/Item/ItemBase.h"
class ItemBoom : public ItemBase
{
public:
	ItemBoom(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemBoom();

	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);
	virtual void Render();
	void Init(POINT tileIndex);

	virtual void EatItem();

private:
	//ÆøÅº 
	UINT hasbomb;
};

