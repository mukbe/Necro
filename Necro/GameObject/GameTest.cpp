#include "stdafx.h"
#include "GameTest.h"

GameDate::GameDate(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	// 받아 드릴 키값 
	this->name = name;
}
GameDate::~GameDate()
{
}

void GameDate::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
	PS.Hp = 6;
	PS.AttackPower = 1;
	//PS.PlayerVision
}

void GameDate::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}
//키 받을려면 이렇게 ?
void GameDate::update(float tick, TagMessage msg)
{

}

void GameDate::Render()
{

}

void GameDate::ImguiRender()
{
}
