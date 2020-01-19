#pragma once
#include <iostream>
#include <fstream>
#include <time.h>

class BeatManager
{
	friend class SceneBase;
public:
	static float currentInterval;

	void LoadText(wstring filePath);
	void ConvertArrayToCount(vector<UINT>& input, deque<pair<float, UINT>>& output);

	bool Update(float tick);

private:
	//delta, count
	deque<pair<float, UINT>> beats;

	float saveTime;

private:
	BeatManager();
	~BeatManager();

	bool CheckInputForUpdate();



};

