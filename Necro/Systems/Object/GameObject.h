#pragma once
#include "../Message/MessageComponent.h"

class Matrix2D;
class GameObject : public MessageComponent
{
	using VertexType = VertexColor;
public:
	GameObject(string name = "None");
	GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, Pivot p = Pivot::CENTER);
	virtual~GameObject();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//ī�޶� ���� ���ʾ�����Ʈ - ��� ���صε�
	virtual void PreUpdate();
	//���� ��ƾ
	virtual void Update(float tick);
	//�̵����� ���
	virtual void PostUpdate();

	//�̹��� ������ - direct2D
	virtual void Render(bool isRelative = true);
	//��ó�� ������ -direct3D
	virtual void PostRender();
	//imgui debugUI render
	virtual void ImguiRender() {}



	const string& Name() { return name; }
	void SetName(const string& s) { name = s; }


	Matrix2D& Transform() { return transform; }

	const bool& IsActive() { return bActive; }
	void SetActive(const bool& b) { bActive = b; }

	void SetAlpha(const float& a)
	{
		a > 0.f ? (a > 1.f ? alpha = 1.f : alpha = a) : alpha = 0.f;
	}
	const float& GetAlpha() { return alpha; }

	void SetSize(const D3DXVECTOR2& s) 
	{
		//�����ؾߵ�
		size = s;
	}
	const D3DXVECTOR2& GetSize() { return size; }








protected:
	string name;
	Matrix2D transform;
	D3DXVECTOR2 size;
	bool bActive;

	float alpha;
	float lifeTiem;

	



private:
	string shaderKey;
	WorldBuffer* worldBuffer;

};

