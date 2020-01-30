#include "stdafx.h"
#include "GameData.h"

GameData::GameData(string name)
	:GameObject(name)
{
	moveType = MoveType_Custom;

	weaponinfo = Dagger;

	playerCoin = 0;
	playerDia = 0;
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
}

void GameData::MissControlUpdate()
{
}

void GameData::Update(float tick)
{
	switch (weaponinfo)
	{
	case GameData::Dagger:
		// 단검 속성 
		break;
	case GameData::Spear:
		// 창 
		break;
	case GameData::Broadsword:
		// 대검 
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
