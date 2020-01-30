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

protected:
	
	bool bShow;  // ������ �þ߿� ������� ���̰� Ȥ�� �Ⱥ��̰� �ϴ°�
	bool bDrop;  // ������ ��ü�� �ؿ� ������ �ٽ� �ֿ� �� �̹����� �ٲ���� !

};

