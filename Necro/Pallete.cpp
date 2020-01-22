#include "stdafx.h"
#include "Pallete.h"
#include "TileManager.h"
#include "TileNode.h"

/*
	Player
*/
#include "./GameObject/Player.h"
/*
	Monster
*/
#include "./GameObject/Monster/Monster.h"
#include "./GameObject/Monster/Bat.h"
#include "./GameObject/Monster/BlueSlime.h"
#include "./GameObject/Monster/GreenSlime.h"


Pallete::Pallete(D3DXVECTOR2 pivot)
	:pivotPos(pivot), separateSize(5)
{
	for(int i = ObjectTypeBegin; i != ObjectTypeEnd; ++i)
	{
		if (i == ObjectTypeBegin || i == ObjectAll || i == ObjectTypeEnd) continue;

		VecStorage tempStorage;
		objectStorage.insert(make_pair((ObjectType)i, tempStorage));
	}

	string namePal = "Pallete_";
	GameObject* temp;
	//temp = _ObjectPool->CreateObject<Player>(namePal + "Player", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	//AddObject(ObjectPlayer, temp);
	//temp = _ObjectPool->CreateObject<Bat>(namePal + "Bat", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	//AddObject(ObjectMonster, temp);
	//temp = _ObjectPool->CreateObject<BlueSlime>(namePal + "BlueSlime", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	//AddObject(ObjectMonster, temp);
	/*temp = _ObjectPool->CreateObject<GreenSlime>(namePal + "GreenSlime", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	AddObject(ObjectMonster, temp);*/
}

Pallete::~Pallete()
{
}

void Pallete::Init()
{
	
	
}

void Pallete::release()
{
}

void Pallete::update()
{
}

void Pallete::render()
{
}

void Pallete::AddObject(ObjectType type, GameObject * object)
{
	objectStorage[type].push_back(object);
}

void Pallete::DeleteObject(ObjectType type, GameObject * object)
{
	VecIter iter = objectStorage[type].begin(), end = objectStorage[type].end();
	for (; iter != end; ++iter)
	{
		if (*iter == object)
		{
			objectStorage[type].erase(iter);
			--iter;
		}
	}
}

void Pallete::CreatePallete(ObjectType inputType, D3DXVECTOR2 inputPivotPos)
{
	for (int i = 0; i < objectStorage[inputType].size(); ++i)
	{
		float x = pivotPos.x + (i % separateSize) * defaultTileSize.x;
		float y = pivotPos.y + (i / separateSize) * defaultTileSize.y;
		TileNode* newTile = _ObjectPool->CreateObject<TileNode>("", D3DXVECTOR2(x,y), D3DXVECTOR2(defaultTileSize.x, defaultTileSize.y));
		newTile->Init("DefautMap");
		newTile->SetPivotPos(inputPivotPos);
		newTile->AddObject(objectStorage[inputType][i]);
		newTile->SetHighlight(true);
	}
}

void Pallete::ReleasePallete()
{
}
