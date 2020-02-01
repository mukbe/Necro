#pragma once

struct EffectDesc
{
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Size;
	UINT Frame;
	UINT MaxFrame;
	float InvFps;
	float UpdateTime;
	int RoopCount;
	shared_ptr<Texture> Image;
	EffectDesc() : Frame(0), RoopCount(0), InvFps(1 / 60.f), UpdateTime(0.f) {}
};
class EffectManager
{
	SingletonHeader(EffectManager)
public:

	void Update(float tick);
	void Render();

	void Fire(string key, D3DXVECTOR2 pos, D3DXVECTOR2 size, float fps = 60.f);
	void AddEffact(string key, string imageKey);
	EffectDesc Find(string key);
private:
	using MapIter = unordered_map < string, EffectDesc>::iterator;
	using VecIter = vector < EffectDesc>::iterator;
	unordered_map<string, EffectDesc> effectList;
	vector<EffectDesc> playList;
};

#define EFFECTS EffectManager::Get()