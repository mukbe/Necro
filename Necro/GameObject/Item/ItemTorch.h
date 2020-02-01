#pragma once
#include "./GameObject/Item/ItemBase.h"

class ItemTorch :public ItemBase
{

public:
	ItemTorch(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemTorch();

	virtual void Init();
	virtual void Release();

	virtual void Update(float tick);
	virtual void Render();
	void Init(POINT tileIndex);

	virtual void EatItem();

private:



};

