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


//ui���̽��� ��Ȯ�� �� �ϱ� ���� Ŭ������? ��ü ui �� ���ִ°ž� �ƴϸ�
	// ���� ��ӹ޾Ƽ� ���� �ϴ°ž�? ��ü ui �� �� ���ִ� Ŭ�������� ������ ��ӹٴ缭 
	//�����̰� ���� �Ϸ�?�׷����� ���ƿ� �׷� �Ḹ ��
	//coin->Render();
	//Dia->DiaRender();
	
	