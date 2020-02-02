#pragma once
#include "TileHelper.h"


class TileNode;
class Spawner;

class TileManager
{
public:
	static POINT mapSize;
	static D3DXVECTOR2 tileSize;
	static D3DXVECTOR2 pivotPos;

	static void SetMapInfo(POINT tileMax, D3DXVECTOR2 size, D3DXVECTOR2 mapPivot);

private:
	friend class SceneBase;
	friend class MapTool;
	friend class Pallete;
	

public:
	TileManager();
	~TileManager();


	TileNode* Tile(POINT index);
	TileNode* Tile(int x, int y);

	vector<TileNode*> GetArray();

	POINT GetMapSize() { return mapSize; }
	D3DXVECTOR2 GetTileSize() { return tileSize; }
	D3DXVECTOR2 GetPivotPos() { return pivotPos; }

	Spawner* GetSpawner() { return spawner; }

	void CreateMap();

	void HighLightOn();

	void SetAllActive();

	void SaveMap(wstring mapName);
	void LoadMap(wstring mapName);
	int LoadMapData(vector<string> input);

	D3DXVECTOR2 GetPlayerSpawn() { return playerSpawn; }
	void SetPlayerSpawn(D3DXVECTOR2 input) { playerSpawn = input; }

	void ActiveAll();

private:
	typedef vector<TileNode*>::iterator VecIter;
	vector<TileNode*> mapTiles;

	Spawner* spawner;

	string textureName;

	D3DXVECTOR2 playerSpawn;

	void Release();


	void ReleaseMap();

	void SetMapSize(POINT input)
	{
		ReleaseMap();
		mapSize = input;
		CreateMap();
		
	}
	void SetTileSize(D3DXVECTOR2 input)
	{
		ReleaseMap();
		tileSize = input;
		CreateMap();
	}
	void SetPivotPos(D3DXVECTOR2 input)
	{
		ReleaseMap();
		pivotPos = input;
		CreateMap();
	}

	void SetTexture(string key);
};