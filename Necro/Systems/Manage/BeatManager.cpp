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
			//노트에 사용자가 맞춰서 입력 받았을 때 행돌할 오브젝트들
			//Player, Tile, Item 등  이것들 외에는 모두 업데이트에서 박자에 맞춤

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
	//파일 읽어서
	while (!r.eof())
	{
		//완벽하지 않음 띄어쓰기 있으면 문제발생
		//해결법 일단 컨테이너 안에 다 받아와서 string자체의 함수로 공백을 찾아서 지워서 합쳐주면됨
		//엔터나 스페이스를 기준으로 가져옴
		r >> str;
	}
	
	//분할하고
	vector<string> temp;
	string tok = ",";
	String::SplitString(&temp, str, tok);

	//uint로 변환한다
	vector<UINT> times;
	for (string s : temp)
	{
		times.push_back((UINT)stoul(s, nullptr, 0));
	}

	//delta 와 카운트의 형태로 컨테이너의 크기를 감소
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
		//시간 하나를 받아서 전에꺼랑 비교
		delta = time - oldtime;
		if (delta == 0)continue;

		//차잇값이 새로운거면 컨테이너에 하나 더 등록
		if (delta != oldDelta)
		{
			float temp = delta / 1000.f;
			output.push_back(make_pair(temp, 0));
		}
		//그게 아니면 카운트 증가
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
		//스테이지 끝남 이벤트
	}


}
