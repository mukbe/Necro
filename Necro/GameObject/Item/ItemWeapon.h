#pragma once
#include "./GameObject/Item/ItemBase.h"

class ItemWeapon : public ItemBase
{
public:
	ItemWeapon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemWeapon();

	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update();
	virtual void Render();

	virtual void Init(POINT tileIndex);
private: 
	// 타일 위치 / 타일 크기 /  공격력 / 공격 범위 / 무기 뭐든 먹었을 때 슬롯 위치로 이동하는 이미지가 있음 (러프) / 플레이어에게 전달할 방법 
	int Dmage;



};

