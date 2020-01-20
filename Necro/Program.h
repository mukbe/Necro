#pragma once


class TestScene;
class Program
{

public:
	Program();
	~Program();

	void ControlUpdate();
	void Update(float tick);
	void PostUpdate();

	void Render();

	void PostRender();
	void ImguiRender();
	void GameUIRender();

	void ResizeScreen();


private:


};