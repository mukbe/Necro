#pragma once
#include "./GameObject/Item/ItemBase.h"

class ItemWeapon : public ItemBase
{
public:
	ItemWeapon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemWeapon();

	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);
	virtual void Render();
	virtual void EatItem();

	void Init(POINT tileIndex);

	void SetItemData(Weapon weaponType, POINT weaponRange, UINT weaponDamage, string weaponEffectImageKey, string iconImageKey)
	{
		info.Type = weaponType;
		info.Range = weaponRange;
		info.Damage = weaponDamage;
		info.EffactImagekey = weaponEffectImageKey;
		info.Imagekey = iconImageKey;
	}
	void SetItemData(GameData::WeaponInfo info) { this->info = info; }

	GameData::WeaponInfo GetInfo() { return info; }

private: 
	
	GameData::WeaponInfo info;

	Weapon myType;

};

