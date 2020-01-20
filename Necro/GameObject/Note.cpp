#include "stdafx.h"
#include "Note.h"



Note::Note(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	saveTime = 0.f;
	this->size = size;
	ratio = 0.5f;
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
	float factor = saveTime / ratio;
	position.x = Math::Lerp(0, WinSizeY *0.5f, factor);
	if (factor > 1.0f)
	{

		saveTime = 0.f;
	}
	saveTime += tick;
	//rc = FloatRect::MoveRect(rc, D3DXVECTOR2(5.f, 0));
	//if (rc.right > WinSizeX * 0.5f)
	//	rc.Update(D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70), Pivot::CENTER);
	rc.Update(position, size, Pivot::CENTER);
}

void Note::Render()
{
	p2DRenderer->SetCamera(false);
	p2DRenderer->DrawRectangle(rc, nullptr);

}
