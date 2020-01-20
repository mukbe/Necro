#pragma once

#include "./GameObject/Player.h"

class TestScene;
class Program
{

public:
	Program();
	~Program();

	void PreUpdate();
	void Update(float tick);
	void PostUpdate();

	void Render();

	void PostRender();
	void ImguiRender();
	void GameUIRender();

	void ResizeScreen();


private:
	Player* player;

};