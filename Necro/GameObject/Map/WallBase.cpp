#include "stdafx.h"
#include "WallBase.h"
#include "./GameObject/Map/TileNode.h"


WallBase::WallBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size), haveIShowIcon(false), IconLifeTime(0.f), life(1)
{
	_RenderPool->Request(this,RenderManager::Layer::Object);

	D3DXVECTOR2 tempPivot = _GameWorld->GetTileManager()->GetPivotPos();
	D3DXVECTOR2 tempTileSize = _GameWorld->GetTileManager()->GetTileSize();

	myIndex = PosToIndex(pos, tempTileSize, tempPivot);
	myTile = _GameWorld->GetTileManager()->Tile(myIndex);
	
	AddCallback("ShovelHit", [&](TagMessage msg) {
		haveIShowIcon = true;
		if (type == WallDestructableShovel)
		{
			ProcessDestroy();
		}
		
	});
	AddCallback("PickHit", [&](TagMessage msg) {
		haveIShowIcon = true;
		if (type == WallDestructablePick || type == WallDestructableShovel)
		{
			ProcessDestroy();
		}
	});
}

WallBase::~WallBase()
{
	_RenderPool->Remove(this);
}

void WallBase::Init()
{
	switch (type)
	{
	case WallDestructableShovel:
		myTile->SetAttribute(ObjDestructable);
		break;
	case WallDestructablePick:
		myTile->SetAttribute(ObjDestructable);
		break;
	case WallUndestructable:
		myTile->SetAttribute(ObjStatic);
		break;
	default:
		break;
	}
}

void WallBase::Release()
{
}

void WallBase::ControlUpdate()
{
}

void WallBase::MissControlUpdate()
{
}

void WallBase::Update(float tick)
{
	if (haveIShowIcon)
	{
		IconLifeTime += Time::Tick();

		if (IconLifeTime >= 5.f)
		{
			haveIShowIcon = false;
		}
	}
}

void WallBase::Render()
{
	if(haveIShowIcon)
	{
		_ImageManager->FindTexture("ShovelIcon")->Render(FloatRect(this->Transform().GetPos(), 52.f, Pivot::CENTER), NULL);
	}
}

void WallBase::ProcessDestroy()
{
	life--;
	if (life <= 0) 
	{
		//이펙트 추가 필요.

		myTile->SetAttribute(ObjNone);
		this->SetActive(false);
	}
}
