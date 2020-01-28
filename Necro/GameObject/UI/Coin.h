#pragma once
#include "./GameObject/UI/UIBase.h"

class Coin : public UIBase
{

public:
	Coin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Coin();

	// 상속 받을때 이렇게 .
	
	virtual void Init();

	virtual void Release();

	virtual void ControlUpdate();

	virtual void Update(float tick);

	virtual void Render();

private:
	
};

