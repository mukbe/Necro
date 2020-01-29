#include "stdafx.h"
#include "RenderManager.h"
#include "./Systems/Manage/TileManager.h"
#include "./GameObject/Map/TileNode.h"


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
		
		else ++Iter;
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


void RenderManager::ObjectRender()
{
	p2DRenderer->SetCamera(true);
	vector<GameObject*> arr = renderList[Layer::BackGround];
	VecIter Iter = arr.begin();
	for (; Iter != arr.end(); ++Iter)
	{
		GameObject* obj = *Iter;
		if (obj->IsActive())
			obj->Render();
	}

	arr = renderList[Layer::Terrain];
	Iter = arr.begin();
	FloatRect render = CAMERA->GetRenderRect();

	POINT startIndex = PosToIndex(D3DXVECTOR2(render.left, render.top), TileManager::tileSize, TileManager::pivotPos);
	POINT endIndex = PosToIndex(D3DXVECTOR2(render.right, render.bottom), TileManager::tileSize, TileManager::pivotPos);

	startIndex.x = Math::Clamp(startIndex.x, 0, TileManager::mapSize.x);
	startIndex.y = Math::Clamp(startIndex.x, 0, TileManager::mapSize.y);
	endIndex.x = Math::Clamp(endIndex.x, 0, TileManager::mapSize.x);
	endIndex.y = Math::Clamp(endIndex.y, 0, TileManager::mapSize.y);

	POINT deltaIndex = { endIndex.x - startIndex.x, endIndex.y - endIndex.x };

	for (LONG y = startIndex.y; y <= endIndex.y; y++)
	{
		for (LONG x = startIndex.x; x <= endIndex.x; x++)
		{
			_TileMap->Tile((int)x, (int)y)->Render();
		}
	}



	//for (GameObject* obj : arr)
	//{
	//	if (obj->IsActive())
	//	{
	//		if (Math::IsAABBInAABB(render, obj->GetRect()))
	//			obj->Render();
	//	}
	//}


	//TODO 퀵소트로 바꿔라
	multimap<float, GameObject*> sorted;
	multimap<float, GameObject*>::iterator sortedIter;

	arr = renderList[Layer::Object];
	for (GameObject* obj : arr)
	{
		if (obj->IsActive())
		{
			if (Math::IsAABBInAABB(render, obj->GetRect()))
			{
				sorted.insert(make_pair(obj->GetRect().bottom, obj));
			}
				//obj->Render();
		}
	}

	sortedIter = sorted.begin();
	for (; sortedIter != sorted.end(); ++sortedIter)
	{
		sortedIter->second->Render();
	}

}

//라이팅패스
void RenderManager::LightRender()
{

}

//게임 UI를 위한
void RenderManager::UIRender()
{
	p2DRenderer->SetCamera(false);

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
