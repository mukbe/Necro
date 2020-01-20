#pragma once
#include "UIBase.h"
class TorchSlot : public UIBase
{
public:
	TorchSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~TorchSlot();
	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();
};

