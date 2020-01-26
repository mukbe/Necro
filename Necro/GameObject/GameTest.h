#pragma once

class GameDate  : public GameObject
{
public:
	GameDate(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~GameDate();

	virtual void Init();
	virtual void Release();
	virtual void update(float tick);
	virtual void Render();
	virtual void ImguiRender();
};

