#pragma once
#include "WallBase.h"

class StoneWall : public WallBase
{
public:
	StoneWall(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~StoneWall();

	virtual void Init();
	virtual void Release();

	virtual void ControlUpdate();
	virtual void MissControlUpdate();

	virtual void Update(float tick);

	virtual void Render();
	virtual void ImguiRender();

	virtual void Show();
	virtual void Hide();

	virtual void Active();

	virtual void SetActiveTexture();
};