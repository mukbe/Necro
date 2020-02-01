#include "TileManager.h"
#include "./GameObject/Map/TileNode.h"
#include "./GameObject/Map/MapTool/MapHelper.h"

POINT TileManager::mapSize = defaultMapSize;
D3DXVECTOR2 TileManager::tileSize = { 0.f,0.f };
D3DXVECTOR2 TileManager::pivotPos = { 0.f,0.f };

void TileManager::SetMapInfo(POINT tileMax, D3DXVECTOR2 size, D3DXVECTOR2 mapPivot)
{
	mapSize = tileMax;
	tileSize = size;
	pivotPos = mapPivot;
}

TileManager::TileManager()
{
	spawner = new Spawner();
	spawner->LoadObjects();
}

TileManager::~TileManager()
{
}

void TileManager::SetTexture(string key)
{
	textureName = key;
}

void TileManager::Release()
{
}


void TileManager::CreateMap()
{
	ReleaseMap();

	for (int i = 0; i < mapSize.x * mapSize.y; ++i)
	{
		float x = (i % mapSize.x) * (tileSize.x ) + pivotPos.x;
		float y = (i / mapSize.x) * (tileSize.y ) + pivotPos.y;

		TileNode* newTile = _ObjectPool->CreateObject<TileNode>("TileNode", D3DXVECTOR2(x, y), D3DXVECTOR2(tileSize.x, tileSize.y));

		newTile->SetData("DefaultMap");

		newTile->SetPivotPos(pivotPos);

		mapTiles.push_back(newTile);
	}
}

void TileManager::HighLightOn()
{
	if (mapTiles.size() > 0)
	{
		for (int i = 0; i < mapTiles.size(); ++i)
		{
			mapTiles[i]->SetHighlight(true);
		}
	}
}

void TileManager::SetAllActive()
{
	if (mapTiles.size() > 0)
	{
		for (int i = 0; i < mapTiles.size(); ++i)
		{
			mapTiles[i]->Active();
			mapTiles[i]->Show();
		}
	}
}

void TileManager::SaveMap(wstring mapName)
{
	ofstream saveOut;
	saveOut.open(ResourcePath + L"/MapData/" + mapName + L".map");
	
	saveOut << "[MapSize]" << endl;
	saveOut << to_string(mapSize.x) + "," + to_string(mapSize.y) << endl;
	saveOut << "[TileSize]" << endl;
	saveOut << to_string(tileSize.x) + "," + to_string(tileSize.y) << endl;
	saveOut << "[PivotPosition]" << endl;
	saveOut << to_string(pivotPos.x) + "," + to_string(pivotPos.y) << endl << endl;

	for (int i = 0; i < mapTiles.size(); ++i)
	{
		TileNode* tempTile = mapTiles[i];
		string interpolation = "";
		if (i < 1000) interpolation = "0";
		if (i < 100) interpolation = "00";
		if (i < 10) interpolation = "000";
		saveOut << "[TileNode" + interpolation + to_string(i) + "]" << endl;
		saveOut << "TextureKey:" + tempTile->GetTextureKey() << endl;
		saveOut << "Attribute:" + to_string(tempTile->GetAttribute()) << endl;
		saveOut << "ObjectContainer:";

		unordered_map<ObjectType, vector<GameObject*>> tempStorage = mapTiles[i]->GetStorage();
		unordered_map<ObjectType, vector<GameObject*>>::iterator tempIter = tempStorage.begin(), tempEnd = tempStorage.end();
		for (; tempIter != tempEnd; ++tempIter)
		{
			vector<GameObject*> tempVector = (*tempIter).second;
			vector<GameObject*>::iterator vectorIter = tempVector.begin(), vectorEnd = tempVector.end();

			for (; vectorIter != vectorEnd; ++vectorIter)
			{
				saveOut << (*vectorIter)->Name() + ",";
			}
		}
		saveOut << endl << endl;
	}
}

void TileManager::LoadMap(wstring mapName)
{

}

void TileManager::ReleaseMap()
{
	if (mapTiles.size() > 0)
	{
		for (int i = 0; i < mapTiles.size(); ++i)
		{
			_ObjectPool->DeletaObject(mapTiles[i]);

			//VecIter iter = mapTiles.begin() + i;
			//(*iter)->Release();
			//mapTiles.erase(iter);
			//--i;
		}
		mapTiles.clear();
	}
}



TileNode* TileManager::Tile(POINT index)
{
	if (index.x < 0 || index.y < 0 || index.x >= mapSize.x || index.y >= mapSize.y)
	{
		return nullptr;
	}

	return mapTiles[index.y * mapSize.x + index.x];
}

TileNode * TileManager::Tile(int x, int y)
{
	if (x < 0 || y < 0 || x >= mapSize.x || y >= mapSize.y)
	{
		return nullptr;
	}

	return mapTiles[y * mapSize.x + x];
}

vector<TileNode*> TileManager::GetArray()
{
	return mapTiles;
}
