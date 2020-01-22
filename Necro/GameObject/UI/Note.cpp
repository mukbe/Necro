#include "stdafx.h"
#include "Note.h"
#include "./Systems/Manage/BeatManager.h"


Note::Note(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	this->size = size;
	AddCallback("EnterBeat", [&](TagMessage msg) {
		OnBeatEnter();
	});
	AddCallback("Shown", [&](TagMessage msg) {
		//if (this->IsMove() == false)return;
		float lerp = msg.Data->GetValue<float>();
		Init(lerp);

	});
}

Note::~Note()
{
}

void Note::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	ratio = BeatManager::currentDelta;
	saveTime = 0.f;
	bMove = false;
	bGrace = false;
	gracePeriod = 0.5f;
	alpha = 1.0f;
}

void Note::Init(float lerpTime)
{
	ratio = lerpTime;
	bMove = true;
	bGrace = false;
	saveTime = 0.f;
	alpha = 0.f;
	gracePeriod = 0.5f;

	position.x = -30.f;
	rc.Update(position, size, Pivot::CENTER);
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
	if (bMove)
	{
		alpha = Math::Lerp(0.f, 1.f, position.x / 100);

		float factor = saveTime / ratio;
		position.x = Math::Lerp(-30.f, WinSizeX *0.5f, factor);
		if (factor > 1.0f)
		{
			saveTime = 0.f;
			bMove = false;

			_BeatManager->ReturnNote();

		}
		saveTime += tick;
		rc.Update(position, size, Pivot::CENTER);

	}
	if (bGrace)
	{
		saveTime -= tick;
		alpha = Math::Lerp(0.f, 1.f, saveTime / gracePeriod);
		if (alpha > 1.f)
		{
			_BeatManager->ReturnNote();
			bGrace = false;
		}

	}

}

void Note::Render()
{
	p2DRenderer->SetCamera(false);

#ifdef DEBUGMODE
	p2DRenderer->DrawRectangle(rc, nullptr, ColorF::White, alpha, 1.f);
#else
	p2DRenderer->DrawRectangle(rc, nullptr, ColorF::White, alpha, 1.f);
#endif // DEBUGMODE
}

void Note::OnBeatEnter()
{
	//_BeatManager->ReturnNote();

	saveTime = gracePeriod = 0.5f;
	alpha = 1.f;
	bGrace = true;
	bMove = false;
}
