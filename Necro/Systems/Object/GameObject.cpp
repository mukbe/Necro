#include "stdafx.h"
#include "GameObject.h"
#include "./Utilities/Matrix2D.h"

GameObject::GameObject(string name)
	: name(name), bActive(true), worldBuffer(nullptr), shaderKey("None")
	, alpha(1.f), lifeTiem(0.f)

{
	moveType = MoveType_Beat;

}

GameObject::GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: name(name), bActive(true), worldBuffer(nullptr), shaderKey("None")
	, alpha(1.f), lifeTiem(0.f)
{
	worldBuffer = Buffers->FindShaderBuffer<WorldBuffer>();
	transform = Matrix2D(pos);

	bActive = true;
	position = pos;
	rc = FloatRect(pos, size, Pivot::CENTER);
	bBeatChance = 1;

	moveType = MoveType_Beat;

	AddCallback("OnBeat", [&](TagMessage msg) {
		if (bBeatChance <= 0)
		{
			return;
		}
		ControlUpdate();
		bBeatChance--;
	});
	AddCallback("AddChance", [&](TagMessage msg) {
		if (bBeatChance > 0)
		{
			MissControlUpdate();
			return;
		}
		bBeatChance++;
	});
}


GameObject::~GameObject()
{

}

void GameObject::Init()
{
	
}

void GameObject::Release()
{
	//랜더링을 하지말라고 지워야됨
	//_RenderPool->Remove(this, RenderManager::Layer::layer);
}

void GameObject::ControlUpdate()
{

}

void GameObject::MissControlUpdate()
{
}

void GameObject::Update(float tick)
{
	lifeTiem += tick;


}


//뷰행렬 계산을 하면 TRUE
void GameObject::Render()
{
	
}

//void GameObject::PostRender()
//{
//	if (bActive == false)return;
//	if (shaderKey == "None") return;
//
//	CAMERA->CameraDataBind();
//	worldBuffer->Setting(transform.GetResult());
//	worldBuffer->SetPSBuffer(1);
//	Shaders->BindShader(shaderKey);
//
//	UINT stride = sizeof(VertexType);
//	UINT offset = 0;
//
//	DeviceContext->IASetInputLayout(nullptr);
//	DeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
//	DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
//	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	pRenderer->TurnOnAlphaBlend();
//	DeviceContext->Draw(4, 0);
//	pRenderer->TurnOffAlphaBlend();
//
//}
