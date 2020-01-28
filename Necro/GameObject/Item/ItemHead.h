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

	//���� ���� 
	// ũ�� , ��ġ�� �Ȱ��� / �÷��̾� ���� ���ڰ� �������� ������ �μ�  / ���簡���� �ִ� �𺸴� �Ѵܰ� �� ���� ������Ʈ ���� �ı� ���� 

};

