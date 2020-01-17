#include "stdafx.h"
#include "UIBase.h"





UIBase::UIBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
}

UIBase::~UIBase()
{
}


void UIBase::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);

}

void UIBase::PreUpdate()
{

}

void UIBase::Update(float tick)
{
	rc = FloatRect::MoveRect(rc, D3DXVECTOR2(5.f, 0));
	if (rc.right > WinSizeX * 0.5f)
		rc.Update(D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 100), Pivot::CENTER);
}


void UIBase::Render()
{
	p2DRenderer->SetCamera(false);
	p2DRenderer->DrawRectangle(rc, nullptr);
}
