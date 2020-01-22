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
//===== ������ �ް� ������
	using Beat = pair<float, UINT>;
	deque<Beat> beats;
//=====================================

	using Shown = pair<float, float>;
	deque<Shown> shownInfos;
	deque<Shown> checkInfos;

	float saveTime;
	float syncTime;
	
	//�޼����� ������ ��Ʈ��
	vector<Note*> notes;
	queue<Note*> freeNoteList;
	//��ǲ�� ���� ��Ʈ
	Note* target;
	vector<string> onBeatObjectList;
private:
	BeatManager();
	~BeatManager();

	bool CheckInputForUpdate();
	void ConvertArrayToCount(vector<UINT>& input, deque<Beat>& output);
	void MakeNote(float inputTime, float shownTime);

	//��Ʈ�� ���缭 ������ ��ü�ΰ�
	bool OnBeatObject(GameObject* obj);


	//TODO ���߿� �������� ������ �� �����ؾߵ�
	void MusicStart();
	bool bMusic;
};

