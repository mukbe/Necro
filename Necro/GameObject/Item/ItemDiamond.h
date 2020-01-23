#pragma once
#include "./GameObject/Item/ItemBase.h"
class ItemDiamond : public ItemBase
{
public:
	ItemDiamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemDiamond();

	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);
	virtual void Render();

private:
	// 타일 뽀개졌을 때 혹은 필드 드랍 되는 위치 / 타일 크기 / 러프 이용한 플레이어와  충돌 했을 때 다이아몬드가 UI 다이아 몬드 위치로 날라감. / 다이아 카운팅

};

