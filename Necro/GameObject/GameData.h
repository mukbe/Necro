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
	//삽 . 곡괭이 

	struct ShovelInfo
	{
		ShovelType Type;
		UINT life;  // 벽 까기위한
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
	void PosRedefinition(POINT pos);					// 플레이어 위치 재정의

	UINT GetCoin() { return playerCoin; }		
	UINT GetDia() { return playerDia; }	
	POINT GetIndex() {return playerIndex;}



	WeaponInfo getWeaponData() { return weaponData; }

	void setWeaponData(Weapon Type, UINT Range, UINT Damage, string Imagekey) {}
	 

	//몬스터를 죽였을때 한번 호출(몬스터가 호출할지 플레이어가 호출할지 정해야됨)
	void Combo();
	
	
	//타일만 사용할것
	bool BeatForTile() { return bBeat; }
private:

	UINT playerCoin;
	UINT playerBomb;
	UINT playerDia;
	UINT playerHp;

	POINT playerIndex;	// 플레이어 위치 인덱스 

	WeaponInfo weaponData;
	ShovelInfo shovelDate;
	//ItemHeadInfo HeadDate;

	bool bCombo;
	UINT comboCount;
	int ratioCoin;
	//타일노드만 사용할듯
	bool bBeat;
};
