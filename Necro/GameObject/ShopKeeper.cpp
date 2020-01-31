#include "stdafx.h"
#include "ShopKeeper.h"
#include "Player.h"

ShopKeeper::ShopKeeper(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	position = pos;
	this->size = size;
	interver = frameX = frameY = 0;
	
	loudness = 0.6f;
}

ShopKeeper::~ShopKeeper()
{

}

void ShopKeeper::Init()
{
	GameObject::Init();
	wstring path = ResourcePath + L"Music/ShopKeeper.ogg";
	SOUNDMANAGER->AddSound("ShopKeeper", String::WStringToString(path), true, false);

	_RenderPool->Request(this, RenderManager::Layer::Object);
	// �̹��� �ְ� 
	// �뷡 �θ��� ���� 
}

void ShopKeeper::Release()
{
	GameObject::Release();

	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ShopKeeper::Update(float tick)
{
	GameObject::Update(tick);
	if (Keyboard::Get()->Down(VK_F3))
	{
		SOUNDMANAGER->Play("ShopKeeper");
		SOUNDMANAGER->SetVolume("ShopKeeper", loudness);
		// 4-5��? ���� ������ ���� ���
	}
		//int time =SOUNDMANAGER->Getposition("stage1");
		//SOUNDMANAGER->Setposition("ShopKeeper", time);
	
	D3DXVECTOR2 playerPos = IndexToPos(_GameWorld->GetGameData()->GetIndex(), D3DXVECTOR2(52,52), D3DXVECTOR2(26,26));
	
	distance = D3DXVECTOR2(playerPos.x - position.x, playerPos.y - position.y);
	float factor;
	factor = Math::Abs(D3DXVec2Length(&distance)) / 350;
	if (factor <= 1)
	{
		loudness = 1 - factor;
	}
	if (factor > 1)
	{
		loudness = 0;
	}

	// ������ ��� ���� ���ش� .
	SOUNDMANAGER->SetVolume("ShopKeeper", loudness);



	interver += tick * 4;
	// ������ �ݺ� �ϴٰ� �뷡 ������ ���� ������ ����, �־����� frameY 1�� �ٲ㼭 �˰� ������ 
	if (interver > 0.5f) {
		frameX++;
		interver = 0;
	}
	if (frameX > 2) {
		frameX = 0;
	}
}

void ShopKeeper::Render()
{
	_ImageManager->FindTexture("ShopKeeper")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y - 20), size, Pivot::CENTER), nullptr, frameX, frameY);
}
