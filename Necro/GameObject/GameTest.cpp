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
}

void GameDate::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}

void GameDate::update(float tick)
{
}

void GameDate::Render()
{

}

void GameDate::ImguiRender()
{
}
