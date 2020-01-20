#pragma once
#include "UIBase.h"
class AttackSlot : public UIBase
{

public:
	AttackSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~AttackSlot();

	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();
};

