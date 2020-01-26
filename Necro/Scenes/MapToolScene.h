#pragma once
#include "./Scenes/SceneBase.h"
#include "./GameObject/Map/MapTool/MapTool.h"

class MapToolScene : public SceneBase
{
public:
	MapToolScene();
	~MapToolScene();

	virtual void Init();

	MapTool* tool;

	void LoadResource();
};

