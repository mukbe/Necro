#include "stdafx.h"
#include "GameData.h"

GameData::GameData(string name)
	:GameObject(name)
{
	moveType = MoveType_Custom;
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
