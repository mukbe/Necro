#pragma once
#include "./Scenes/SceneBase.h"


class TestScene : public SceneBase
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Init();
	virtual void PreUpdate();


};

