#include "stdafx.h"
#include "BeatManager.h"

float BeatManager::currentInterval = 0.f;

BeatManager::BeatManager()
{
	LoadText(ResourcePath + L"zone.txt");
	saveTime = 0.f;

}

BeatManager::~BeatManager()
{
}

void BeatManager::LoadText(wstring filePath)
{
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

	currentInterval = beats.front().first;

}

void BeatManager::ConvertArrayToCount(vector<UINT>& input, deque<pair<float, UINT>>& output)
{
	UINT oldDelta = 0;
	UINT oldtime = 0;
	for (UINT time : input)
	{
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

}

bool BeatManager::Update(float tick)
{
	if (beats.size() > 0)
	{
		saveTime += tick;
		if (saveTime >= beats.front().first)
		{
			beats.front().second--;
			if (beats.front().second == 0)
				beats.pop_front();

			currentInterval = beats.front().first;



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
