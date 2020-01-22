#pragma once
#include "UIBase.h"

class Note : public UIBase
{
public:
	enum NoteState
	{
		Note_None, Note_Move, Note_Grace,
	};

public:
	Note(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Note();

	virtual void Init();
	void Init(float lerpTime);

	virtual void Release();

	virtual void ControlUpdate();
	// 틱으로 올 때 마다 덮어 씌운다고 생각을하면되나 .
	virtual void Update(float tick);

	virtual void Render();
	
	void OnBeatEnter();

	NoteState GetState() { return state; }

private:
	float ratio;
	float saveTime;
	float gracePeriod;

	shared_ptr<Texture> tex;

	NoteState state;
	FloatRect reflect;

};

