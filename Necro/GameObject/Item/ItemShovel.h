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
	virtual void Init(POINT tileIndex);

private:
	// ȶ�� ������ / Ÿ�� ��ġ / �÷��̾� �þ� ���� 
};

