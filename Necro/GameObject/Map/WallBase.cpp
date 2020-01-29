#include "stdafx.h"
#include "WallBase.h"
#include "./GameObject/Map/TileNode.h"


WallBase::WallBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size), haveIShowIcon(false), IconLifeTime(0.f)
{
	_RenderPool->Request(this,RenderManager::Layer::Object);
	
	AddCallback("ShovelHit", [&](TagMessage msg) {
		haveIShowIcon = true;
		if (type == WallDestructableShovel)
		{
			CAMERA->Shake();
			ProcessDestroy();
		}
		
	});
	AddCallback("PickHit", [&](TagMessage msg) {
		haveIShowIcon = true;
		if (type == WallDestructablePick || type == WallDestructableShovel)
		{
			CAMERA->Shake();
			ProcessDestroy();
		}
	});
}

WallBase::~WallBase()
{
}

void WallBase::Init()
{
	life = 1;
	type = WallDestructableShovel;
	textureKey = "DefaultWall";
}

void WallBase::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);

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
	
	_ImageManager->FindTexture(textureKey)->Render(FloatRect(D3DXVECTOR2(this->Transform().GetPos().x, this->Transform().GetPos().y - 14.f) , D3DXVECTOR2(52.f, 80.f), Pivot::CENTER), NULL);

	if(haveIShowIcon)
	{
		_ImageManager->FindTexture("EffectShovel")->Render(FloatRect(this->Transform().GetPos(), 52.f, Pivot::CENTER), NULL);
	}
}

void WallBase::SetTileAttribute()
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
