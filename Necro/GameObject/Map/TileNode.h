#pragma once

#include "TileHelper.h"
//#include "MapTool.h"


class TileNode : public GameObject
{
public:
	TileNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~TileNode();

	virtual void Init(string textureStringKey = "DefaultMap", POINT textureFrameIndex = { 0,0 }, AttributeType type = ObjNone);
	virtual void Init(D3DXVECTOR2 pos, D3DXVECTOR2 size, string textureStringKey = "NoneTexture", POINT textureFrameIndex = { 0,0 }, AttributeType type = ObjNone);
	
	virtual void Release();
	virtual void ControllUpdate();
	virtual void Update(float tick);

	virtual void Render();
	virtual void ImguiRender();

	virtual void HighlightRender();

	string GetTextureKey() { return textureKey; }
	POINT GetFrame() { return textureFrame; }
	int GetFrameX() { return textureFrame.x; }
	int GetFrameY() { return textureFrame.y; }
	AttributeType GetAttribute() { return attribute; }

	void SetTextureKey(string key) { textureKey = key; }
	void SetFrame(POINT frame) { textureFrame = frame; }
	void SetFrameX(int frameX) { textureFrame.x = frameX; }
	void SetFrameY(int frameY) { textureFrame.y = frameY; }
	void SetAttribute(AttributeType inputAttribute) { attribute = inputAttribute; }

	D3DXVECTOR2 GetPos() { return this->Transform().GetPos();}
	//void SetPos(D3DXVECTOR2 inputPos) { this->Transform().SetPos(inputPos);}

	void SetPivotPos(D3DXVECTOR2 input) { pivotPos = input; }

	POINT GetIndex()
	{
		//return posToIndex(GetPos());
		return PosToIndex(GetPos(), tileSize, pivotPos);
	}

	RECT GetCollision() { return rc.GetRect(); }

	vector<GameObject*> GetObjects(ObjectType type) { return objectStorage[type]; }
	void AddObject(ObjectType type, GameObject* input) { objectStorage[type].push_back(input); }
	void DeleteObject(ObjectType type, GameObject* input)
	{
		for (int i = 0; i < objectStorage[type].size(); ++i)
		{
			if (objectStorage[type][i] == input)
			{
				OnIter pointIter = objectStorage[type].begin() + i;
				objectStorage[type].erase(pointIter);
				return;
			}
		}
	}
	void ReleaseObjects()
	{
		StorageIter iter = objectStorage.begin(), end = objectStorage.end();

		for (; iter != end; ++iter)
		{
			if ((*iter).second.size() > 0)
			{
				for (int i = 0; i < (*iter).second.size(); ++i)
				{
					OnIter pointIter = (*iter).second.begin() + i;
					(*iter).second.erase(pointIter);
					--i;
				}
			}
			(*iter).second.clear();
		}
		objectStorage.clear();
	}

	bool GetSelected() { return isSelected; }
	bool GetHighlight() { return haveIDrawHighlight; }
	void SetHighlight(bool input) { haveIDrawHighlight = input; }
	void SetUIMode(bool input) { isUI = input; }

protected:
	string textureKey;
	POINT textureFrame;
	AttributeType attribute;
	
	unordered_map<ObjectType, vector<GameObject*>> objectStorage;
	typedef unordered_map<ObjectType, vector<GameObject*>>::iterator StorageIter;

	typedef vector<GameObject*> typeVector;
	typedef vector<GameObject*>::iterator OnIter;

	D3DXVECTOR2 tileSize;
	D3DXVECTOR2 pivotPos;

	bool isSelected;
	bool haveIDrawHighlight;
	bool isUI;
};