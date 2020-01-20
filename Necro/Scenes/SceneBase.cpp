#include "stdafx.h"
#include "SceneBase.h"

SceneBase::SceneBase()
	: messageManager(new MessageManager), objectManager(new ObjectManager), renderManager(new RenderManager),
	  beatManager(new BeatManager)
{
	
}


SceneBase::~SceneBase()
{
	Release();
	SafeDelete(messageManager);
	SafeDelete(renderManager);
	SafeDelete(beatManager);
	SafeDelete(objectManager);
}

void SceneBase::Init()
{
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


