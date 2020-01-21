#pragma once
#include "./Scenes/SceneBase.h"
#include "MapTool.h"

class MapToolScene : public SceneBase
{
public:
	MapToolScene();
	~MapToolScene();

	virtual void Init();

	MapTool* tool;
};

