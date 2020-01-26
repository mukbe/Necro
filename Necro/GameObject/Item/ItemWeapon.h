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
	// Ÿ�� ��ġ / Ÿ�� ũ�� /  ���ݷ� / ���� ���� / ���� ���� �Ծ��� �� ���� ��ġ�� �̵��ϴ� �̹����� ���� (����) / �÷��̾�� ������ ��� 
	int Dmage;



};

