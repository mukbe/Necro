#include "stdafx.h"
#include "GameData.h"

GameData::GameData(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	moveType = MoveType_Beat;

	
	playerHp = 10;
	playerCoin = 999;
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

//Minus �� ���� ���� 
void GameData::MinusCoin(UINT val)
{
	//���� ���� 
	if (playerCoin < val)
	{
		Log_ErrorAssert(playerCoin < val);
		//���� ���� �� �� 
		return;
	}
	playerCoin -= (int)val;
}

void GameData::MinusDia(UINT val)
{
	if (playerDia < val)
	{
		// ���̾� ���� 
		return;
	}
	playerDia -= (int)val;
}

void GameData::PosRedefinition(POINT pos)
{
	playerIndex = pos;
}

void GameData::SetWeaponData(WeaponInfo weaponInfo)
{
	weaponData = weaponInfo;
}

void GameData::SetShovelData(ShovelInfo shovelInfo)
{
	shovelData = shovelInfo;
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
