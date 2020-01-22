#include "stdafx.h"
#include "HPUi.h"
#include "UIBase.h"

HPUi::HPUi(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	
}

HPUi::~HPUi()
{
}

void HPUi::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_FullHp", ResourcePath + L"UI/FullHp.png");
	_ImageManager->AddTexture("UI_HalfHp", ResourcePath + L"UI/HalfHp.png");
	_ImageManager->AddTexture("UI_EmptyHp", ResourcePath + L"UI/EmptyHp.png");
}

void HPUi::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void HPUi::ControlUpdate()
{
}

void HPUi::Update(float tick)
{
}

void HPUi::Render()
{
	p2DRenderer->SetCamera(false);

}
