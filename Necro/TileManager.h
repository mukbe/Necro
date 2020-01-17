#pragma once
#include "TileHelper.h"


class TileNode;

class TileManager
{
public:
	TileManager();
	~TileManager();

	void Release();
	void PreUpdate();
	void Update(float tick);
	void PostUpdate();
	void Render();
	void ImguiRender();

	void CreateMap();
private:
	unordered_map<string, TileNode*> mapTiles;
	typedef unordered_map<string, TileNode*>::iterator MapIter;
	typedef vector<TileNode*> vecTiles;
	typedef vector<TileNode*> VecIter;
	
};

