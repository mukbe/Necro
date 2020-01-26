#pragma once
class WallBase : public GameObject
{
public:
	WallBase();
	WallBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~WallBase();

	virtual void Init();
	virtual void Release();

	virtual void ControlUpdate();
	virtual void Update(float tick);

	virtual void Render();

private:

};