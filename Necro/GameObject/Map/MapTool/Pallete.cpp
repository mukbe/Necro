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
	ReleasePallete();

	for (int i = 0; i < objectStorage[inputType].size(); ++i)
	{
		float x = inputPivotPos.x + (i % separateSize) * defaultTileSize.x;
		float y = inputPivotPos.y + (i / separateSize) * defaultTileSize.y;
		palleteNode* newTile = _ObjectPool->CreateObject<palleteNode>(
			"Pallete" + to_string(i) , D3DXVECTOR2(x, y), D3DXVECTOR2(defaultTileSize.x, defaultTileSize.y));

		newTile->SetData(objectStorage[inputType][i]->Name(),objectStorage[inputType][i]);

		vecPallete.push_back(newTile);
	}
}

void Pallete::ReleasePallete()
{
	PalleteIter iter;

	if(vecPallete.size() > 0)
	{
		for (int i = 0; i < vecPallete.size(); ++i)
		{
			iter = vecPallete.begin() + i;
			_ObjectPool->DeletaObject(vecPallete[i]);
			vecPallete.erase(iter);

			--i;
		}
	}
}

void Pallete::LoadObjects()
{
	GameObject* temp = Load<Player>("Player", ObjectPlayer, RenderManager::Layer::Object);
	_RenderPool->Remove(temp, RenderManager::Layer::Imgui);
	
	Load<Bat>("Bat", ObjectMonster, RenderManager::Layer::Object);
	Load<BlueSlime>("BlueSlime", ObjectMonster, RenderManager::Layer::Object);
	Load<GreenSlime>("GreenSlime", ObjectMonster, RenderManager::Layer::Object);
	Load<Skeleton>("Skeleton", ObjectMonster, RenderManager::Layer::Object);

	Load<WallBase>("WallBase", ObjectWall, RenderManager::Layer::Object);
	Load<WallBase>("StoneWall", ObjectWall, RenderManager::Layer::Object);
	Load<TileNode>("TileNode", ObjectTerrain, RenderManager::Layer::Terrain);
}
