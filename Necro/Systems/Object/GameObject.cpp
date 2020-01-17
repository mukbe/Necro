#include "stdafx.h"
#include "GameObject.h"
#include "./Utilities/Matrix2D.h"

GameObject::GameObject(string name)
	: name(name), bActive(true), worldBuffer(nullptr), shaderKey("None")
	, alpha(1.f), lifeTiem(0.f)

{
	
}

GameObject::GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: name(name), bActive(true), worldBuffer(nullptr), shaderKey("None")
	, alpha(1.f), lifeTiem(0.f)
{
	worldBuffer = Buffers->FindShaderBuffer<WorldBuffer>();
	transform = Matrix2D(pos);

	bActive = true;
	rc = FloatRect(pos, size, Pivot::CENTER);

}


GameObject::~GameObject()
{

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


}

void GameObject::PostUpdate()
{
}

//뷰행렬 계산을 하면 TRUE
void GameObject::Render(bool isRelative)
{
	if (bActive == false)return;


	
	p2DRenderer->DrawEllipse(rc,nullptr);


	
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
