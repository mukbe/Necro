#pragma once


class ObjectManager
{
	friend class SceneBase;		//씬에서 생성함
	friend class BeatManager;	//모든 오브젝트가 필요함 ( UI는 빼고 필요한데.. 일단 전부)
public:
	void DeletaObject(class GameObject* object);
	
	IS_INHERITED_THAN_RETURN(GameObject) CreateObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	IS_INHERITED_THAN_RETURN(GameObject) FindObject(string name);
	IS_INHERITED_THAN_RETURN_VECTOR_ARRAY(GameObject) FindObjects(string name);

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


IS_INHERITED_THAN_RETURN_VECTOR_ARRAY(GameObject) ObjectManager::FindObjects(string name)
{
	vector<Derived*> vec;
	for (size_t t = 0; t < objects.size(); t++)
	{
		if (name == objects[t]->Name())
			vec.push_back(static_cast<Derived*>(objects[t]));
	}
	return std::move(vec);
}


