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

	// 아이템 광부 모자 
	struct ItemHeadInfo
	{
		UINT Range;
		UINT life;  // 타일 벽  라이프 깍기위해서 
		//ItemHeadInfo()
		// Range(4), life(1)
		//{
		//
		//}
	};

	//삽 . 곡괭이 
	enum ItemShovel
	{
		Shovel, Pickaxe
	};

	struct ShovelInfo
	{
		ItemShovel Type;
		UINT life;  // 벽 까기위한
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
	//컨트롤 관련
	virtual void ControlUpdate();
	//노트를 못 눌렀을 경우 ( Movetype_Control만 해당함)
	virtual void MissControlUpdate();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();
	virtual void ImguiRender();

	

	void AddDia(UINT val);						// 다이아
	void AddCoin(UINT val);						// 코인 
	void MinusCoin(UINT val);					// 코인 사용 할 때
	void MinusDia(UINT val);					// 다이아 사용 할 때
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
	//타일노드만 사용할듯
	bool bBeat;
};

