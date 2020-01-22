#include "stdafx.h"
#include "Diamond.h"
#include "UIBase.h"

Diamond::Diamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
}

Diamond::~Diamond()
{
}

void Diamond::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_Diamond", ResourcePath + L"UI/UI_Diamond.png");
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


//
//DiamondCount::DiamondCount(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
//	:Diamond(name, pos, size)
//{
//}
//
//DiamondCount::~DiamondCount()
//{
//}
//
//void DiamondCount::Init()
//{
//	_RenderPool->Request(this, RenderManager::Layer::UI);
//}
//
//void DiamondCount::Release()
//{
//	_RenderPool->Remove(this, RenderManager::Layer::UI);
//}
//
//void DiamondCount::Update()
//{
//}
//
//void DiamondCount::Render()
//{
//	p2DRenderer->SetCamera(false);
//	//_ImageManager->Render("UI_DiaX", rc, nullptr);
//}
