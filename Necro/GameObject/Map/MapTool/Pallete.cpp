#include "stdafx.h"
#include "Pallete.h"
#include "./GameObject/Map/TileNode.h"

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

/*
	Wall
*/

#include "./GameObject/Map/WallBase.h"


Pallete::Pallete(D3DXVECTOR2 pivot)
	:pivotPos(pivot), separateSize(5)
{
	for(int i = ObjectTypeBegin; i != ObjectTypeEnd; ++i)
	{
		if (i == ObjectTypeBegin || i == ObjectAll || i == ObjectTypeEnd) continue;

		VecStorage tempStorage;
		objectStorage.insert(make_pair((ObjectType)i, tempStorage));
	}

	LoadObjects();
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
}

void Pallete::CreatePallete(ObjectType inputType, D3DXVECTOR2 inputPivotPos)
{
	for (int i = 0; i < objectStorage[inputType].size(); ++i)
	{
		float x = inputPivotPos.x + (i % separateSize) * defaultTileSize.x;
		float y = inputPivotPos.y + (i / separateSize) * defaultTileSize.y;
		palleteNode* newTile = _ObjectPool->CreateObject<palleteNode>(
			"Pallete" + to_string(i) , D3DXVECTOR2(x, y), D3DXVECTOR2(defaultTileSize.x, defaultTileSize.y));
	
		/*newTile->AddObject(objectStorage[inputType][i]);

		palleteTiles.push_back(newTile);*/
	}
}

void Pallete::ReleasePallete()
{
	PalleteIter iter;

	if(palleteTiles.size() > 0)
	{
		for (int i = 0; i < palleteTiles.size(); ++i)
		{
			iter = palleteTiles.begin() + i;
			_ObjectPool->DeletaObject(palleteTiles[i]);
			palleteTiles.erase(iter);

			--i;
		}
	}
}

void Pallete::LoadObjects()
{
	Load<Player>("Player", ObjectPlayer, RenderManager::Layer::Object);
	
	Load<Bat>("Bat", ObjectMonster, RenderManager::Layer::Object);
	Load<BlueSlime>("BlueSlime", ObjectMonster, RenderManager::Layer::Object);
	Load<GreenSlime>("GreenSlime", ObjectMonster, RenderManager::Layer::Object);

	Load<WallBase>("WallBase", ObjectWall, RenderManager::Layer::Object);
	Load<TileNode>("TileNode", ObjectTerrain, RenderManager::Layer::Terrain);


	/*tring namePal = "Tool";
	GameObject* temp;
	temp = _ObjectPool->CreateObject<Player>(namePal + "Player", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	_RenderPool->Remove(temp, RenderManager::Layer::Object);
	AddObject(ObjectPlayer, temp);
	AddImage(temp);

	


	temp = _ObjectPool->CreateObject<Bat>(namePal + "Bat", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	_RenderPool->Remove(temp, RenderManager::Layer::Object);
	AddObject(ObjectMonster, temp);
	AddImage(temp);

	temp = _ObjectPool->CreateObject<BlueSlime>(namePal + "BlueSlime", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	_RenderPool->Remove(temp, RenderManager::Layer::Object);
	AddObject(ObjectMonster, temp);
	AddImage(temp);

	temp = _ObjectPool->CreateObject<GreenSlime>(namePal + "GreenSlime", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	_RenderPool->Remove(temp, RenderManager::Layer::Object);
	AddObject(ObjectMonster, temp);
	AddImage(temp);




	temp = _ObjectPool->CreateObject<WallBase>(namePal + "WallBase", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	_RenderPool->Remove(temp, RenderManager::Layer::Object);
	AddObject(ObjectWall, temp);
	AddImage(temp);

	temp = _ObjectPool->CreateObject<TileNode>(namePal + "TileNode", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	_RenderPool->Remove(temp, RenderManager::Layer::Terrain);
	AddObject(ObjectTerrain, temp);
	AddImage(temp);
*/
	
}
