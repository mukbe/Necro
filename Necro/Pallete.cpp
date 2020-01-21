#include "stdafx.h"
#include "Pallete.h"
#include <algorithm>
/*
	Player
*/
#include "./GameObject/Player.h"
/*
	Monster
*/
#include "./GameObject/Monster/Monster.h"
#include "./GameObject/Monster/Bat.h"
#include "./GameObject/Monster/BlueSlime.h"
#include "./GameObject/Monster/GreenSlime.h"

Pallete::Pallete()
{
	vecStorage tempStorage;
	objectStorages.insert(make_pair(Player, tempStorage));
	
	for (int i = ObjectTypeBegin; i != ObjectTypeEnd; ++i)
	{

	}
}

Pallete::~Pallete()
{
}

void Pallete::Init()
{
}

void Pallete::Release()
{
}

void Pallete::Update()
{
}

void Pallete::AddObject()
{
}

void Pallete::DeleteObject()
{
}

void Pallete::CreatePallete()
{
}
