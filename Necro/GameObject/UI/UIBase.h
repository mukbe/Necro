#pragma once

class UIBase : public GameObject
{

public:
	UIBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~UIBase();

private:
	virtual void Init();

	virtual void Release();

	virtual void ControlUpdate();
	
	virtual void Update(float tick);

	virtual void Render();


};

