#pragma once
#include "./Scenes/SceneBase.h"
#include "TileManager.h"
#include "./GameObject/Player.h"

class TileTestScene : public SceneBase
{
public:
	TileTestScene();
	~TileTestScene();

	virtual void Init();

	TileManager* testTileManager;
	Player* player;

};

  