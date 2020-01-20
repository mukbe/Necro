#pragma once
#include "UIBase.h"
class Heart : public UIBase
{
public:
	Heart(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Heart();

	virtual void Release();

	virtual void ControlUpdate();
	
	virtual void Update(float tick);

	virtual void Render();

private:
	int frameX;
	int frameY;
};

