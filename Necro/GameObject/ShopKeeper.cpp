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
	bShow = false;
	alpha = 0.f;
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
	// 이미지 넣고 
	// 노래 부르게 하자 
}

void ShopKeeper::Release()
{
	GameObject::Release();

	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ShopKeeper::ControlUpdate()
{
	D3DXVECTOR2 playerPos = IndexToPos(_GameWorld->GetGameData()->GetIndex(), D3DXVECTOR2(52, 52), D3DXVECTOR2(26, 26));

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

	// 볼륨을 계속 갱신 해준다 .
	SOUNDMANAGER->SetVolume("ShopKeeper", loudness);


}

void ShopKeeper::Update(float tick)
{
	GameObject::Update(tick);

	if (SOUNDMANAGER->IsPlaySound(_BeatManager->CurrentMusic()))
	{
		if (!SOUNDMANAGER->IsPlaySound("ShopKeeper"))
		{
			SOUNDMANAGER->Play("ShopKeeper");
			SOUNDMANAGER->SetVolume("ShopKeeper", loudness);
		}
	}


		//int time =SOUNDMANAGER->Getposition("stage1");
		//SOUNDMANAGER->Setposition("ShopKeeper", time);
	


	interver += tick * 4;
	// 프레임 반복 하다가 노래 나오면 뒤쪽 프레임 감고, 멀어지면 frameY 1로 바꿔서 검게 만들면댐 
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
	_ImageManager->FindTexture("ShopKeeper")->FrameRender(FloatRect(D3DXVECTOR2(position.x, position.y - 20), size, Pivot::CENTER), nullptr, frameX, (UINT)!bShow, alpha);
}

void ShopKeeper::Show()
{
	bShow = true;
}

void ShopKeeper::Hide()
{
	bShow = false;
}

void ShopKeeper::Active()
{
	bActive = true;
	alpha = 1.0f;
}
