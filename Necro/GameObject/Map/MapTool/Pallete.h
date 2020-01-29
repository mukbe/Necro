#pragma once

class palleteNode : public GameObject
{
public:
	palleteNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
		: GameObject(name,pos,size)
	{
		_RenderPool->Request(this, RenderManager::Layer::UI);
	}
	~palleteNode(){}

private:
	string textureKey;
	GameObject* myObject;
	
};

class Pallete
{
public:
	Pallete(D3DXVECTOR2 pivot);
	~Pallete();

	void Init();

	void release();

	void update();

	void render();

	void AddObject(ObjectType type, GameObject* object);

	void DeleteObject(ObjectType type, GameObject* object);

	void CreatePallete(ObjectType inputType, D3DXVECTOR2 inputPivotPos);

	void ReleasePallete();

	void LoadObjects();

	template<typename T>
	GameObject* Load(string Key, ObjectType objType, RenderManager::Layer renderType)
	{
		string namePal = "Tool";
		GameObject* temp;
		temp = _ObjectPool->CreateObject<T>(namePal + Key, D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
		_RenderPool->Remove(temp, renderType);
		AddObject(objType, temp);

		wstring tempString;
		tempString.assign(temp->Name().begin(), temp->Name().end());

		_ImageManager->AddTexture(temp->Name(), ResourcePath + L"/MapTool/" + tempString + L".png");

		return temp;
	}


	vector<GameObject*> GetArrayByType(ObjectType inputType)
	{
		return objectStorage[inputType];
	}
	unordered_map<ObjectType, vector<GameObject*>> GetStorage()
	{
		return objectStorage;
	}

private:
	vector<palleteNode*> palleteMap;
	vector<palleteNode*>::iterator palleteIter;

	int separateSize;
	D3DXVECTOR2 pivotPos;

	

	unordered_map<ObjectType, vector<GameObject*>> objectStorage;
	typedef unordered_map<ObjectType, vector<GameObject*>>::iterator MapIter;
	typedef vector<GameObject*> VecStorage;
	typedef vector<GameObject*>::iterator VecIter;

	vector<TileNode*> palleteTiles;
	typedef vector<TileNode*>::iterator PalleteIter;
};

