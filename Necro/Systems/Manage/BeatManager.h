#pragma once
#include <iostream>
#include <fstream>
#include <time.h>


//속도가 느려진다면 메세지를 통해서 호출하던걸 직접호출로 변경


class Note;
class BeatManager
{
	friend class SceneBase;
public:
	enum class MoveMode
	{
		MOVE_MUSIC,
		MOVE_FREE
	};

	static float currentDelta;
	void LoadText(wstring filePath);

	void Update(float tick);
	void ReturnNote();

	MoveMode GetMode() { return moveMode; }
	void SetMode(MoveMode mode) { moveMode = mode; }
	string CurrentMusic() { return currentMusicName; }
private:
//===== 정보만 받고 사용안함
	using Beat = pair<float, UINT>;
	deque<Beat> beats;
//=====================================
	string currentMusicName;

	MoveMode moveMode;
	using Shown = pair<float, float>;
	deque<Shown> shownInfos;
	using Check = pair<float, bool>;
	deque<Check> checkInfos;

	float saveTime;
	float syncTime;
	
	//메세지를 전달할 노트들
	vector<Note*> notes;
	queue<Note*> freeNoteList;
	//인풋을 받을 노트
	Note* target;
	
private:
	BeatManager();
	~BeatManager();

	bool CheckInputForUpdate();
	void ConvertArrayToCount(vector<UINT>& input, deque<Beat>& output);
	void MakeNote(float inputTime, float shownTime);



	//TODO 나중에 스테이지 변경할 때 수정해야됨
	void MusicStart();
	bool bMusic;
};

