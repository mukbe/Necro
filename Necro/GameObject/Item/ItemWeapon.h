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
	virtual void Update();
	virtual void Render();
	virtual void EatItem();

	void Init(POINT tileIndex);

	void SetItemData(Weapon weaponType, POINT weaponRange, UINT weaponDamage, string weaponEffectImageKey, string iconImageKey)
	{
		info.Type = weaponType;
		info.Range = weaponRange;
		info.Damage = weaponDamage;
		info.Imagekey = weaponEffectImageKey;
		textureKey = iconImageKey;
	}



private: 
	
	GameData::WeaponInfo info;

	Weapon myType;

	string textureKey;
	 
};

