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
	virtual void EatItem();

	void Init(POINT tileIndex);

	void SetItemData(ShovelType shovelType, UINT Damge,  string IamgeKey)
	{
		info.Type = shovelType;
		info.Damge = Damge;
		info.Imagekey = IamgeKey;
	}
	void SetItemDate(GameData::ShovelInfo info) { this->info = info; }

	GameData::ShovelInfo GetInfo() { return info; }

private:

	GameData::ShovelInfo info;

	ShovelType MyType;

};

