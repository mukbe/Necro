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

//Minus 는 상점 관련 
void GameData::MinusCoin(UINT val)
{
	//상점 관련 
	if (playerCoin < val)
	{
		//못 사는데 왜 넘겨줌?
	}
	playerCoin -= (int)val;
}

void GameData::MinusDia(UINT val)
{
	if (playerDia < val)
	{
		// 역시 못 산다 . 
	}
	playerDia -= (int)val;
}

void GameData::Combo()
{
	//이미 콤보값이 있었을 경우
	if (bCombo)
	{
		comboCount++;
		ratioCoin = 2 + (int)(comboCount / 3);
	}
	bCombo = true;
}
