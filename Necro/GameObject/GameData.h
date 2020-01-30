#pragma once

enum Weapon
{
	Baredhand, Dagger, Spear, Broadsword
};

enum ShovelType
{
	Hand, Shovel, Pickaxe
};

class GameData : public GameObject
{
public:
	
	struct WeaponInfo
	{
		Weapon Type;
		UINT Range;
		UINT Damage;
		string Imagekey;
		WeaponInfo()
			: Range(0), Damage(0)
		{
			Imagekey = "";
			Type = Weapon::Baredhand;
		}
	};
	//�� . ��� 

	struct ShovelInfo
	{
		ShovelType Type;
		UINT life;  // �� �������
		string Imagekey;
		ShovelInfo()
			: life(1)
		{
			Imagekey = "";
			Type = ShovelType::Shovel;
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

	

	void AddDia(UINT val);						// ���̾�
	void AddCoin(UINT val);						// ���� 
	void MinusCoin(UINT val);					// ���� ��� �� ��
	void MinusDia(UINT val);					// ���̾� ��� �� ��
	UINT GetCoin() { return playerCoin; }		// ���� �� 
	UINT GetDia() { return playerDia; }			// ���� ��

	WeaponInfo getWeaponData() { return weaponData; }

	void setWeaponData(Weapon Type, UINT Range, UINT Damage, string Imagekey) {}
	 
private:

	UINT playerCoin;
	UINT playerBomb;
	UINT playerDia;
	UINT playerHp;


	WeaponInfo weaponData;
	ShovelInfo shovelDate;
};
