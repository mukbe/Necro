#pragma once

class palleteNode : public GameObject
{
public:
	palleteNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
		: GameObject(name, pos, size), isSelected(false)
	{
		_RenderPool->Request(this, RenderManager::Layer::UI);
	}
	~palleteNode() {}

	virtual void Init()
	{

	}

	virtual void SetData(string TextureKey, GameObject* Object)
	{
		textureKey = TextureKey;
		myObject = Object;
	}

	virtual void Release()
	{
		_RenderPool->Remove(this, RenderManager::Layer::UI);
	}

	virtual void Update(float tick)
	{
		int a = 0;
		if (Math::IsPointInAABB(rc, (D3DXVECTOR2)Mouse::Get()->GetPosition()))
		{
			isMouseOnMe = true;
			if (Keyboard::Get()->Down(VK_LBUTTON))
			{
				isSelected = true;
			}
		}
		else
		{
			isMouseOnMe = false;
		}
	}

	virtual void Render()
	{
		if (isMouseOnMe)
		{
			HighlightRender(255, 255, 255);
		}
		if (isSelected)
		{
			HighlightRender(200, 50, 50);
		}

		_ImageManager->Render(textureKey, rc, NULL);
		int a = 0;
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

private:
	string textureKey;
	GameObject* myObject;
	bool isSelected;
	bool isMouseOnMe;
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
	vector<palleteNode*> vecPallete;
	typedef vector<palleteNode*>::iterator PalleteIter;

	int separateSize;
	D3DXVECTOR2 pivotPos;

	

	unordered_map<ObjectType, vector<GameObject*>> objectStorage;
	typedef unordered_map<ObjectType, vector<GameObject*>>::iterator MapIter;
	typedef vector<GameObject*> VecStorage;
	typedef vector<GameObject*>::iterator VecIter;
};

