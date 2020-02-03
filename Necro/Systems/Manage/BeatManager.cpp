#include "stdafx.h"
#include "BeatManager.h"
#include "./GameObject/TestPlayer.h"
#include "./GameObject/UI/Note.h"
#include"./GameObject/Player.h"
#include "./GameObject/Map/MapTool/MapTool.h"
#include "./GameObject/Map/TileNode.h"
#include "./GameObject/UI/Heart.h"

float BeatManager::currentDelta = 0.f;



BeatManager::BeatManager()
{
	saveTime = -4.f;
	syncTime = -0.02f;
	target = nullptr;
	bMusic = false;
	moveMode = MoveMode::MOVE_FREE;
}

BeatManager::~BeatManager()
{
}

bool BeatManager::CheckInputForUpdate()
{
	if (checkInfos.size() > 0)
	{
		Check check = checkInfos.front();

		if (Keyboard::Get()->Down(VK_LEFT)
			|| Keyboard::Get()->Down(VK_RIGHT)
			|| Keyboard::Get()->Down(VK_UP)
			|| Keyboard::Get()->Down(VK_DOWN))
		{
			if (Math::Abs(check.first - saveTime) <= 0.25f)
			{
				if (check.second)
				{
					//플레이어 컨트롤에 의해서 움직여질 오브젝트
					vector<GameObject*> objects = _ObjectPool->objects;
					for (GameObject* obj : objects)
					{
						if (obj->GetMoveType() == MoveType_Control)
						{
							_MessagePool->ReserveMessage(obj, "OnBeat");
						}
					}


					//타일들
					//FloatRect render = CAMERA->GetRenderRect();
					//POINT startIndex = PosToIndex(D3DXVECTOR2(render.left, render.top), TileManager::tileSize, TileManager::pivotPos);
					//POINT endIndex = PosToIndex(D3DXVECTOR2(render.right, render.bottom), TileManager::tileSize, TileManager::pivotPos);

					//startIndex.x = Math::Clamp(startIndex.x - 1, -1, TileManager::mapSize.x);
					//startIndex.y = Math::Clamp(startIndex.y - 1, -1, TileManager::mapSize.y);
					//endIndex.x = Math::Clamp(endIndex.x + 1, -1, TileManager::mapSize.x);
					//endIndex.y = Math::Clamp(endIndex.y + 1, -1, TileManager::mapSize.y);
					//
					//POINT deltaIndex = { endIndex.x - startIndex.x, endIndex.y - endIndex.x };

					//for (LONG y = startIndex.y; y <= endIndex.y; y++)
					//{
					//	for (LONG x = startIndex.x; x <= endIndex.x; x++)
					//	{

					//		GameObject* tile = _TileMap->Tile((int)x, (int)y);
					//		if(tile != nullptr)
					//			_MessagePool->ReserveMessage(tile, "OnBeat");

					//		//생길 수 있는 문제점 
					//		//타일의 움직일 수 있는 찬스가 0에서 고정되는 현상
					//		//해결방안 ControlUpdate를 타일에서 거친 후 마지막에 찬스를 하나 증가
					//		//위에 방식이 맞는것 같다 업데이트 도중 화면 밖으로 넘어가게되면 해줄 수 없다 =>  메세지는 가능하지만 전체를 탐색할 수 없다
					//	}
					//}

					//노트에 사용자가 맞춰서 입력 받았을 때 행돌할 오브젝트들
					//Player, Tile, Item 등  이것들 외에는 모두 업데이트에서 박자에 맞춤
					_MessagePool->ReserveMessage(target, "EnterBeat");

					checkInfos.front().second = false;

				}
			}
			else if (Math::Abs(check.first - saveTime) > 0.25f && Math::Abs(check.first - saveTime) < 0.505f)
			{

				if (checkInfos.front().second == true)
				{
					_MessagePool->ReserveMessage(_GameData, "Miss");
					_MessagePool->ReserveMessage(target, "EnterBeat");
					//너무 빨리 눌렀다면
					checkInfos.front().second = false;
				}
				_MessagePool->ReserveMessage(_ObjectPool->FindObject<Heart>("Heart"), "Miss");

			}
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
		freeNoteList.push(note);
	}
	notes.clear();

	currentMusicName = Path::GetFileNameWithoutExtension(String::WStringToString( filePath));
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
	Note* note = freeNoteList.front();
	freeNoteList.pop();
	//TODO 노트수가 적으면 생성해줄 코드가 필요하다

	_MessagePool->ReserveMessage(note, "Shown", 0, float(shownTime));
	notes.push_back(note);

	if (shownInfos.size() < 30)
	{
		note->SetRedNote();
	}

	//처음엔 타겟이 없기때문에 맨 처음 타겟을 정해주기 위함
	if (target == nullptr)
		target = note;

}

void BeatManager::MusicStart()
{
	if (bMusic == false)
	{
		saveTime = 0.f;
		SOUNDMANAGER->Play("stage1");
		SOUNDMANAGER->SetVolume("stage1", 0.3f);
		bMusic = true;
	}
}

void BeatManager::ReturnNote()
{
	if (notes.empty()) return;

	Note* note = notes.front();

	while (note->GetState() != Note::Note_Move)
	{
		freeNoteList.push(note);
		notes.erase(notes.begin());
		if (notes.empty())
		{
			note = nullptr;
			break;
		}
		note = notes.front();
	}
	target = note;
}

void BeatManager::Update(float tick)
{
	if (Keyboard::Get()->Down(VK_F3))
	{
		if (moveMode == MoveMode::MOVE_FREE)
		{
			 moveMode = MoveMode::MOVE_MUSIC;
		}
		else if (moveMode == MoveMode::MOVE_MUSIC)
		{
			 moveMode = MoveMode::MOVE_FREE;
		}
	}


	if (moveMode == MoveMode::MOVE_FREE)
	{
		vector<GameObject*> objects = _ObjectPool->objects;
		for (GameObject* obj : objects)
		{
			if (obj->GetMoveType() == MoveType_Control)
			{
				_MessagePool->ReserveMessage(obj, "OnBeat");
				_MessagePool->ReserveMessage(obj, "AddChance");
			}

			//필요하면 타일들도 해줌
		}

	}
	else if (moveMode == MoveMode::MOVE_MUSIC)
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
				checkInfos.push_back(make_pair(shownInfos.front().first, true));
				shownInfos.pop_front();

			}
			if (checkInfos.size() > 0)
			{
				if (checkInfos.front().first - saveTime <= 0)
				{
					vector<GameObject*> objects = _ObjectPool->objects;
					for (GameObject* obj : objects)
					{
						if (obj->GetMoveType() == MoveType_Beat)
						{
							_MessagePool->ReserveMessage(obj, "OnBeat");
						}
						_MessagePool->ReserveMessage(obj, "AddChance");

					}

					if (checkInfos.front().second == true)
					{
						_MessagePool->ReserveMessage(_GameData, "Miss");
					}
					checkInfos.pop_front();
				}
			}

		}
		else
		{
			//스테이지 끝남 이벤트
		}
	}//else if (moveMode == MoveMode::MOVE_MUSIC)

}
