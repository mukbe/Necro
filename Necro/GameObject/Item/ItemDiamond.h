#pragma once
#include "./GameObject/Item/ItemBase.h"
class ItemDiamond : public ItemBase
{
public:
	ItemDiamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemDiamond();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void Render();
	void Init(POINT tileIndex);

	virtual void EatItem();



private:
	shared_ptr<Texture> itemTex;
	string itemKey;

	UINT hasDia;
};

