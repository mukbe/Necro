#pragma once
#include "UIBase.h"
class HPUi : public UIBase
{
public:
	HPUi(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~HPUi();

	virtual void Init();
	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();

private:

	const float holdTime = 0.08f; 
	bool hold;
	float frameTime;
	
};

