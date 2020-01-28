#include "stdafx.h"
#include "BlueSlime.h"

//#include "TileManager.h"
//#include "TileNode.h"

#include "./Systems/Manage/TileManager.h""
#include "./GameObject/Map/TileNode.h"

//#include "Monster.h"


BlueSlime::BlueSlime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: Monster(name, pos, size)
{
	//_ImageManager->AddFrameTexture("blueslime", ResourcePath + L"slime_ice.png", 4, 2);
	
		FrameCount = 0;
	frameX = 0;
	frameY = 0;
	position = pos;
	this->size = size;
	startPos = pos;
	endPos = { position.x + 52.f, position.y + 52.f };
	monsterBeat = 2;
}


BlueSlime::~BlueSlime()
{
}


void BlueSlime::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void BlueSlime::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);

}



void BlueSlime::Update(float tick)
{
	Monster::Update(tick);
	//SettingCenterXY(tilesize);
	//MoveAndCheck();

	//	// 이미지프레임 돌린다
	FrameCount++;
	if (FrameCount == 10)
	{
		frameX++;
		FrameCount = 0;
		if (frameX > 3)
		{

			frameX = 0;
		}
	}



	/*if (KeyCode->Down(VK_RIGHT))
	{

		mosterstate = Monster1RIGHT;
	}
	if (KeyCode->Down(VK_LEFT))
	{
		mosterstate = Monster1LEFT;

	}


	if (KeyCode->Down(VK_UP))
	{
		mosterstate = Monster1TOP;


	}

	if (KeyCode->Down(VK_DOWN))
	{
		mosterstate = Monster1BOTTOM;

	}
*/
}

void BlueSlime::PostUpdate()
{
}

void BlueSlime::Render()
{
	_ImageManager->FindTexture("blueslime")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, frameY);
	
}

void BlueSlime::ImguiRender()
{
}


