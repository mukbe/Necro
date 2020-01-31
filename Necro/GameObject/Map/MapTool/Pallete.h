#pragma once



class Spawner;


class palleteNode : public GameObject
{
public:
	palleteNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
		: GameObject(name, pos, size), isSelected(false)
	{
		_RenderPool->Request(this, RenderManager::Layer::UI);
		isSelected = false;
		isMouseOver = false;
	}
	~palleteNode() {}

	virtual void Init()
	{

	}

	virtual void SetData(string textureStringKey, string objectStringKey)
	{
		textureKey = textureStringKey;
		objectKey = objectStringKey;
	}

	virtual void Release()
	{
		_RenderPool->Remove(this, RenderManager::Layer::UI);
	}

	virtual void Update(float tick)
	{

	}

	virtual void Render()
	{
		_ImageManager->Render(textureKey, rc, NULL);


		if (isMouseOver)
		{
			HighlightRender(255, 255, 255);
		}
		if (isSelected)
		{
			HighlightRender(200, 50, 50);
		}
	}

	void HighlightRender(BYTE r, BYTE g, BYTE b)
	{
		p2DRenderer->SetCamera(false);
		p2DRenderer->DrawLine(D3DXVECTOR2(rc.left, rc.top), D3DXVECTOR2(rc.right, rc.top), nullptr,
			D3DXCOLOR(r, g, b, 1), 2);
		p2DRenderer->DrawLine(D3DXVECTOR2(rc.right, rc.top), D3DXVECTOR2(rc.right, rc.bottom), nullptr,
			D3DXCOLOR(r, g, b, 1), 2);
		p2DRenderer->DrawLine(D3DXVECTOR2(rc.right, rc.bottom), D3DXVECTOR2(rc.left, rc.bottom), nullptr,
			D3DXCOLOR(r, g, b, 1), 2);
		p2DRenderer->DrawLine(D3DXVECTOR2(rc.left, rc.bottom), D3DXVECTOR2(rc.left, rc.top), nullptr,
			D3DXCOLOR(r, g, b, 1), 2);
	}

	bool GetIsMouseOver() { return isMouseOver; }
	void SetIsMouseOver(bool input) { isMouseOver = input; }

	bool GetIsSelected() { return isSelected; }
	void SetIsSelected(bool input) { isSelected = input; }

	string GetTextureKey() { return textureKey; }
	string GetObjectKey() { return objectKey; }

private:
	string textureKey;
	string objectKey;
	bool isSelected;
	bool isMouseOver;
};




/*       /////////////////////////             */





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

	vector<palleteNode*> GetPalleteArray()
	{
		return vecPallete;
	}
private:
	vector<palleteNode*> vecPallete;
	typedef vector<palleteNode*>::iterator PalleteIter;

	int separateSize;
	D3DXVECTOR2 pivotPos;

	unordered_map<ObjectType, vector<GameObject*>> objectStorage;
	typedef unordered_map<ObjectType, vector<GameObject*>>::iterator MapIter;
	typedef vector<GameObject*> VecStorage;
	typedef vector<GameObject*>::iterator VecIter;
};

