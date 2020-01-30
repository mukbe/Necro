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



	WeaponInfo getWeaponData() { return weaponData; }

	void setWeaponData(Weapon Type, UINT Range, UINT Damage, string Imagekey) {}
	 

	//���͸� �׿����� �ѹ� ȣ��(���Ͱ� ȣ������ �÷��̾ ȣ������ ���ؾߵ�)
	void Combo();
	
	
	//Ÿ�ϸ� ����Ұ�
	bool BeatForTile() { return bBeat; }
private:

	UINT playerCoin;
	UINT playerBomb;
	UINT playerDia;
	UINT playerHp;

	POINT playerIndex;	// �÷��̾� ��ġ �ε��� 

	WeaponInfo weaponData;
	ShovelInfo shovelDate;
	//ItemHeadInfo HeadDate;

	bool bCombo;
	UINT comboCount;
	int ratioCoin;
	//Ÿ�ϳ�常 ����ҵ�
	bool bBeat;
};
