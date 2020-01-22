#include "stdafx.h"
#include "TorchSlot.h"



TorchSlot::TorchSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{

}

TorchSlot::~TorchSlot()
{
	
}

void TorchSlot::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_TorchSlot", ResourcePath + L"UI/Torch_Slot.png");

}

void TorchSlot::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void TorchSlot::ControlUpdate()
{
}

void TorchSlot::Update(float tick)
{
}

void TorchSlot::Render()
{
	p2DRenderer->SetCamera(false);
	_ImageManager->Render("UI_TorchSlot", rc, nullptr);
	
}
