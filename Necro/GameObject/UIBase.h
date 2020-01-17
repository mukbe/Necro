#pragma once

class UIBase : public GameObject
{

public:
	UIBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~UIBase();

private:
	virtual void Release();

	virtual void PreUpdate();
	// 틱으로 올 때 마다 덮어 씌운다고 생각을하면되나 .
	virtual void Update(float tick);

	virtual void Render();

	int frameX;
	int frameY;

};

