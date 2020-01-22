#pragma once
#include "UIBase.h"

class ItemSlot  : public UIBase
{
public:
	ItemSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ItemSlot();

	virtual void Init();

	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();

};

