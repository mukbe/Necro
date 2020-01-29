#include "stdafx.h"
#include "TileNode.h"


TileNode::TileNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	moveType = MoveType_Control;

	tileSize = size;
	isSelected = false;
	haveIDrawHighlight = false;
	isUI = false;

	for (int i = ObjectTypeBegin; i != ObjectTypeEnd; ++i)
	{
		if (i == ObjectTypeBegin || i == ObjectAll || i == ObjectTypeEnd) continue;

		typeVector tempVector;
		objectStorage.insert(make_pair((ObjectType)i, tempVector));
	}

}

TileNode::~TileNode()
{

}

void TileNode::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Terrain);
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
	_RenderPool->Remove(this, RenderManager::Layer::Terrain);
	//_ObjectPool->DeletaObject(this);
}

void TileNode::ControllUpdate()
{
}

void TileNode::Update(float tick)
{
	//if (Math::IsPointInAABB(rc, CAMERA->GetMousePos()))
	//{
	//	if (Keyboard::Get()->Down(VK_LBUTTON))
	//	{
	//		isSelected = true;
	//	}
	//}

	//if (Keyboard::Get()->Up(VK_LBUTTON))
	//{
	//	isSelected = false;
	//}
}

void TileNode::Render()
{
	p2DRenderer->SetCamera(!isUI);
	_ImageManager->FindTexture(textureKey)->FrameRender(rc, nullptr, textureFrame.x, textureFrame.y);
	
	if(!isUI)
	{
	
		if (Math::IsPointInAABB(rc, CAMERA->GetMousePos()) && haveIDrawHighlight)
		{
			HighlightRender();
		}
	}
	else
	{
		if (Math::IsPointInAABB(rc, (D3DXVECTOR2)Mouse::Get()->GetPosition()) && haveIDrawHighlight)
		{
			HighlightRender();
		}
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
	if(!isUI)p2DRenderer->SetCamera(true);
	else p2DRenderer->SetCamera(false);

	p2DRenderer->DrawLine(D3DXVECTOR2(rc.left, rc.top), D3DXVECTOR2(rc.right, rc.top), nullptr,
		D3DXCOLOR(200, 50, 50, 1), 2);
	p2DRenderer->DrawLine(D3DXVECTOR2(rc.right, rc.top), D3DXVECTOR2(rc.right, rc.bottom), nullptr,
		D3DXCOLOR(200, 50, 50, 1), 2);
	p2DRenderer->DrawLine(D3DXVECTOR2(rc.right, rc.bottom), D3DXVECTOR2(rc.left, rc.bottom), nullptr,
		D3DXCOLOR(200, 50, 50, 1), 2);
	p2DRenderer->DrawLine(D3DXVECTOR2(rc.left, rc.bottom), D3DXVECTOR2(rc.left, rc.top), nullptr,
		D3DXCOLOR(200, 50, 50, 1), 2);
}