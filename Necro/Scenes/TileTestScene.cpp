#include "stdafx.h"
#include "TileTestScene.h"
#include "./GameObject/UIBase.h"
#include "TileHelper.h"

TileTestScene::TileTestScene()
	: SceneBase()
{
}

TileTestScene::~TileTestScene()
{
}

void TileTestScene::Init()
{
	SceneBase::Init();
	testTileManager = new TileManager({ 10,10 }, D3DXVECTOR2(52.f, 52.f), D3DXVECTOR2(10.f, 10.f));
}
