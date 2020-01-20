#include "stdafx.h"
#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	deleteList.clear();
	objects.clear();
}


ObjectManager::~ObjectManager()
{

}

void ObjectManager::ControlUpdate()
{
	for (GameObject* obj : objects)
	{
		obj->ControlUpdate();
	}
}

void ObjectManager::Update(float tick)
{
	for (GameObject* obj : objects)
	{
		obj->Update(tick);
	}
	if (deleteList.empty() == false)
	{
		VecIter Iter = deleteList.begin();
		for (; Iter != deleteList.end();)
		{
			(*Iter)->Release();
			SafeDelete(*Iter);
			Iter = deleteList.erase(Iter);
		}
	}
	
}


void ObjectManager::DeletaObject(GameObject * object)
{
	for (size_t t = 0; t < objects.size(); t++)
	{
		if (objects[t] == object)
		{
			deleteList.emplace_back(object);
			objects.erase(objects.begin() + t);
			break;
		}
	}

}


