#include "stdafx.h"
#include "Note.h"
#include "./Systems/Manage/BeatManager.h"


Note::Note(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	this->size = size;
	AddCallback("save", [&](TagMessage msg) {
		temp.push_back(position);
	});
	AddCallback("Shown", [&](TagMessage msg) {
		
	});
}

Note::~Note()
{
}

void Note::Init()
{
	ratio = BeatManager::currentDelta;
	saveTime = 0.f;
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
