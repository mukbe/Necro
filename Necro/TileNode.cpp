#include "stdafx.h"
#include "TileNode.h"


TileNode::TileNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::Object);

	tileSize = size;
	isSelected = false;
}

TileNode::~TileNode()
{

}

void TileNode::Init(string textureStringKey, POINT textureFrameIndex, AttributeType type)
{
	textureKey = textureStringKey;
	textureFrame = textureFrameIndex;
	attribute = type;
	ReleaseObjects();
}

void TileNode::Init(D3DXVECTOR2 pos, D3DXVECTOR2 size, string textureStringKey, POINT textureFrameIndex, AttributeType type)
{
	this->Transform().SetPos(pos);
	this->Transform().SetScale(size);
	textureKey = textureStringKey;
	textureFrame = textureFrameIndex;
	attribute = type;
	ReleaseObjects();
}

void TileNode::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
	//_ObjectPool->DeletaObject(this);
}

void TileNode::ControllUpdate()
{
}

void TileNode::Update(float tick)
{
}

void TileNode::Render()
{
	_ImageManager->FindTexture(textureKey)->FrameRender(rc, nullptr, textureFrame.x, textureFrame.y);
	
	if (Math::IsPointInAABB(rc, CAMERA->GetMousePos()))
	{
		HighlightRender();
	}
	/*wstring str;
	wstring abc = L" , ";
	str = to_wstring(posToIndex(this->GetPos()).x) + abc + to_wstring(posToIndex(this->GetPos()).y);
	p2DRenderer->DrawText2D(GetPos().x, GetPos().y, str, 10);*/
}



void TileNode::ImguiRender()
{
}

void TileNode::HighlightRender()
{
	p2DRenderer->SetCamera(true);
	p2DRenderer->DrawLine(D3DXVECTOR2(rc.left, rc.top), D3DXVECTOR2(rc.right, rc.top), nullptr,
		D3DXCOLOR(200, 50, 50, 1), 2);
	p2DRenderer->DrawLine(D3DXVECTOR2(rc.right, rc.top), D3DXVECTOR2(rc.right, rc.bottom), nullptr,
		D3DXCOLOR(200, 50, 50, 1), 2);
	p2DRenderer->DrawLine(D3DXVECTOR2(rc.right, rc.bottom), D3DXVECTOR2(rc.left, rc.bottom), nullptr,
		D3DXCOLOR(200, 50, 50, 1), 2);
	p2DRenderer->DrawLine(D3DXVECTOR2(rc.left, rc.bottom), D3DXVECTOR2(rc.left, rc.top), nullptr,
		D3DXCOLOR(200, 50, 50, 1), 2);
}