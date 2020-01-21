#include "stdafx.h"
#include "Monster.h"



Monster::Monster(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: GameObject(name, pos, size)
{
	currentState = nullptr;

	states.insert(make_pair("Idle", new MonsterStateIdle(this)));
	states.insert(make_pair("Move", new MonsterStateOneStep(this)));
	startTime = 0.f;
	realtime = 0.f;
	//startPos = pos;
	//endPos = { pos.x+52.f, pos.y+52.f };
	firstmove = false;
	ChangeState("Idle");
}

Monster::~Monster()
{
}

void Monster::Init()
{
}

void Monster::Release()
{
}

void Monster::PreUpdate()
{
}

void Monster::Update(float tick)
{
	if (currentState) // 값이 있으면 업데이트 시켜라.
		currentState->Update();
}

void Monster::ControlUpdate()
{
}

void Monster::Render()
{
}

void Monster::ImguiRender()
{
}

void Monster::SettingCenterXY(float tilesize)
{
	rc.left = x - tilesize / 2;
	rc.right = x + tilesize / 2;
	rc.top = y - tilesize / 2;
	rc.bottom = y + tilesize / 2;
}

void Monster::MoveAndCheck()
{
}

void Monster::ChangeState(string key)
{
	MonsterStateBase* state = states[key];
	state->Enter();
	currentState = state;
}


void MonsterStateOneStep::Enter()
{
	
	me->startTime = 0.f;
	me->realtime = 0.f;
}

void MonsterStateOneStep::Update()
{
	if (me->name == "BlueSlime") {

		me->realtime = me->startTime ;
		me->startTime += Time::Tick()*2;
		if (me->realtime <= 1.f) 
		{
			me->x = Math::Lerp(me->startPos.x, me->endPos.x, me->realtime);
			me->firstmove = true;
			
		}
		if (me->realtime > 1.f)
		{
			me->ChangeState("Idle");
		}

	}
}

void MonsterStateIdle::Enter()
{
	me->startTime = 0.f;
	me->realtime = 0.f;

	if (me->firstmove) {
		D3DXVECTOR2 temp;
		temp.x = me->endPos.x;
		me->endPos.x = me->startPos.x;
		me->startPos.x = temp.x;
	}
}

void MonsterStateIdle::Update()
{
	
		me->ChangeState("Move");
	
}