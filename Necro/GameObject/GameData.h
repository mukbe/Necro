#pragma once

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

	// ������ ���� ���� 
	struct ItemHeadInfo
	{
		UINT Range;
		UINT life;  // Ÿ�� ��  ������ ������ؼ� 
		//ItemHeadInfo()
		// Range(4), life(1)
		//{
		//
		//}
	};

	//�� . ��� 
	enum ItemShovel
	{
		Shovel, Pickaxe
	};

	struct ShovelInfo
	{
		ItemShovel Type;
		UINT life;  // �� �������
		string Imagekey;
		ShovelInfo()
			: life(1)
		{
			Imagekey = "";
			Type = ItemShovel::Shovel;
		}
	};


public:
	GameData(string name ,D3DXVECTOR2 pos, D3DXVECTOR2 size);
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
	UINT GetCoin() { return playerCoin; }		
	UINT GetDia() { return playerDia; }			


	void Combo();

	WeaponInfo getWeaponDate() { return weaponData; }

private:

	UINT playerCoin;
	UINT playerBomb;
	UINT playerDia;
	Weapon weaponinfo;
	WeaponInfo weaponData;
	ShovelInfo shovelDate;
	ItemHeadInfo HeadDate;

	bool bCombo;
	UINT comboCount;
	int ratioCoin;
	//Ÿ�ϳ�常 ����ҵ�
	bool bBeat;
};

