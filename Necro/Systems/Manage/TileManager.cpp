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
		saveOut << "ObjectContainer:" << endl;

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
		saveOut << endl;
	}
	saveOut.close();
}

void TileManager::LoadMap(wstring mapName)
{
	ifstream loadIn;
	loadIn.open(ResourcePath + L"/MapData/" + mapName + L".map", ios_base::in);

	vector<string> tempLines;
	
	string buffer;

	while (!loadIn.eof())
	{
		getline(loadIn, buffer);
		tempLines.push_back(buffer);
	}
	loadIn.close();

	vector<string>::iterator lineIter = tempLines.begin(), lineEnd = tempLines.end();

	int cnt = LoadMapData(tempLines);
	CreateMap();
	
	char abc[15];
	int target = 0;

	while (cnt < tempLines.size())
	{
		if (tempLines[cnt] == "")
		{
			++cnt;
			continue;
		}
		tempLines[cnt].copy(abc, 1, 0);
		if (abc[0] == '[') 
		{
			tempLines[cnt].copy(abc,9, 12);
			target = atoi(abc);
			++cnt;
			mapTiles[target]->SetTextureKey(tempLines[cnt].substr(11,tempLines[cnt].size()-11));
			++cnt;
			mapTiles[target]->SetAttribute((AttributeType)stoi(tempLines[cnt].substr(10,1)));
			cnt = cnt + 2;
			
			//if (tempLines[i] == "")continue;

			vector<int> vecPoint;

			for (int i = 0; i < tempLines[cnt].size(); ++i)
			{
				if (tempLines[cnt][i] == ',')
				{
					vecPoint.push_back(i);
				}
			}

			if (vecPoint.size() > 0)
			{
				for (int i = 0; i < vecPoint.size(); ++i)
				{
					int begin = 0;
					if (i != 0) begin = i-1;

					char tempKey[20];
					//tempLines[cnt].substr(begin,);
					// 여까지 했고.. substr 제대로 되게 고쳐야 댐.

					ObjectType tempType;
					
					switch (tempKey[0])
					{
					case 'T':
						tempType = ObjectTerrain;
						break;
					case 'P':
						tempType = ObjectPlayer;
						break;
					case 'M':
						tempType = ObjectMonster;
						break;
					case 'I':
						tempType = ObjectItem;
						break;
					case 'N':
						tempType = ObjectNPC;
						break;
					case 'W':
						tempType = ObjectWall;
						break;
					}
					GameObject* newObject = spawner->Spawn(tempKey);
					mapTiles[target]->AddObject(tempType, newObject);
					newObject->SetPosition(mapTiles[target]->Transform().GetPos());
				}
			}
		}
		cnt++;
	}

	/*
	saveOut << "TextureKey:" + tempTile->GetTextureKey() << endl;
	saveOut << "Attribute:" + to_string(tempTile->GetAttribute()) << endl;
	saveOut << "ObjectContainer:";*/
}

int TileManager::LoadMapData(vector<string> input)
{
	int i = 0;
	if (input[i] == "[MapSize]")
	{
		++i;
		int point = input[i].find(',') + 1;
		mapSize.x = stoi(input[i].substr(point, input[i].size()));
		mapSize.y = stoi(input[i].substr(0, point));
	}
	++i;
	if (input[i] == "[TileSize]")
	{
		++i;
		int point = input[i].find(',') + 1;
		tileSize.x = stoi(input[i].substr(point, input[i].size()));
		tileSize.y = stoi(input[i].substr(0, point));
	}
	++i;
	if (input[i] == "[PivotPosition]")
	{
		++i;
		int point = input[i].find(',') + 1;
		pivotPos.x = stoi(input[i].substr(point, input[i].size()));
		pivotPos.y = stoi(input[i].substr(0, point));
	}
	++i;
	return i;
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
