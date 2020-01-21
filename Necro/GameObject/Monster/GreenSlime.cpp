#include "stdafx.h"
#include "GreenSlime.h"
#include "TileManager.h"
#include "TileNode.h"
//#include "Monster.h"

GreenSlime::GreenSlime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Monster(name, pos, size)
{
	//_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"slime_green.png", 4, 2);
	_RenderPool->Request(this, RenderManager::Layer::Object);
	
	//값 출력 테스트 할 창을 그려보아요
	_RenderPool->Request(this, RenderManager::Layer::Imgui);

	
	FrameCount=0;
	frameX=0;
	frameY=0;
	x = pos.x;
	y = pos.y;
	tilesize = size.x;
	speed = D3DXVECTOR2(tilesize, tilesize);
}


GreenSlime::~GreenSlime()
{

}

void GreenSlime::Init()
{
}

void GreenSlime::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);

	//값 출력 테스트 할 창을 지워보아요
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}

void GreenSlime::ControlUpdate()
{
}

void GreenSlime::Update(float tick)
{
	Monster::Update(tick);
	SettingCenterXY(tilesize);
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
	p2DRenderer->SetCamera(true);
	_ImageManager->FindTexture("greenslime")->FrameRender(rc, nullptr, frameX, frameY);
}

void GreenSlime::ImguiRender()
{

	//값을 창에 출력해보아요
	char aa[100];
	sprintf(aa, "%d", tileX);
	ImGui::Begin(u8"씨발");
	ImGui::Text(aa);
	ImGui::End();
}




//움직임과 못가는 타일 체크를해보아요
void GreenSlime::MoveAndCheck()
{

	FloatRect rcCollision;		//임의의 충돌판정 렉트를 선언한다
	int tileIndex[2];		//이동 방향에 따라 타일속성을 검출하기 위한 타일 인덱스 값 계산용
	//int tileX, tileY;		//실제 몬스터가 어디 타일에 있는지 검출용도(인덱스)


	// 충돌 사각형이연
	rcCollision = rc;
	   


	rcCollision.left += 3;
	rcCollision.right -= 3;
	rcCollision.top += 3;
	rcCollision.bottom -= 3;


	tileX = x / tilesize;    // 몬스터 현재위치 검출 
	tileY = y / tilesize;
	
	//_GameWorld->GetTileManager()->Tile()
	
		switch (mosterstate)
		{


			// 타일 매니저 가져와서 내좌표값과 사방으로 검사를 합니다.

		case MonsterIDEL:
			
			break;
		case MonsterLEFT:
			
			if (_GameWorld->GetTileManager()->Tile({ tileX-1 , tileY })->GetAttribute() != ObjStatic)
			{
				x -= speed.x;
			}
			mosterstate = MonsterIDEL;
			break;
		case MonsterRIGHT:
			
			if (_GameWorld->GetTileManager()->Tile({ tileX+1 , tileY })->GetAttribute() != ObjStatic)
			{
				x += speed.x;
			}
			mosterstate = MonsterIDEL;
			break;
		case MonsterTOP:
			
		      if (_GameWorld->GetTileManager()->Tile({ tileX , tileY-1  })->GetAttribute() != ObjStatic)
			{
				y -= speed.y;
			}
			mosterstate = MonsterIDEL;
			break;
		case MonsterBOTTOM:
			
			if (_GameWorld->GetTileManager()->Tile({ tileX , tileY+1  })->GetAttribute() != ObjStatic)
			{
				y += speed.y;
			}
			mosterstate = MonsterIDEL;
			break;

		}
	
}


