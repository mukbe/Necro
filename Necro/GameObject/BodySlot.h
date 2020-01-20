#pragma once
#include "UIBase.h"

class BodySlot : public UIBase
{
public:
	BodySlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~BodySlot();

	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();
};

