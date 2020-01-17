#pragma once


class ObjectManager
{
	friend class SceneBase;
public:
	void DeletaObject(class GameObject* object);
	
	IS_INHERITED_THAN_RETURN(GameObject) CreateObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	IS_INHERITED_THAN_RETURN(GameObject) FindObject(string name);
	vector<GameObject*> FindObjects(string name);

private:
	using VecIter = vector<class GameObject*>::iterator;
	vector<class GameObject*> objects;
	vector<class GameObject*> deleteList;


	ObjectManager();
	~ObjectManager();

	void ControlUpdate();
	void Update(float tick);

};

IS_INHERITED_THAN_RETURN(class GameObject) ObjectManager::CreateObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	Derived* temp = new Derived(name, pos, size);

	objects.push_back(temp);

	return temp;
}



IS_INHERITED_THAN_RETURN(class GameObject) ObjectManager::FindObject(string name)
{
	for (size_t t = 0; t < objects.size(); t++)
	{
		if (name == objects[t]->Name())
			return static_cast<Derived*>(objects[t]);
	}

	LOG->Error(__FILE__, __LINE__, "can't find object");
	return nullptr;
}

