#include "stdafx.h"
#include "BlueSlime.h"
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
	x = pos.x;
	y = pos.y;
	tilesize = size.x;
	startPos = pos;
	endPos = { pos.x + 52.f, pos.y + 52.f };
	speed = D3DXVECTOR2(tilesize, tilesize);
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
	SettingCenterXY(tilesize);
	//MoveAndCheck();

	//	// �̹��������� ������
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
	_ImageManager->FindTexture("blueslime")->FrameRender(rc, nullptr, frameX, frameY);
}

void BlueSlime::ImguiRender()
{
}



void BlueSlime::MoveAndCheck()
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




	switch (mosterstate)
	{


		// Ÿ�� �Ŵ��� �����ͼ� ����ǥ���� ������� �˻縦 �մϴ�.

	case Monster1IDEL:

		break;
	case Monster1LEFT:

		if (_GameWorld->GetTileManager()->Tile({ tileX - 1 , tileY })->GetAttribute() != ObjStatic)
		{
			x -= speed.x;
		}
		mosterstate = Monster1IDEL;
		break;
	case Monster1RIGHT:

		if (_GameWorld->GetTileManager()->Tile({ tileX + 1 , tileY })->GetAttribute() != ObjStatic)
		{
			x += speed.x;
		}
		mosterstate = Monster1IDEL;
		break;
	case Monster1TOP:

		if (_GameWorld->GetTileManager()->Tile({ tileX , tileY - 1 })->GetAttribute() != ObjStatic)
		{
			y -= speed.y;
		}
		mosterstate = Monster1IDEL;
		break;
	case Monster1BOTTOM:

		if (_GameWorld->GetTileManager()->Tile({ tileX , tileY + 1 })->GetAttribute() != ObjStatic)
		{
			y += speed.y;
		}
		mosterstate = Monster1IDEL;
		break;

	}
}
