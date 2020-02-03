#include "stdafx.h"
#include "GreenSlime.h"

GreenSlime::GreenSlime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Monster(name, pos, size)
{
	//_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"slime_green.png", 4, 2);
	//_RenderPool->Request(this, RenderManager::Layer::Object);
	
	//값 출력 테스트 할 창을 그려보아요
	//_RenderPool->Request(this, RenderManager::Layer::Imgui);

	
	FrameCount=0;
	frameX=0;
	frameY=0;
	position = pos;
	this->size = size;
	startPos = pos;
	endPos = pos;
	monsterBeat = 1;
	life = 1;
	
}


GreenSlime::~GreenSlime()
{

}

void GreenSlime::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
}

void GreenSlime::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
	//값 출력 테스트 할 창을 지워보아요
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}



void GreenSlime::Update(float tick)
{
	Monster::Update(tick);
	
	//MoveAndCheck();


	// 이미지프레임 돌린다
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
	
	clocking();
	
	/*if (KeyCode->Down(VK_RIGHT))
	{
	
		mosterstate = MonsterRIGHT;
	}
	if (KeyCode->Down(VK_LEFT))
	{
		mosterstate = MonsterLEFT;
		
	}


		if (KeyCode->Down(VK_UP))
		{
			mosterstate = MonsterTOP;
			

		}

			if (KeyCode->Down(VK_DOWN))
			{
				mosterstate = MonsterBOTTOM;

			}*/
		
	

	//Math::Lerp(FrameCount, start.x, end.x);
	
	//transform.SetPos(a);


}

void GreenSlime::PostUpdate()
{
}

void GreenSlime::Render()
{
	
	_ImageManager->FindTexture("greenslime")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y), size, Pivot::CENTER), nullptr, frameX, frameY);
	//_ImageManager->FindTexture("greenslime")->FrameRender(rc, nullptr, frameX, frameY);
}

void GreenSlime::ImguiRender()
{

	
}




