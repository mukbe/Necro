#pragma once
#include "stdafx.h"
#include "TileHelper.h"

/*Player*/
#include "./GameObject/Player.h"

/*Monster*/
#include "./GameObject/Monster/GreenSlime.h"
#include "./GameObject/Monster/BlueSlime.h"
#include "./GameObject/Monster/Bat.h"
#include "./GameObject/Monster/Skeleton.h"
#include "./GameObject/Monster/Ghost.h"
#include "./GameObject/Monster/Monkey.h"

#include "./GameObject/Monster/Minotaur.h"
#include "./GameObject/Monster/RedDragon.h"
#include "./GameObject/Monster/GreenDragon.h"

/* Item */
#include "./GameObject/Item/ItemBase.h"			
#include "./GameObject/Item/ItemShovel.h"		// 삽 or 곡괭
#include "./GameObject/Item/ItemWeapon.h"		// 무기 3종류
#include "./GameObject/Item/ItemDiamond.h"		// 다이아몬드
#include "./GameObject/Item/ItemBody.h"			// 방어구
#include "./GameObject/Item/ItemHead.h"			// 뚝배기
#include "./GameObject/Item/ItemHP.h"			// 체력하트 
#include "./GameObject/Item/ItemCoin.h"			// 동전
#include "./GameObject/Item/ItemTorch.h"
#include "./GameObject/Item/ItemWeaponDagger.h"
#include "./GameObject/Item/ItemWeaponBroadSword.h"
#include "./GameObject/Item/ItemWeaponSpear.h"
#include "./GameObject/Item/ItemShovelShovel.h"
#include "./GameObject/Item/ItemShovelPickaxe.h"

/*Wall*/
#include "./GameObject/Map/WallBase.h"
#include "./GameObject/Map/StoneWall.h"
#include "./GameObject/Map/GravelWall.h"
#include "./GameObject/Map/GoldWall.h"
#include "./GameObject/Map/Door.h"
#include "./GameObject/Map/DoorVertical.h"

/*NPC*/
#include "./GameObject/ShopKeeper.h"


class Spawner
{
public:
	Spawner(){}
	~Spawner(){}

	void LoadObjects()
	{
		/*Player*/
		Load<Player>("P_Player");

		/*NPC*/
		Load<ShopKeeper>("N_ShopKeeper");

		/*Monster*/
		Load<GreenSlime>("M_GreenSlime");
		Load<BlueSlime>("M_BlueSlime");
		Load<Bat>("M_Bat");
		Load<Skeleton>("M_Skeleton");
		//Load<Ghost>("M_Ghost");
		//Load<Monkey>("M_Monkey");

		//Load<Minotaur>("M_Minotaur");
		//Load<RedDragon>("M_RedDragon");
		//Load<GreenDragon>("M_GreenDragon");

		/*Item*/
		Load<ItemDiamond>("I_Diamond");
		Load<ItemWeaponDagger>("I_ItemWeaponDagger");
		Load<ItemWeaponBroadSword>("I_ItemWeaponBroadSword");
		Load<ItemWeaponDagger>("I_ItemWeaponSpear");
		Load<ItemShovelShovel>("I_ItemShovelShovel");
		Load<ItemShovelPickaxe>("I_ItemShovelPickaxe");
		
		/*Wall*/
		Load<WallBase>("W_WallBase");
		Load<StoneWall>("W_StoneWall");
		Load<GravelWall>("W_GravelWall");
		Load<GoldWall>("W_GoldWall");
		Load<Door>("W_Door");
		Load<DoorVertical>("W_DoorVertical");
	}

	GameObject* Spawn(string Key)
	{
		 return spawnFuncStorage[Key](Key);
	}

	unordered_map<string, function<GameObject*(string)>> GetFuncStorage()
	{
		return spawnFuncStorage;
	}

	int GetStorageSize()
	{
		return spawnFuncStorage.size();
	}
private:
	IS_INHERITED_THAN_RETURN(class GameObject) Load(string Key)
	{
		spawnFuncStorage.insert(make_pair(Key, [&](string funcKey) {
			int temp = (*spawnCounter.find(funcKey)).second;
			temp++;
			(*spawnCounter.find(funcKey)).second = temp;
			string interpolation = "";
			if (temp < 1000) interpolation = "0";
			if (temp < 100) interpolation = "00";
			if (temp < 10) interpolation = "000";
			Derived* newObject;
			newObject = _ObjectPool->CreateObject<Derived>(funcKey + interpolation+ to_string(temp), D3DXVECTOR2(0, 0), D3DXVECTOR2(defaultTileSize.x, defaultTileSize.y));

			return newObject;
		}));

		if (spawnCounter.end() == spawnCounter.find(Key))
		{
			spawnCounter.insert(make_pair(Key, 0));
		}
		return nullptr;
	}

	unordered_map<string, function<GameObject*(string)>> spawnFuncStorage;
	typedef unordered_map<string, function<GameObject*(string)>>::iterator FuncIter;

	unordered_map<string, int> spawnCounter;
};


