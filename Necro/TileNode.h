#pragma once

#include "TileHelper.h"


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
		return posToIndex(GetPos());
	}

	D3DXVECTOR2 indexToPos(const POINT index)
	{
		return { index.x * tileSize.x + (tileSize.x / 2.f),
				index.y * tileSize.y + (tileSize.y / 2.f) };
	}

	POINT posToIndex(const D3DXVECTOR2 pos)
	{
		float x = ((pos.x - pivotPos.x) / tileSize.x) * 2.f;
		float y =  ((pos.y - pivotPos.y) / tileSize.y) * 2.f;

		return { (int)x,(int)y };
	}

	RECT GetCollision() { return rc.GetRect(); }

	vector<GameObject*> GetObjects() { return onMyHead; }
	void AddObject(GameObject* input) { onMyHead.push_back(input); }
	void DeleteObject(GameObject* input) 
	{
		OnIter iter = onMyHead.begin(), end = onMyHead.end();
		for(;iter != end; ++iter)
		{
			if ((*iter) == input)
			{
				onMyHead.erase(iter);
				--iter;
			}
		}
	}
	void ReleaseObjects()
	{
		if (onMyHead.size() > 0)
		{
			OnIter iter = onMyHead.begin(), end = onMyHead.end();
			for (; iter != end; ++iter)
			{
				onMyHead.erase(iter);
				--iter;
			}
		}
		onMyHead.clear();
	}

protected:
	string textureKey;
	POINT textureFrame;
	AttributeType attribute;
	
	vector<GameObject*> onMyHead;
	typedef vector<GameObject*>::iterator OnIter;

	D3DXVECTOR2 tileSize;
	D3DXVECTOR2 pivotPos;

	bool isSelected;
};