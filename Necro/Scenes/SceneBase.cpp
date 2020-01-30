#include "stdafx.h"
#include "SceneBase.h"

SceneBase::SceneBase()
	: messageManager(new MessageManager), objectManager(new ObjectManager), renderManager(new RenderManager),
	  beatManager(new BeatManager), tileManager(nullptr)
{
	float tile = 52.f;
	TileManager::SetMapInfo({ 1,1 }, { tile,tile }, { tile * 0.5f,tile * 0.5f });
	tileManager = new TileManager;
	
}

SceneBase::~SceneBase()
{
	Release();
	SafeDelete(messageManager);
	SafeDelete(beatManager);
	SafeDelete(objectManager);
	SafeDelete(renderManager);

}

void SceneBase::Init()
{
	tileManager->CreateMap();
	gameData = _ObjectPool->CreateObject<GameData>("GameData", D3DXVECTOR2(), D3DXVECTOR2());
}

void SceneBase::Release()
{
	messageManager->RemoveAllMessage();
}

void SceneBase::ControlUpdate()
{
	objectManager->ControlUpdate();
}

void SceneBase::Update(float tick)
{
	beatManager->Update(tick);
	messageManager->Update(tick);
	objectManager->Update(tick);
}

void SceneBase::ObjectRender()
{
	renderManager->ObjectRender();
}

void SceneBase::LightRender()
{
	renderManager->LightRender();
}

void SceneBase::UIRender()
{
	renderManager->UIRender();
}

void SceneBase::ImguiRender()
{
	renderManager->ImguiRender();
}


