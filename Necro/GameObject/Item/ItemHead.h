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

	virtual void Init(POINT tileIndex);

private:

	//광부 모자 
	// 크기 , 위치는 똑같므 / 플레이어 기준 십자가 방향으로 벽들을 부숨  / 현재가지고 있는 삽보다 한단계 더 높은 오브젝트 까지 파괴 가능 

};

