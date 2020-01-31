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
		POINT Range;
		UINT Damage;
		string EffactImagekey;
		string Imagekey;
		WeaponInfo()
			: Range({ 0,1 }), Damage(1)
		{
			Imagekey = "";
			EffactImagekey = "";
			Type = Weapon::Dagger;
		}
	};

	//�� . ��� 
	struct ShovelInfo
	{
		ShovelType Type;
		UINT Damge;  
		string Imagekey;
		ShovelInfo()
			: Damge(1)
		{
			Imagekey = "";
			Type = ShovelType::Shovel;
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
	void PosRedefinition(POINT pos);					// �÷��̾� ��ġ ������

	UINT GetCoin() { return playerCoin; }		
	UINT GetDia() { return playerDia; }	
	POINT GetIndex() {return playerIndex;}


	ShovelInfo GetShovelData() { return shovelData; }
	WeaponInfo GetWeaponData() { return weaponData; }
	void SetWeaponData(WeaponInfo weaponInfo);
	void SetShovelData(ShovelInfo shovelInfo);

	//���͸� �׿����� �ѹ� ȣ��(���Ͱ� ȣ������ �÷��̾ ȣ������ ���ؾߵ�)
	void Combo();
	//������ ���
	void UseItem();
	//void Use

	
	//Ÿ�ϸ� ����Ұ�
	bool BeatForTile() { return bBeat; }
private:

	UINT playerCoin;
	UINT playerBomb;
	UINT playerDia;
	UINT playerHp;

	POINT playerIndex;	// �÷��̾� ��ġ �ε��� 

	WeaponInfo weaponData;
	ShovelInfo shovelData;

	bool bCombo;
	UINT comboCount;
	int ratioCoin;
	//Ÿ�ϳ�常 ����ҵ�
	bool bBeat;
};
