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
	
	//�� ��� �׽�Ʈ �� â�� �׷����ƿ�
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

	//�� ��� �׽�Ʈ �� â�� �������ƿ�
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


	// �̹��������� ������
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

	//���� â�� ����غ��ƿ�
	char aa[100];
	sprintf(aa, "%d", tileX);
	ImGui::Begin(u8"����");
	ImGui::Text(aa);
	ImGui::End();
}




//�����Ӱ� ������ Ÿ�� üũ���غ��ƿ�
void GreenSlime::MoveAndCheck()
{

	FloatRect rcCollision;		//������ �浹���� ��Ʈ�� �����Ѵ�
	int tileIndex[2];		//�̵� ���⿡ ���� Ÿ�ϼӼ��� �����ϱ� ���� Ÿ�� �ε��� �� ����
	//int tileX, tileY;		//���� ���Ͱ� ��� Ÿ�Ͽ� �ִ��� ����뵵(�ε���)


	// �浹 �簢���̿�
	rcCollision = rc;
	   


	rcCollision.left += 3;
	rcCollision.right -= 3;
	rcCollision.top += 3;
	rcCollision.bottom -= 3;


	tileX = x / tilesize;    // ���� ������ġ ���� 
	tileY = y / tilesize;
	
	//_GameWorld->GetTileManager()->Tile()
	
		switch (mosterstate)
		{


			// Ÿ�� �Ŵ��� �����ͼ� ����ǥ���� ������� �˻縦 �մϴ�.

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


