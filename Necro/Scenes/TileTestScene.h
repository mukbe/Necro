#pragma once
#include "./Scenes/SceneBase.h"
#include "TileManager.h"

class TileTestScene : public SceneBase
{
public:
	TileTestScene();
	~TileTestScene();

	virtual void Init();

	TileManager* testTileManager;

};

