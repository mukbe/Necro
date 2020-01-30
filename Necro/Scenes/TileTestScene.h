#pragma once
#include "./Scenes/SceneBase.h"

class TileTestScene : public SceneBase
{
public:
	TileTestScene();
	~TileTestScene();

	virtual void Init();

	//===for Init()==========
	void ImageLoad();
	void MonsterLoad();

};

  