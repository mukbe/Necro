#include "stdafx.h"
#include "HPUi.h"


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
 
	_ImageManager->Render("E_Hp", rc, nullptr);	//  Empty
	_ImageManager->Render("H_Hp", rc, nullptr);	//  Half
	_ImageManager->Render("F_Hp", rc, nullptr); //  Full
}
