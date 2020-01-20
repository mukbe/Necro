#include "stdafx.h"
#include "Heart.h"



Heart::Heart(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddFrameTexture("UI_Heart", ResourcePath + L"UI/TempHeart.png", 2, 1);
	frameX = 0;
}


Heart::~Heart()
{
}

void Heart::Release()
{
}

void Heart::ControlUpdate()
{
}

void Heart::Update(float tick)
{
	// ----------심장 노트 
	rc = FloatRect::MoveRect(rc, D3DXVECTOR2(5.f, 0));
	if (rc.right > WinSizeX * 0.5f)
		rc.Update(D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70), Pivot::CENTER);
	//---------------

	frameX++;
	if (frameX > 1) {
		frameX = 0;
	}

}

void Heart::Render()
{
	//심장
	p2DRenderer->SetCamera(false);
	p2DRenderer->DrawRectangle(rc, nullptr);
	_ImageManager->FrameRender("UI_Heart", FloatRect({ WinSizeX / 2.f , 830.f }, { 130.f,140.f }, Pivot::CENTER), nullptr, frameX, 0);
}
