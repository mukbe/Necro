#include "stdafx.h"
#include "HPUi.h"
#include "UIBase.h"

HPUi::HPUi(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_FullHp", ResourcePath + L"UI/FullHp.png");
	_ImageManager->AddTexture("UI_HalfHp", ResourcePath + L"UI/HalfHp.png");
	_ImageManager->AddTexture("UI_EmptyHp", ResourcePath + L"UI/EmptyHp.png");
}

HPUi::~HPUi()
{
}

void HPUi::Release()
{
}

void HPUi::ControlUpdate()
{
}

void HPUi::Update(float tick)
{
}

void HPUi::Render()
{
}
