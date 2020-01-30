#pragma once
#include "UIBase.h"
class Heart : public UIBase
{
public:
	Heart(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Heart();

	virtual void Init();
	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);

	virtual void Render();

	void MissUpdate();

	struct Text
	{
		D3DXVECTOR2 textPos;
		float textShownTime;
		float textMoveSpeed;

	};

private:
	const float holdTime = 0.08f;
	const wstring textMiss = L"ºø³ª°¨!";

	bool hold;
	float frameTime;

	using TextIter = vector<Text>::iterator;
	vector<Text> texts;
};

