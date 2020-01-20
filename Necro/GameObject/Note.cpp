#include "stdafx.h"
#include "Note.h"
#include "./Systems/Manage/BeatManager.h"


Note::Note(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	saveTime = 0.f;
	this->size = size;
	ratio = BeatManager::currentDelta;
	AddCallback("save", [&](TagMessage msg) {
		temp.push_back(position);
	});

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
	position.x = Math::Lerp(WinSizeX *0.5f *0.25f, WinSizeX *0.5f, factor);
	if (factor > 1.0f)
	{

		saveTime = 0.f;
	}
	saveTime += tick;
	//rc = FloatRect::MoveRect(rc, D3DXVECTOR2(5.f, 0));
	//if (rc.right > WinSizeX * 0.5f)
	//	rc.Update(D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70), Pivot::CENTER);
	rc.Update(position, size, Pivot::CENTER);
	if (Keyboard::Get()->Down('F')) temp.clear();
}

void Note::Render()
{
	p2DRenderer->SetCamera(false);
	p2DRenderer->DrawRectangle(rc, nullptr);

	for (int i = 0; i < temp.size(); i++)
	{
		FloatRect debug(temp[i], D3DXVECTOR2(10, 70), Pivot::CENTER);
		p2DRenderer->DrawRectangle(debug,nullptr,DefaultBrush::red);
	}
}
