#include "stdafx.h"
#include "EffectManager.h"


SingletonCpp(EffectManager)
EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
}

void EffectManager::Update(float tick)
{

	for (int i = 0; i < playList.size(); i++)
	{
		playList[i].UpdateTime += tick;
		if (playList[i].UpdateTime >= playList[i].InvFps)
		{
			playList[i].UpdateTime -= playList[i].InvFps;
			playList[i].Frame++;
			if (playList[i].Frame >= playList[i].MaxFrame)
			{
				playList[i].RoopCount--;
			}
		}
	}

	VecIter Iter = playList.begin();
	for (;Iter != playList.end();)
	{
		if ((*Iter).RoopCount <= 0)
		{
			Iter = playList.erase(Iter);
		}
		else
		{
			Iter++;
		}
	}
}

void EffectManager::Render()
{
	//TODO 회전도 가능하게 만들어야됨
	p2DRenderer->SetCamera(true);
	for (int i = 0; i < playList.size(); i++)
	{
		FloatRect rc(D3DXVECTOR2(0,0), playList[i].Size, Pivot::CENTER);
		Matrix2D rot;
		rot.SetRotate(Math::PI* 1.5f);
		rot.SetPos(playList[i].Position);
		playList[i].Image->FrameRender(rc, &rot, playList[i].Frame);
	}
}

void EffectManager::Fire(string key, D3DXVECTOR2 pos, D3DXVECTOR2 size, float fps)
{
	EffectDesc effect = Find(key);
	effect.Position = pos;
	effect.Size = size;
	effect.InvFps = 1.f / fps;
	effect.RoopCount = 1;
	playList.push_back(effect);
}

void EffectManager::AddEffact(string key, string imageKey)
{
	EffectDesc effect;
	effect.Image = _ImageManager->FindTexture(imageKey);
	effect.MaxFrame = (UINT)effect.Image->GetMaxFrame().x;
	effectList.insert(make_pair(key, effect));
}

EffectDesc EffectManager::Find(string key)
{
	MapIter Iter = effectList.find(key);
	if (Iter != effectList.end())
	{
		return Iter->second;
	}

	//없는거임 예외처리 해야됨
	return EffectDesc();
}
