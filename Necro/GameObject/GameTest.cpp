#include "stdafx.h"
#include "GameTest.h"

GameDate::GameDate(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	// �޾� �帱 Ű�� 
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
//Ű �������� �̷��� ?
void GameDate::update(float tick, TagMessage msg)
{

}

void GameDate::Render()
{

}

void GameDate::ImguiRender()
{
}
