#pragma once
#include "./GameObject/Item/ItemBase.h"

class ItemHead : public ItemBase
{
public:
	ItemHead(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemHead();

	virtual void Init();
	virtual void Release();
	
	virtual void Update(float tick);
	virtual void Render();

	void Init(POINT tileIndex);
	virtual void EatItem();

private:

	//광부 모자 

	GameData::ItemHeadInfo info; // 사이즈, 타일 벽 라이프 가지고 있음. 
	UINT hasHead;
};

