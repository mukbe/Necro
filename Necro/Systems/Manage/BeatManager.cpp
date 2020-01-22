#include "stdafx.h"
#include "BeatManager.h"
#include "./GameObject/TestPlayer.h"
#include "./GameObject/UI/Note.h"

float BeatManager::currentDelta = 0.f;



BeatManager::BeatManager()
{
	saveTime = -4.f;
	syncTime = -0.02f;
	target = nullptr;
	bMusic = false;

	onBeatObjectList.clear();
	onBeatObjectList.push_back("Monster");
	onBeatObjectList.push_back("Heart");
	onBeatObjectList.push_back("");
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
		if (checkInfos.size() <= 0) return false;

		Shown beat = checkInfos.front();
		if (Math::Abs(beat.first - saveTime) <= 0.25f)
		{
			//��Ʈ�� ����ڰ� ���缭 �Է� �޾��� �� �൹�� ������Ʈ��
			//Player, Tile, Item ��  �̰͵� �ܿ��� ��� ������Ʈ���� ���ڿ� ����

			_MessagePool->ReserveMessage(_ObjectPool->FindObject<TestPlayer>("Player"), "OnBeat");
			_MessagePool->ReserveMessage(target, "EnterBeat");
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
	notes.push_back(note);
	notes.erase(notes.begin());
	if(target == nullptr)
		target = note;
}

bool BeatManager::OnBeatObject(GameObject* obj)
{
	for (size_t t = 0; t < onBeatObjectList.size();t++)
	{
		if (obj->Name() == onBeatObjectList[t])
			return true;
	}
	return false;
}

void BeatManager::MusicStart()
{
	if (bMusic == false)
	{
		saveTime = 0.f;
		SOUNDMANAGER->Play("stage1");
		SOUNDMANAGER->SetVolume("stage1", 0.6f);
		bMusic = true;
	}
}

void BeatManager::ReturnNote()
{
	target = nullptr;
	for (size_t t = 0; t < notes.size(); t++)
	{
		if (notes[t]->IsMove())
		{
			target = notes[t];
			break;
		}
	}
}

void BeatManager::Update(float tick)
{

	if (shownInfos.size() > 0)
	{
		saveTime += tick;
		

		if (saveTime >= syncTime)
		{
			MusicStart();
		}

		CheckInputForUpdate();
		if (shownInfos.front().first - shownInfos.front().second <= saveTime)
		{
			float delta = saveTime - (shownInfos.front().first - shownInfos.front().second);
			MakeNote(0, shownInfos.front().second - delta);
			checkInfos.push_back(shownInfos.front());
			shownInfos.pop_front();

		}
		if (checkInfos.size() > 0)
		{
			if (checkInfos.front().first - saveTime <= 0)
			{
				vector<GameObject*> objects = _ObjectPool->objects;
				for (GameObject* obj : objects)
				{
					if (OnBeatObject(obj))
					{
						_MessagePool->ReserveMessage(obj, "OnBeat");
					}
					_MessagePool->ReserveMessage(obj, "AddChance");

				}

				checkInfos.pop_front();
			}
		}

	}
	else
	{
		//�������� ���� �̺�Ʈ
	}


}
