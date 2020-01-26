#pragma once


// ������ �������� ����ϴ� �Լ� / ����  ��  �� ���⼭ ����! 
// ��� �޼��� Ű ���� ���Ϸ� �ؼ� �÷��̾� / ������ ��밡�� �� �� �ְ� 

class ItemBase : public GameObject
{
public:
	ItemBase(string name, D3DXVECTOR2 pos,D3DXVECTOR2 size);
	~ItemBase();

public:
											// ���� ������Ʈ����  ��� ���� �� �ʿ��� �Լ� �׸��� Itembase�� ��� �޴� Ŭ�������� �� �Ÿ� �������� ��!
	virtual void Init();					// ����!
											
	virtual void Release();					// ������!  �� �ΰ��� �ʼ�
											
	virtual void ControlUpdate();			
											
	virtual void Update(float tick);		
											
	virtual void Render();					
											
	virtual void Init(POINT tileIndex);		

protected:
	
	bool bShow;  // ������ �þ߿� ������� ���̰� Ȥ�� �Ⱥ��̰� �ϴ°�
};

