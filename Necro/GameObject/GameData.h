#pragma once

struct PlayerState
{
	int Hp;				// 체력
	int AttackPower;	// 공격력
	//int PlayerVision;	// 시야 

};


class GameData : public GameObject
{
public:
	enum Weapon
	{
		Dagger, Spear, Broadsword
	};
	struct WeaponInfo
	{
		Weapon Type;
		UINT Range;
		UINT Damage;
		string Imagekey;
		WeaponInfo()
			: Range(1), Damage(1)
		{
			Imagekey = "";
			Type = Weapon::Dagger;
		}
	};

public:
	GameData(string name = "GameData");
	virtual~GameData();

	virtual void Init();
	virtual void Release();
	//컨트롤 관련
	virtual void ControlUpdate();
	//노트를 못 눌렀을 경우 ( Movetype_Control만 해당함)
	virtual void MissControlUpdate();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();
	virtual void ImguiRender();

	void AddCoin(UINT val);
	void MinusCoin(UINT val);
	UINT GetCoin() { return playerCoin; }

private:
	UINT playerCoin;
	WeaponInfo weaponData;

};

