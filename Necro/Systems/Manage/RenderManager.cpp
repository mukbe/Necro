#include "stdafx.h"
#include "RenderManager.h"



void RenderManager::Request(GameObject * const obj, const Layer & layer)
{
	if (obj == nullptr) return;

	renderList[layer].push_back(obj);
}

void RenderManager::Remove(GameObject * const obj, const Layer & layer)
{
	if (obj == nullptr) return;

	vector<GameObject*>& arr = renderList[layer];
	VecIter Iter = arr.begin();
	for (; Iter != arr.end();)
	{
		if (*Iter == obj)
		{
			Iter = arr.erase(Iter);
			break;
		}
		
		//else ++Iter;
	}
}

void RenderManager::Remove(GameObject * const obj)
{
	if (obj == nullptr) return;

	MapIter mIter = renderList.begin();
	for (; mIter != renderList.end(); mIter++)
	{
		VecIter vIter = mIter->second.begin();
		for (; vIter != mIter->second.end();)
		{
			if (*vIter == obj)
			{
				vIter = mIter->second.erase(vIter);
				break;
			}

			//else ++Iter;
		}

	}
}

RenderManager::RenderManager()
{
	renderList.clear();
}


RenderManager::~RenderManager()
{
	renderList.clear();
}

void RenderManager::Render()
{
	//TODO 랜더링 온오프 기능
	ObjectRender();
	LightRender();
	UIRender();
	ImguiRender();
}

//
void RenderManager::ObjectRender()
{
	vector<GameObject*> arr = renderList[Layer::BackGround];
	VecIter Iter = arr.begin();
	for (; Iter != arr.end(); ++Iter)
	{
		GameObject* obj = *Iter;
		if (obj->IsActive())
			obj->Render();
	}

	arr = renderList[Layer::Object];
	for (GameObject* obj : arr)
	{
		if (obj->IsActive())
			obj->Render();
	}


}

//라이팅패스
void RenderManager::LightRender()
{
}

//게임 UI를 위한
void RenderManager::UIRender()
{
	vector<GameObject*>& arr = renderList[Layer::UI];
	VecIter Iter = arr.begin();
	for (; Iter != arr.end(); ++Iter)
	{
		GameObject* obj = *Iter;
		if (obj->IsActive())
			obj->Render();
	}

}

//특정 객체에 디버깅을 위한
void RenderManager::ImguiRender()
{
	vector<GameObject*>& arr = renderList[Layer::Imgui];
	VecIter Iter = arr.begin();
	for (; Iter != arr.end(); ++Iter)
	{
		GameObject* obj = *Iter;
		if (obj->IsActive())
			obj->ImguiRender();
	}

}
