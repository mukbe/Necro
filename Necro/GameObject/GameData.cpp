#include "stdafx.h"
#include "GameData.h"

GameData::GameData(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	moveType = MoveType_Beat;


	playerCoin = 0;
	playerDia = 0;
	comboCount = 0;
	ratioCoin = 1.f;
	bCombo = false;
	bBeat = false;

	AddCallback("Miss", [&](TagMessage msg) {
		MissControlUpdate();
	});
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
	ImGui::Begin("GameData");
	ImGui::Text("bBeat %d", (int)bBeat);
	ImGui::End();
}

void GameData::AddDia(UINT val)
{
	playerDia += val;
}

void GameData::AddCoin(UINT val)
{
	playerCoin += val * ratioCoin;
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
