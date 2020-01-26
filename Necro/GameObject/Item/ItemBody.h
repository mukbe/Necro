#pragma once
#include "./GameObject/Item/ItemBase.h"
class ItemBody : public ItemBase
{
public:
	ItemBody(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemBody();

	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);
	virtual void Render();

private:
	// 생성되는 타일 위치 / 크기 / 방어력 수치 / 플레이어 정보 전달 / 장착 했을 때 이미지가 바뀜. / 종류는 일단 한개 
};

