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
					//�÷��̾� ��Ʈ�ѿ� ���ؼ� �������� ������Ʈ
					vector<GameObject*> objects = _ObjectPool->objects;
					for (GameObject* obj : objects)
					{
						if (obj->GetMoveType() == MoveType_Control)
						{
							_MessagePool->ReserveMessage(obj, "OnBeat");
						}
					}


					//Ÿ�ϵ�
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

					//		//���� �� �ִ� ������ 
					//		//Ÿ���� ������ �� �ִ� ������ 0���� �����Ǵ� ����
					//		//�ذ��� ControlUpdate�� Ÿ�Ͽ��� ��ģ �� �������� ������ �ϳ� ����
					//		//���� ����� �´°� ���� ������Ʈ ���� ȭ�� ������ �Ѿ�ԵǸ� ���� �� ���� =>  �޼����� ���������� ��ü�� Ž���� �� ����
					//	}
					//}

					//��Ʈ�� ����ڰ� ���缭 �Է� �޾��� �� �൹�� ������Ʈ��
					//Player, Tile, Item ��  �̰͵� �ܿ��� ��� ������Ʈ���� ���ڿ� ����
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
					//�ʹ� ���� �����ٸ�
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
	Note* note = freeNoteList.front();
	freeNoteList.pop();
	//TODO ��Ʈ���� ������ �������� �ڵ尡 �ʿ��ϴ�

	_MessagePool->ReserveMessage(note, "Shown", 0, float(shownTime));
	notes.push_back(note);

	if (shownInfos.size() < 30)
	{
		note->SetRedNote();
	}

	//ó���� Ÿ���� ���⶧���� �� ó�� Ÿ���� �����ֱ� ����
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

			//�ʿ��ϸ� Ÿ�ϵ鵵 ����
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
			//�������� ���� �̺�Ʈ
		}
	}//else if (moveMode == MoveMode::MOVE_MUSIC)

}
