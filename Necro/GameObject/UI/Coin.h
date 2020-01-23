#pragma once
#include "UIBase.h"

class Coin : public UIBase
{

public:
	Coin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Coin();

	// ��� ������ �̷��� .
	
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
//	// ���� �ö󰡰� ��� 
//	virtual void Update(float tick);
//
//	//�׷����� 
//	virtual void Render();
//
//private :
//	char str[256];
//};
//
