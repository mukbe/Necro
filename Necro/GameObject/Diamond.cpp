#include "stdafx.h"
#include "Diamond.h"
#include "UIBase.h"

Diamond::Diamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_Diamond", ResourcePath + L"UI/DIA.png");
}


Diamond::~Diamond()
{
}

void Diamond::Release()
{
}

void Diamond::ControlUpdate()
{
}

void Diamond::Update(float tick)
{
}

void Diamond::Render()
{
	_ImageManager->Render("UI_Diamond", FloatRect({ 1200,100}, { 50,50.}, Pivot::CENTER), nullptr);
}
