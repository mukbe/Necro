#include "stdafx.h"
#include "UIBase.h"


UIBase::UIBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	AddCallback("EatItem", [&](TagMessage msg) {
		EatItem(msg.Data->GetValue<string>());
	});
	AddCallback("CurrentPosition", [&](TagMessage msg) {
		SetLocalPosition(msg.Data->GetValue<D3DXVECTOR2>());
	});

	bMove = false;
	saveTime = 0.f;
	SetSlotImage(name);
}

UIBase::~UIBase()
{
}


void UIBase::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
}

void UIBase::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void UIBase::ControlUpdate()
{
}

void UIBase::Update(float tick)
{
	if (bMove)
	{
		saveTime += tick;
		float factor = saveTime / 0.2f;

		screenPos = Math::LerpSmoothArrival(screenPosItem, position, factor, 3);

		if (factor > 1.0)
		{
			screenPos = Math::Lerp(screenPosItem, position, 1.f);
			bMove = false;
		}
	}

}


void UIBase::Render()
{
	if (slotTex != false)
	{
		slotTex->Render(rc, nullptr);
	}
	if (itemTex != false)
	{
		FloatRect itemRc(screenPos, itemTex->GetFrameSize() * 2, Pivot::CENTER);
		itemTex->FrameRender(itemRc, nullptr, 0, 0);
	}
}

void UIBase::EatItem(string key)
{
	itemTex = _ImageManager->FindTexture(key);
}

void UIBase::SetLocalPosition(D3DXVECTOR2 pos)
{
	screenPosItem = CAMERA->WorldToScreen(pos);
	bMove = true;

}

void UIBase::SetSlotImage(string slot)
{
	slotKey = slot;
	slotTex = _ImageManager->FindTexture(slotKey);
}
