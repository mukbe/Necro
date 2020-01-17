#pragma once

class UIBase : public GameObject
{

public:
	UIBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~UIBase();

private:
	virtual void Release();

	virtual void PreUpdate();
	// ƽ���� �� �� ���� ���� ����ٰ� �������ϸ�ǳ� .
	virtual void Update(float tick);

	virtual void Render();

	int frameX;
	int frameY;

};

