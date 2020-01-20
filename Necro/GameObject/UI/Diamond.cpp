#include "stdafx.h"
#include "Diamond.h"
#include "UIBase.h"

Diamond::Diamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_Diamond", ResourcePath + L"UI/DIA.png");
}


Diamond::~Diamond()
{
}

void Diamond::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Diamond::ControlUpdate()
{
}

void Diamond::Update(float tick)
{
}

void Diamond::Render()
{
	p2DRenderer->SetCamera(false);
	_ImageManager->Render("UI_Diamond", rc, nullptr);
	
}
