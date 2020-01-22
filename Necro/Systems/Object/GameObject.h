#pragma once
#include "../Message/MessageComponent.h"

class Matrix2D;
class GameObject : public MessageComponent
{
	using VertexType = VertexColor;
public:
	GameObject(string name = "None");
	GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~GameObject();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//��Ʈ�� ����
	virtual void ControlUpdate();
	//���� ��ƾ
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender() {}



	const string& Name() { return name; }
	Matrix2D& Transform() { return transform; }

	const bool& IsActive() { return bActive; }
	void SetActive(const bool& b) { bActive = b; }

	void SetAlpha(const float& a)
	{
		a > 0.f ? (a > 1.f ? alpha = 1.f : alpha = a) : alpha = 0.f;
	}
	const float& GetAlpha() { return alpha; }

	FloatRect GetRect() { return rc; }


	void SetPivot(Pivot p) { rc.Update(position, D3DXVECTOR2(rc.right - rc.left, rc.bottom - rc.top), p); }

protected:
	//�̳��� �̸� (�ߺ����)
	string name;
	//�̳��� ��ġ, ȸ��, ������ ���� 
	Matrix2D transform;

	FloatRect rc;
	Pivot pivot;
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;

	bool bActive;

	
	float alpha;
	float lifeTiem;
	int bBeatChance;

private:
	string shaderKey;
	WorldBuffer* worldBuffer;

};

