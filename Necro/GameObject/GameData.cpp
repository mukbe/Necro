#include "stdafx.h"
#include "GameData.h"

GameData::GameData(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	moveType = MoveType_Control;


	playerCoin = 0;
	playerDia = 0;
	bBeat = false;
}
GameData::~GameData()
{
}

void GameData::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
}

void GameData::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}

void GameData::ControlUpdate()
{
	bBeat = !bBeat;
}

void GameData::MissControlUpdate()
{
	bCombo = false;
	ratioCoin = 1.f;
	comboCount = 0;
}

void GameData::Update(float tick)
{
	switch (weaponinfo)
	{
	case GameData::Dagger:
		// �ܰ� �Ӽ� 
		break;
	case GameData::Spear:
		// â 
		break;
	case GameData::Broadsword:
		// ��� 
		break;
	default:
		break;
	}
}


void GameData::Render()
{

}

void GameData::ImguiRender()
{
}

void GameData::AddDia(UINT val)
{
	playerDia += val;
}

void GameData::AddCoin(UINT val)
{
	playerCoin += val;
}

//Minus �� ���� ���� 
void GameData::MinusCoin(UINT val)
{
	//���� ���� 
	if (playerCoin < val)
	{
		//�� ��µ� �� �Ѱ���?
	}
	playerCoin -= (int)val;
}

void GameData::MinusDia(UINT val)
{
	if (playerDia < val)
	{
		// ���� �� ��� . 
	}
	playerDia -= (int)val;
}

void GameData::Combo()
{
	//�̹� �޺����� �־��� ���
	if (bCombo)
	{
		comboCount++;
		ratioCoin = 2 + (int)(comboCount / 3);
	}
	bCombo = true;
}
