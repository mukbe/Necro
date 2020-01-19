#include "stdafx.h"
#include "TileNode.h"


TileNode::TileNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

TileNode::~TileNode()
{
}

void TileNode::Init(string textureStringKey, POINT textureFrameIndex, AttributeType type)
{
	textureKey = textureStringKey;
	textureFrame = textureFrameIndex;
	attribute = type;
}

void TileNode::Init(D3DXVECTOR2 pos, D3DXVECTOR2 size, string textureStringKey, POINT textureFrameIndex, AttributeType type)
{
	this->Transform().SetPos(pos);
	this->Transform().SetScale(size);
	textureKey = textureStringKey;
	textureFrame = textureFrameIndex;
	attribute = type;
}

void TileNode::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void TileNode::PreUpdate()
{
}

void TileNode::Update()
{
}

void TileNode::PostUpdate()
{
}

void TileNode::Render()
{
	
	_ImageManager->FindTexture(textureKey)->FrameRender(rc, &this->transform, textureFrame.x, textureFrame.y);
	
	
	/*wstring str;
	str = to_wstring(GetPos().x) + to_wstring(GetPos().y);
	p2DRenderer->DrawText2D(GetPos().x, GetPos().y, str, 20);*/
	
}

void TileNode::ImguiRender()
{
}
