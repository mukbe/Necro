#pragma once
#include "./GameObject/Item/ItemBase.h"
class ItemShovel : public ItemBase
{
public:
	ItemShovel(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemShovel();

	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);
	virtual void Render();

private:
	// 횃불 아이템 / 타일 위치 / 플레이어 시야 증가 
};

