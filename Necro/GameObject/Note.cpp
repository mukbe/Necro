#include "stdafx.h"
#include "Note.h"



Note::Note(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);

}

Note::~Note()
{
}

void Note::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Note::ControlUpdate()
{
}

void Note::Update(float tick)
{
	rc = FloatRect::MoveRect(rc, D3DXVECTOR2(5.f, 0));
	if (rc.right > WinSizeX * 0.5f)
		rc.Update(D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70), Pivot::CENTER);

}

void Note::Render()
{
	p2DRenderer->SetCamera(false);
	p2DRenderer->DrawRectangle(rc, nullptr);

}
