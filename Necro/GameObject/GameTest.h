#pragma once

struct PlayerState
{
	int Hp;				// ü��
	int AttackPower;	// ���ݷ�
	//int PlayerVision;	// �þ� 

};


class GameDate  : public GameObject
{
public:
	GameDate(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~GameDate();

	virtual void Init();
	virtual void Release();
	virtual void update(float tick, TagMessage msg);
	virtual void Render();
	virtual void ImguiRender();

private:
	PlayerState PS;
};

