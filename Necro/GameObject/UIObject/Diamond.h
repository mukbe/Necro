#pragma once
#include "UIBase.h"
class Diamond : public UIBase
{

public:
	Diamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Diamond();

	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();
};

