#include "stdafx.h"
#include "GameData.h"

GameData::GameData(string name)
	:GameObject(name)
{
	moveType = MoveType_Custom;
	playerCoin = 0;
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
}


void GameData::Render()
{

}

void GameData::ImguiRender()
{
}

void GameData::AddCoin(UINT val)
{
	playerCoin += val;
}

void GameData::MinusCoin(UINT val)
{
	if (playerCoin < val)
	{
		//못 사는데 왜 넘겨줌?
	}
	playerCoin -= (int)val;
}
