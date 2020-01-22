#pragma once



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


	vector<GameObject*> GetArrayByType(ObjectType inputType)
	{
		return objectStorage[inputType];
	}
	unordered_map<ObjectType, vector<GameObject*>> GetStorage()
	{
		return objectStorage;
	}

private:
	vector<TileNode*> palleteMap;
	vector<TileNode*>::iterator palleteIter;

	int separateSize;
	D3DXVECTOR2 pivotPos;

	

	unordered_map<ObjectType, vector<GameObject*>> objectStorage;
	typedef unordered_map<ObjectType, vector<GameObject*>>::iterator MapIter;
	typedef vector<GameObject*> VecStorage;
	typedef vector<GameObject*>::iterator VecIter;

	vector<TileNode*> palleteTiles;
	vector<TileNode*>::iterator PalleteIter;
};

