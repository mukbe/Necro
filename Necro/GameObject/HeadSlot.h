#pragma once
#include "UIBase.h"
class HeadSlot : public UIBase
{
public:
	HeadSlot(string name,D3DXVECTOR2 pos,D3DXVECTOR2 size);
	~HeadSlot();

	virtual void Release();
	virtual void ControlUpdate();
	virtual void Update(float tick);
	virtual void Render();
	
};

