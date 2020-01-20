#include "stdafx.h"
#include "TorchSlot.h"



TorchSlot::TorchSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_TorchSlot", ResourcePath + L"UI/Torch_Slot.png");
}


TorchSlot::~TorchSlot()
{
	
}

void TorchSlot::Release()
{
}

void TorchSlot::ControlUpdate()
{
}

void TorchSlot::Update(float tick)
{
}

void TorchSlot::Render()
{
	_ImageManager->Render("UI_TorchSlot", FloatRect({ 230,75}, { 75,75}, Pivot::CENTER), nullptr);
}
