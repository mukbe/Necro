#include "stdafx.h"
#include "Pallete.h"
#include "MapHelper.h"


Pallete::Pallete(D3DXVECTOR2 pivot)
	:pivotPos(pivot), separateSize(5)
{
	for(int i = ObjectTypeBegin; i != ObjectTypeEnd; ++i)
	{
		if (i == ObjectTypeBegin || i == ObjectAll || i == ObjectTypeEnd) continue;

		VecStorage tempStorage;
		objectStorage.insert(make_pair((ObjectType)i, tempStorage));
	}
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

	char mark;

	switch (inputType)
	{
	case ObjectAll:
		break;
	case ObjectTerrain:
		mark = 'T';
		break;
	case ObjectPlayer:
		mark = 'P';
		break;
	case ObjectMonster:
		mark = 'M';
		break;
	case ObjectItem:
		mark = 'I';
		break;
	case ObjectNPC:
		mark = 'N';
		break;
	case ObjectWall:
		mark = 'W';
		break;
	}

	Spawner* tempSpawner = _GameWorld->GetTileManager()->GetSpawner();
	unordered_map<string, function<GameObject*(string)>> tempStorage = tempSpawner->GetFuncStorage();
	unordered_map<string, function<GameObject*(string)>>::iterator
		iter = tempStorage.begin(),
		end = tempStorage.end();

	int i = 0;

	for (; iter != end; ++iter)
	{
		if ((*iter).first.at(0) == mark)
		{
			float x = inputPivotPos.x + (i % separateSize) * defaultTileSize.x;
			float y = inputPivotPos.y + (i / separateSize) * defaultTileSize.y;
			palleteNode* newTile = _ObjectPool->CreateObject<palleteNode>(
				"Pallete" + to_string(i), D3DXVECTOR2(x, y),
				D3DXVECTOR2(defaultTileSize.x, defaultTileSize.y));

			newTile->SetData("Tool" + (*iter).first.substr(2, (*iter).first.size()), (*iter).first);
			vecPallete.push_back(newTile);
			++i;
		}
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