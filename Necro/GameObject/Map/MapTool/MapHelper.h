#pragma once
#include "stdafx.h"
#include "TileHelper.h"

/*Player*/
#include "./GameObject/Player.h"

/*Monster*/
#include "./GameObject/Monster/Monster.h"

#include "./GameObject/Monster/Bat.h"
#include "./GameObject/Monster/Skeleton.h"
#include "./GameObject/Monster/BlueSlime.h"
#include "./GameObject/Monster/GreenSlime.h"
//¼Ò

/*Wall*/
#include "./GameObject/Map/WallBase.h"
#include "./GameObject/Map/StoneWall.h"

/*Item*/


class Spawner
{
public:
	Spawner(){}
	~Spawner(){}

	void LoadObjects()
	{
		Load<Bat>("M_Bat");
		Load<BlueSlime>("M_BlueSlime");
		Load<GreenSlime>("M_GreenSlime");
		Load<Skeleton>("M_Skeleton");

		Load<WallBase>("W_WallBase");
		Load<WallBase>("W_StoneWall");

		//Load<TileNode>("T_TileNode");
	}

	GameObject* Spawn(string Key)
	{
		 return spawnFuncStorage[Key]();
	}

	unordered_map<string, function<GameObject*(void)>> GetFuncStorage()
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
		Derived* newObject;
		spawnFuncStorage.insert(make_pair(Key, [&](void) {
			newObject = _ObjectPool->CreateObject<Derived>(Key, D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
			return newObject;
		}));

		return newObject;
	}

	unordered_map<string, function<GameObject*(void)>> spawnFuncStorage;
	typedef unordered_map<string, function<GameObject*(void)>>::iterator FuncIter;
};


