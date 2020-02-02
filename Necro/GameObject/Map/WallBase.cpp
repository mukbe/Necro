#include "stdafx.h"
#include "WallBase.h"
#include "./GameObject/Map/TileNode.h"


WallBase::WallBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size), haveIShowIcon(false), IconLifeTime(0.f)
{
	AddCallback("ShovelHit", [&](TagMessage msg) {
		haveIShowIcon = true;
		if (type == WallDestructibleShovel)
		{
			ProcessDestroy();
		}
		else
		{
			ProcessFail();
		}
		
	});
	AddCallback("PickHit", [&](TagMessage msg) {
		haveIShowIcon = true;
		if (type == WallDestructiblePick || type == WallDestructibleShovel)
		{
			ProcessDestroy();
		}
		else
		{
			ProcessFail();
		}
	});
}

WallBase::~WallBase()
{
}

void WallBase::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);

	life = 1;
	type = WallDestructibleShovel;
	textureKey = "DefaultWall";//?
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

		if (IconLifeTime >= 0.3f)
		{
			haveIShowIcon = false;
			IconLifeTime = 0.f;
		}
	}
}

void WallBase::Render()
{
	
	_ImageManager->FindTexture(textureKey)->Render(FloatRect(D3DXVECTOR2(this->Transform().GetPos().x, this->Transform().GetPos().y +defaultTileSize.y/2) , D3DXVECTOR2(52.f, 80.f), Pivot::BOTTOM), NULL);

	if(haveIShowIcon)
	{
		//_ImageManager->FindTexture("EffectShovel")->Render(FloatRect(this->Transform().GetPos(), 52.f, Pivot::CENTER), NULL);
		//EFFECTS->Fire("EffectShovel", this->Transform().GetPos());
		
	}
}

void WallBase::Show()
{
	bShow = true;
	alpha = 1.0f;
}

void WallBase::Hide()
{
	bShow = false;
	alpha = 0.5f;
}

void WallBase::Active()
{
	bActive = true;
	alpha = 0.f;
}

void WallBase::SetTileAttribute()
{
	switch (type)
	{
	case WallDestructibleShovel:
		myTile->SetAttribute(ObjDestructable);
		break;
	case WallDestructiblePick:
		myTile->SetAttribute(ObjDestructable);
		break;
	case WallIndestructible:
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
		CAMERA->Shake();
		SOUNDMANAGER->Play("Dig");
		myTile->SetAttribute(ObjNone);
		this->SetActive(false);
	}
}

void WallBase::ProcessFail()
{
	SOUNDMANAGER->Play("DigFail");
}
