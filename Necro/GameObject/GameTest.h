#pragma once

struct PlayerState
{
	int Hp;				// 체력
	int AttackPower;	// 공격력
	//int PlayerVision;	// 시야 

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

