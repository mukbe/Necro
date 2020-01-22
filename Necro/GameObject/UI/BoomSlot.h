#pragma once
#include "UIBase.h"
class BoomSlot : public UIBase
{
public:
	BoomSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~BoomSlot();

	virtual void Init();

	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();

};

