#pragma once
#include "UIBase.h"

class Note : public UIBase
{
public:
	Note(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Note();

	virtual void Init();
	void Init(float lerpTime);

	virtual void Release();

	virtual void ControlUpdate();
	// ƽ���� �� �� ���� ���� ����ٰ� �������ϸ�ǳ� .
	virtual void Update(float tick);

	virtual void Render();
	
	void OnBeatEnter();
	bool IsMove() { return bMove; }
private:
	float ratio;
	float saveTime;
	bool bMove;
	D3DXVECTOR2 size;
	vector<D3DXVECTOR2> temp;
	bool bGrace;
	float gracePeriod;

};

