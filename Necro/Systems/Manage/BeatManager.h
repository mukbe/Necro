#pragma once
#include <iostream>
#include <fstream>
#include <time.h>


//�ӵ��� �������ٸ� �޼����� ���ؼ� ȣ���ϴ��� ����ȣ��� ����


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
//===== ������ �ް� ������
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
	
	//�޼����� ������ ��Ʈ��
	vector<Note*> notes;
	queue<Note*> freeNoteList;
	//��ǲ�� ���� ��Ʈ
	Note* target;
	
private:
	BeatManager();
	~BeatManager();

	bool CheckInputForUpdate();
	void ConvertArrayToCount(vector<UINT>& input, deque<Beat>& output);
	void MakeNote(float inputTime, float shownTime);



	//TODO ���߿� �������� ������ �� �����ؾߵ�
	void MusicStart();
	bool bMusic;
};

