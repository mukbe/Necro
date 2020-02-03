#pragma once
#include "./Scenes/SceneBase.h"

class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();

	virtual void Init();

	//===for Init()==========
	void ImageLoad();
};

