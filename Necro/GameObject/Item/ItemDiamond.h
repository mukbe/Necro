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
	// Ÿ�� �ǰ����� �� Ȥ�� �ʵ� ��� �Ǵ� ��ġ / Ÿ�� ũ�� / ���� �̿��� �÷��̾��  �浹 ���� �� ���̾Ƹ�尡 UI ���̾� ��� ��ġ�� ����. / ���̾� ī����

};

