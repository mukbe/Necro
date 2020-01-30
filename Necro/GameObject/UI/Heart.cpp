#include "stdafx.h"
#include "Heart.h"



Heart::Heart(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{

	hold = 0;
	frameTime = 0.f;
	AddCallback("Miss", [&](TagMessage msg) {
		MissUpdate();
	});
}


Heart::~Heart()
{
}

void Heart::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
}

void Heart::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void Heart::MissUpdate()
{
	Text text;
	text.textPos = position;
	text.textMoveSpeed = 110.f;
	text.textShownTime = 1.f;
	text.textPos.x -= 35;
	texts.emplace_back(text);
}

void Heart::ControlUpdate()
{
	hold = true;
}

void Heart::Update(float tick)
{
	if (hold)
	{
		frameTime += tick;
		if (frameTime >= holdTime)
		{
			frameTime -= holdTime;
			hold = false;
		}
	}
	if (!texts.empty())
	{
		TextIter Iter = texts.begin();
		for (; Iter!= texts.end();)
		{
			(*Iter).textShownTime -= tick;

			if ((*Iter).textShownTime < 0.f)
			{
				Iter = texts.erase(Iter);
			}
			else
			{
				(*Iter).textPos.y -= (*Iter).textMoveSpeed * tick;
				Iter++;
			}
		}
	}
}

void Heart::Render()
{
	_ImageManager->FrameRender("HeartTemp", rc, nullptr, (UINT)hold, 0);

	for (size_t t = 0; t < texts.size(); t++)
	{
		p2DRenderer->DrawText2D(texts[t].textPos, textMiss, 20, DefaultBrush::white,DWRITE_TEXT_ALIGNMENT_LEADING);
	}

}
