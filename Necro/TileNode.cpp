#include "stdafx.h"
#include "TileNode.h"


TileNode::TileNode()
{
}

TileNode::TileNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, string textureStringKey, POINT textureFrameIndex, AttributeType type)
	:GameObject(name, pos, size), attribute(type), textureKey(textureStringKey), textureFrame(textureFrameIndex)
{
}

TileNode::~TileNode()
{
}

void TileNode::Init()
{
}

void TileNode::Release()
{
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
