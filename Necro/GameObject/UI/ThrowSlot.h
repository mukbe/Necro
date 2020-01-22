#pragma once
#include "UIBase.h"

enum ThrowState
{
	Idle,
	ThrowWait
};

class ThrowSlot : public UIBase
{

public:
	ThrowSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ThrowSlot();

	virtual void Init();
	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();
private:
	ThrowState Throw;
	bool isInPut;
};
