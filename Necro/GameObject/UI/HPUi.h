#pragma once
#include "UIBase.h"
class HPUi : public UIBase
{
public:
	enum HpState
	{
		Full_Hp = 2, Half_Hp = 1 , Empty_Hp = 0
	};

public:
	HPUi(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~HPUi();

	virtual void Init();
	virtual void Release();

	virtual void ControlUpdate();

	//  ��Ʈ ũ�� �� �� �ֳ� ?
	virtual void Update(float tick);

	virtual void Render();

	//�ҷ� ���̴°� ?
	HpState GetHpState() { return Hstate;  }

private:

	HpState Hstate;

	
};

