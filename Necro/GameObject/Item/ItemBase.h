#pragma once


// ������ �������� ����ϴ� �Լ� / ����  ��  �� ���⼭ ����! 
// ��� �޼��� Ű ���� ���Ϸ� �ؼ� �÷��̾� / ������ ��밡�� �� �� �ְ� 

class TileNode;

class ItemBase : public GameObject
{
public:
	ItemBase(string name, D3DXVECTOR2 pos,D3DXVECTOR2 size);
	~ItemBase();

public:
											// ���� ������Ʈ����  ��� ���� �� �ʿ��� �Լ� �׸��� Itembase�� ��� �޴� Ŭ�������� �� �Ÿ� �������� ��!
	virtual void Init();					// ����!
	virtual void Release();					// ������!  �� �ΰ��� �ʼ�
	virtual void Update(float tick);		
	virtual void Render();									
	virtual void Init(POINT tileIndex);		
	virtual void EatItem();

	virtual void Show();
	virtual void Hide();
	virtual void Active();

	void SetCost(UINT val);
	bool CanBuyItem();

protected:
	
	bool bShow;  // ������ �þ߿� ������� ���̰� Ȥ�� �Ⱥ��̰� �ϴ°�
	UINT cost;
	vector<UINT> text;

	void PushCount(UINT val);
};

