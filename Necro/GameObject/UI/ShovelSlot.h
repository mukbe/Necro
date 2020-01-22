#pragma once
#include "UIBase.h"

class ShovelSlot : public UIBase
{
public:
	ShovelSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ShovelSlot();

	virtual void Init();
	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();
};

