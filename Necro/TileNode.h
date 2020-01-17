#pragma once

#include "TileHelper.h"


class TileNode : public GameObject
{
public:
	TileNode(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~TileNode();

	virtual void Init(string textureStringKey = "NoneTexture", POINT textureFrameIndex = { 0,0 }, AttributeType type = ObjNone);
	virtual void Init(D3DXVECTOR2 pos, D3DXVECTOR2 size, string textureStringKey = "NoneTexture", POINT textureFrameIndex = { 0,0 }, AttributeType type = ObjNone);
	virtual void Release();
	virtual void PreUpdate();
	virtual void Update();
	virtual void PostUpdate();

	virtual void Render();
	virtual void ImguiRender();

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

	POINT GetIndex() { return posToIndex(this->GetPos()); }
	void SetIndex(POINT inputIndex) { this->SetPos(indexToPos(inputIndex)); }

	D3DXVECTOR2 GetPos() { return this->Transform().GetPos();}
	void SetPos(D3DXVECTOR2 inputPos) { this->Transform().SetPos(inputPos);}

	RECT GetCollision() { return rc.GetRect(); }

	D3DXVECTOR2 indexToPos(const POINT index)
	{
		return { index.x * _tileSize.x + (_tileSize.x / 2.f)
			    ,index.y * _tileSize.y + (_tileSize.y / 2.f) };
	}

	POINT posToIndex(const D3DXVECTOR2 pos)
	{
		return { static_cast<int>((pos.x - _tilePivotPos.x) / _tileSize.x),
			     static_cast<int>((pos.y - _tilePivotPos.y) / _tileSize.y) };
	}

protected:
	string textureKey;
	POINT textureFrame;
	AttributeType attribute;
};