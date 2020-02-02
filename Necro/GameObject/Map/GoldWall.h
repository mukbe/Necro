#pragma once
#include "WallBase.h"

class GoldWall : public WallBase
{
public:
	GoldWall(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~GoldWall();

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

	virtual void ProcessDestroy();

};