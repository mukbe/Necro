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
	// ����  �ִ� ü�¿��� ���� // ��Ʈ �ִ� ü�� ����  // ���� ����� �Ȱ��� 
};

