#pragma once
//slot Texrue의 이름과 클래스이름은 동일하게 설정해야됨
//즉 처음 imageManager에 초기화한 키값이 클래스의 이름이 됨
class UIBase : public GameObject
{

public:
	UIBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~UIBase();

public:
	virtual void Init();

	virtual void Release();

	virtual void ControlUpdate();
	
	virtual void Update(float tick);

	virtual void Render();

	virtual void EatItem(string key);
	virtual void SetLocalPosition(D3DXVECTOR2 pos);

	void SetSlotImage(string slot);
protected:

	string slotKey;
	shared_ptr<Texture> slotTex;

	string currentItem;
	D3DXVECTOR2 screenPosItem;

	shared_ptr<Texture> itemTex;
	D3DXVECTOR2 screenPos;
	bool bMove;
	float saveTime;

};

