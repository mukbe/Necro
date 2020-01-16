#include "stdafx.h"
#include "SceneBase.h"

#include "./Systems/Message/MessageManager.h"

SceneBase::SceneBase()
	: messageManager(new MessageManager)
{
	
}


SceneBase::~SceneBase()
{
	Release();
	SafeDelete(messageManager);
	
	
}

void SceneBase::Init()
{
}

void SceneBase::Release()
{
	messageManager->RemoveAllMessage();
}

void SceneBase::PreUpdate()
{
}

void SceneBase::Update(float tick)
{
	messageManager->Update(tick);
}

void SceneBase::PostUpdate()
{
}

void SceneBase::Render()
{
}

void SceneBase::PostRender()
{
}

void SceneBase::ImguiRender()
{
}

