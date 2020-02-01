#pragma once
#include "./GameObject/Item/ItemBase.h"
class ItemBody : public ItemBase
{
public:
	ItemBody(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemBody();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();
	void Init(POINT tileIndex);

	virtual void EatItem();
private:
};

