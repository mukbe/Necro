#include "stdafx.h"
#include "BeatManager.h"
#include "./GameObject/TestPlayer.h"
#include "./GameObject/UI/Note.h"

float BeatManager::currentDelta = 0.f;



BeatManager::BeatManager()
{
	saveTime = 0.f;

}

BeatManager::~BeatManager()
{
}

bool BeatManager::CheckInputForUpdate()
{

	if (Keyboard::Get()->Down(VK_LEFT)
		||	Keyboard::Get()->Down(VK_RIGHT) 
		||	Keyboard::Get()->Down(VK_UP) 
		||	Keyboard::Get()->Down(VK_DOWN))
	{
		Beat beat = beats.front();
		if (Math::Abs(beat.first - saveTime) <= 0.3f)
		{
			_MessagePool->ReserveMessage(_ObjectPool->FindObject<TestPlayer>("Player"), "OnBeat");
			_MessagePool->ReserveMessage(_ObjectPool->FindObject<Note>("Note"), "save");
		}
	}



	return false;
}

void BeatManager::LoadText(wstring filePath)
{
	ifstream r;
	string str;
	r.open(filePath, ios::in);
	//���� �о
	while (!r.eof())
	{
		//�Ϻ����� ���� ���� ������ �����߻�
		//�ذ�� �ϴ� �����̳� �ȿ� �� �޾ƿͼ� string��ü�� �Լ��� ������ ã�Ƽ� ������ �����ָ��
		//���ͳ� �����̽��� �������� ������
		r >> str;
	}
	
	//�����ϰ�
	vector<string> temp;
	string tok = ",";
	String::SplitString(&temp, str, tok);

	//uint�� ��ȯ�Ѵ�
	vector<UINT> times;
	for (string s : temp)
	{
		times.push_back((UINT)stoul(s, nullptr, 0));
	}

	//delta �� ī��Ʈ�� ���·� �����̳��� ũ�⸦ ����
	ConvertArrayToCount(times, beats);

	notes = _ObjectPool->FindObjects<Note>("Note");
	for (Note* note : notes)
	{
		note->Init();
	}
}

void BeatManager::ConvertArrayToCount(vector<UINT>& input, deque<pair<float, UINT>>& output)
{
	UINT oldDelta = 0;
	UINT oldtime = 0;
	for (UINT time : input)
	{
		shownInfos.push_back(make_pair((float)(time / 1000.f), 2.f));
		UINT delta = 0;
		//�ð� �ϳ��� �޾Ƽ� �������� ��
		delta = time - oldtime;
		if (delta == 0)continue;

		//���հ��� ���ο�Ÿ� �����̳ʿ� �ϳ� �� ���
		if (delta != oldDelta)
		{
			float temp = delta / 1000.f;
			output.push_back(make_pair(temp, 0));
		}
		//�װ� �ƴϸ� ī��Ʈ ����
		output[output.size() - 1].second += 1;


		oldtime = time;
		oldDelta = delta;
	}
	currentDelta = beats.front().first;
}

void BeatManager::MakeNote(float inputTime, float shownTime)
{
	Note* note = notes.front();
	_MessagePool->ReserveMessage(note, "Shown", 0, float(shownTime));


}

void BeatManager::ReturnNote()
{
	notes.push_back(notes.front());
	notes.erase(notes.begin());
}

bool BeatManager::Update(float tick)
{
	if (beats.size() > 0)
	{
		saveTime += tick;
		CheckInputForUpdate();
		if (saveTime >= beats.front().first)
		{
			beats.front().second--;
			if (beats.front().second == 0)
				beats.pop_front();

			//MakeNote()
			vector<GameObject*> objects = _ObjectPool->objects;
			for (GameObject* obj : objects)
			{
				if (obj->Name() == "Player")
				{
					_MessagePool->ReserveMessage(obj, "AddChance");
					continue;
				}
				_MessagePool->ReserveMessage(obj, "OnBeat");
			}

			currentDelta = beats.front().first;
			saveTime = 0;
			return true;
		}

	}
	else
	{
		//�������� ���� �̺�Ʈ
	}
	return false;
}
