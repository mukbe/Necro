#pragma once
#include <iostream>
#include <fstream>
#include <time.h>

class Note;
class BeatManager
{
	friend class SceneBase;
public:
	static float currentDelta;
	void LoadText(wstring filePath);

	bool Update(float tick);
	void ReturnNote();

private:
	using Beat = pair<float, UINT>;
	using Shown = pair<float, float>;

	deque<Shown> shownInfos;
	deque<Beat> beats;
	float saveTime;


	vector<Note*> notes;
	Note* targetNote;



private:
	BeatManager();
	~BeatManager();

	bool CheckInputForUpdate();
	void ConvertArrayToCount(vector<UINT>& input, deque<Beat>& output);
	void MakeNote(float inputTime, float shownTime);
};

