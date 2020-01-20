#pragma once
#include <iostream>
#include <fstream>
#include <time.h>

class BeatManager
{
	friend class SceneBase;
public:
	static float currentDelta;
	void LoadText(wstring filePath);

	bool Update(float tick);

private:
	using Beat = pair<float, UINT>;
	//delta, count
	deque<Beat> beats;

	float saveTime;

private:
	BeatManager();
	~BeatManager();

	bool CheckInputForUpdate();
	void ConvertArrayToCount(vector<UINT>& input, deque<Beat>& output);


};

