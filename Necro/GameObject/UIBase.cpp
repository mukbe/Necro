#include "stdafx.h"
#include "UIBase.h"


UIBase::UIBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	
	_RenderPool->Request(this, RenderManager::Layer::UI);
}

UIBase::~UIBase()
{
}

void UIBase::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void UIBase::ControlUpdate()
{
}

void UIBase::Update(float tick)
{	
}


void UIBase::Render()
{
}


//ui베이스가 정확히 뭘 하기 위한 클래스야? 전체 ui 다 들어가있는거야 아니면
	// 저거 상속받아서 따로 하는거야? 전체 ui ㄷ ㅏ 들어가있는 클래스에요 얘한테 상속바당서 
	//현진이가 글케 하래?그랬던거 같아요 그래 잠만 넵
	//coin->Render();
	//Dia->DiaRender();
	
	