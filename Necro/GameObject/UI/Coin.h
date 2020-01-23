#pragma once
#include "UIBase.h"

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
	//const float holdTime = 0.05f;
	//bool hold;
	//float frameTime;
};
//
//class CoinCount : public Coin
//{
//public :
//	CoinCount(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
//	~CoinCount();
//
//	virtual void Init();
//
//	virtual void Release();
//	// 코인 올라가게 계산 
//	virtual void Update(float tick);
//
//	//그려야지 
//	virtual void Render();
//
//private :
//	char str[256];
//};
//
