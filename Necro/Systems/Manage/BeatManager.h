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

	void Update(float tick);
	void ReturnNote();

private:
//===== 정보만 받고 사용안함
	using Beat = pair<float, UINT>;
	deque<Beat> beats;
//=====================================

	using Shown = pair<float, float>;
	deque<Shown> shownInfos;
	deque<Shown> checkInfos;

	float saveTime;
	float syncTime;
	
	//메세지를 전달할 노트들
	vector<Note*> notes;
	queue<Note*> freeNoteList;
	//인풋을 받을 노트
	Note* target;
	vector<string> onBeatObjectList;
private:
	BeatManager();
	~BeatManager();

	bool CheckInputForUpdate();
	void ConvertArrayToCount(vector<UINT>& input, deque<Beat>& output);
	void MakeNote(float inputTime, float shownTime);

	//비트에 맞춰서 움직일 객체인가
	bool OnBeatObject(GameObject* obj);


	//TODO 나중에 스테이지 변경할 때 수정해야됨
	void MusicStart();
	bool bMusic;
};

