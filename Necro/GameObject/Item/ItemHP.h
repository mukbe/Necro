#pragma once
#include "./GameObject/Item/ItemBase.h"
class ItemHP : public ItemBase
{
public:
	ItemHP(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemHP();

	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);
	virtual void Render();
private:
	// 음식  최대 체력에서 증가 // 하트 최대 체력 증가  // 이하 기능은 똑같음 
};

