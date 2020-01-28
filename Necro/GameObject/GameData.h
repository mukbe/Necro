#pragma once

struct PlayerState
{
	int Hp;				// ü��
	int AttackPower;	// ���ݷ�
	//int PlayerVision;	// �þ� 

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
	//��Ʈ�� ����
	virtual void ControlUpdate();
	//��Ʈ�� �� ������ ��� ( Movetype_Control�� �ش���)
	virtual void MissControlUpdate();
	//���� ��ƾ
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

