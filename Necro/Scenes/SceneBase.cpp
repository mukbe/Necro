#include "stdafx.h"
#include "SceneBase.h"

SceneBase::SceneBase()
	: messageManager(new MessageManager), objectManager(new ObjectManager), renderManager(new RenderManager),
	  beatManager(new BeatManager), tileManager(nullptr)
{
	float tile = 52.f;
	TileManager::SetMapInfo({ 10,10 }, { tile,tile }, { tile * 0.5f,tile * 0.5f });
	TileManager::SetTexture();
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


