#pragma once
class TestPlayer : public GameObject
{
public:
	TestPlayer(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~TestPlayer();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//��Ʈ�� ����
	virtual void ControlUpdate();
	//���� ��ƾ
	virtual void Update(float tick);

	virtual void Render();


};

