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
	alpha = 100;

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

void TileNode::SetData(string textureStringKey, POINT textureFrameIndex, AttributeType type)
{
	textureKey = textureStringKey;
	textureFrame = textureFrameIndex;
	attribute = type;
	texture = _ImageManager->FindTexture(textureKey);
	ReleaseObjects();
}

void TileNode::SetData(D3DXVECTOR2 pos, D3DXVECTOR2 size, string textureStringKey, POINT textureFrameIndex, AttributeType type)
{
	this->Transform().SetPos(pos);
	this->Transform().SetScale(size);
	textureKey = textureStringKey;
	textureFrame = textureFrameIndex;
	attribute = type;
	texture = _ImageManager->FindTexture(textureKey);
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

void TileNode::MissControlUpdate()
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

	StorageIter sIter = objectStorage.begin(), sEnd = objectStorage.end();

	for (; sIter != sEnd; ++sIter)
	{
		OnIter vIter = (*sIter).second.begin(), vEnd = (*sIter).second.end();

		for (; vIter != vEnd; ++vIter)
		{
			(*vIter)->SetAlpha(alpha);
		}
	}
	
	if (temp)
	{
		if (alpha < 1.f)
		{
			alpha += 0.05f;
		}
		else
		{
			alpha = 1.0f;
			temp = false;
		}

	}

	texture->FrameRender(rc, nullptr, textureFrame.x, textureFrame.y, alpha);
	
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

void TileNode::Show()
{
	bShow = true;
	alpha = 1.0f;
	StorageIter sIter = objectStorage.begin(), sEnd = objectStorage.end();

	for (; sIter != sEnd; ++sIter)
	{
		OnIter vIter = (*sIter).second.begin(), vEnd = (*sIter).second.end();

		for (; vIter != vEnd; ++vIter)
		{
			_MessagePool->ReserveMessage((*vIter), "Show");
		}
	}
}

void TileNode::Hide()
{
	bShow = false;
	alpha = 0.5f;
	StorageIter sIter = objectStorage.begin(), sEnd = objectStorage.end();

	for (; sIter != sEnd; ++sIter)
	{
		OnIter vIter = (*sIter).second.begin(), vEnd = (*sIter).second.end();

		for (; vIter != vEnd; ++vIter)
		{
			_MessagePool->ReserveMessage((*vIter), "Hide");
		}
	}
}

void TileNode::Active()
{
	temp = true;
	bActive = true;
	alpha = 0.f;

	StorageIter sIter = objectStorage.begin(), sEnd = objectStorage.end();

	for (; sIter != sEnd; ++sIter)
	{
		OnIter vIter = (*sIter).second.begin(), vEnd = (*sIter).second.end();
		
		for (; vIter != vEnd; ++vIter)
		{
			_MessagePool->ReserveMessage((*vIter), "Active");
		}
	}
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