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


private:
	// 좌표 , 크기, 금액
	// 타일의 인덱스 / 타일 크기 / 랜덤금액 설정 
	// 전달할방법 등  
};

