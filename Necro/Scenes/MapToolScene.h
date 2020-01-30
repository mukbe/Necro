#pragma once
#include "./Scenes/SceneBase.h"
#include "./GameObject/Map/MapTool/MapTool.h"

static MapTool* tool;

class MapToolScene : public SceneBase
{
public:
	MapToolScene();
	~MapToolScene();

	virtual void Init();

	void LoadResource();
};

