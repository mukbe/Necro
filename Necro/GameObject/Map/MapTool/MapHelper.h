#pragma once
#include "stdafx.h"

#include "Pallete.h"
#include "./GameObject/Map/TileNode.h"

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

class Spawner
{
public:
	Spawner(){}
	~Spawner(){}

	void LoadObjects()
	{
		Load<Bat>("Bat");
		Load<BlueSlime>("BlueSlime");
		Load<GreenSlime>("GreenSlime");
		Load<Skeleton>("Skeleton");

		Load<WallBase>("WallBase");
		Load<WallBase>("StoneWall");
		Load<TileNode>("TileNode");
	}

	GameObject* Spawn(string Key)
	{
		 return spawnFuncStorage[Key]();
	}
private:
	template<typename T>
	GameObject* Load(string Key)
	{
		GameObject* newObject;
		spawnFuncStorage.insert(make_pair(Key, [&](void) {
			newObject = _ObjectPool->CreateObject<T>(Key, D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
			return newObject;
		}));

		return newObject;
	}

	unordered_map<string, function<GameObject*(void)>> spawnFuncStorage;
	typedef unordered_map<string, function<GameObject*(void)>>::iterator FuncIter;
};


