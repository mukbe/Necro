#pragma once
class ShopKeeper : public GameObject
{

	int frameX, frameY;			// ������ ������
	float interver;				// ������ ���͹� 
	float loudness;				// �Ҹ� ũ�� 
	D3DXVECTOR2 distance;		// �÷��̾���� �Ÿ� 

public:
	ShopKeeper(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	 ~ShopKeeper();
	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();

	//���� ��ƾ -> ��Ÿ ������Ʈ �ֱ� 
	virtual void Update(float tick);

	virtual void Render();
};

