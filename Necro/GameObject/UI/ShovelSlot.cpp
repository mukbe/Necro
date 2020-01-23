#include "stdafx.h"
#include "ShovelSlot.h"



ShovelSlot::ShovelSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	
}


ShovelSlot::~ShovelSlot()
{
}

void ShovelSlot::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	
}

void ShovelSlot::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void ShovelSlot::ControlUpdate()
{
}

void ShovelSlot::Update(float tick)
{
}

void ShovelSlot::Render()
{
	_ImageManager->Render("UI_ShovelSlot", rc, nullptr);

}
