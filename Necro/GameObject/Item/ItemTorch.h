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
	virtual void EatItem();
	void Init(POINT tileIndex);


	void SetItemData(string IamgeKey)
	{
		info.ImageKey = IamgeKey;
	}

	void SetItemData(GameData::TorchInfo info) { this->info = info; }

	GameData::TorchInfo GetInfo() { return info; }

private:

	GameData::TorchInfo info;

};

