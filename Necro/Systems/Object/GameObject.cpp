#include "stdafx.h"
#include "GameObject.h"
#include "./Utilities/Matrix2D.h"

GameObject::GameObject(string name)
	: name(name), bActive(true), worldBuffer(nullptr), shaderKey("None")
	, alpha(1.f), lifeTiem(0.f), frameTime(0.f)

{
	
}

GameObject::GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, Pivot p)
	: name(name), bActive(true), worldBuffer(nullptr), shaderKey("None")
	, alpha(1.f), size(size),  lifeTiem(0.f), frameTime(0.f),
{

	worldBuffer = Buffers->FindShaderBuffer<WorldBuffer>();
	transform = Matrix2D(pos, size, p);
	
	bActive = true;

	frameX = frameY = 0;

	frequency = 0.07f;
}


GameObject::~GameObject()
{
	Release();
}

void GameObject::Init()
{
	
}

void GameObject::Release()
{
}

void GameObject::PreUpdate()
{

}

void GameObject::Update(float tick)
{

	//if (Keyboard::Get()->Down(VK_F5))
	//	bActive = !bActive;

	if (bActive == false) return;


	lifeTiem += tick;
	frameTime += tick;


}

void GameObject::PostUpdate()
{
}

//����� ����� �ϸ� TRUE
void GameObject::Render(bool isRelative)
{
	if (bActive == false)return;

	Matrix2D world;

	if (isRelative)
	{
		world = transform * CAMERA->GetView();
	}

	world.Bind();

	//transform.Render();

	
}

void GameObject::PostRender()
{
	if (shaderKey == "None") return;

	CAMERA->CameraDataBind();
	worldBuffer->Setting(transform.GetResult());
	worldBuffer->SetPSBuffer(1);
	Shaders->BindShader(shaderKey);

	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	DeviceContext->IASetInputLayout(nullptr);
	DeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	pRenderer->TurnOnAlphaBlend();
	DeviceContext->Draw(4, 0);
	pRenderer->TurnOffAlphaBlend();

}
