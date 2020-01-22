#include "stdafx.h"
#include "Monster.h"


static float batX;
static float batY;

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
	ChangeState("Move");
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
	me->realtime = me->startTime;
	me->startTime += Time::Tick()*2;
	
	
	//스켈레톤 움직임
	if (me->name == "Skeleton")
	{

		if (me->realtime <= 1.f)
		{

			//0은 목표지점 좌표
			if (me->startPos.x < batX) {
				me->x = Math::Lerp(me->startPos.x, me->endPos.x, me->realtime);
			}
			if (me->startPos.x > batX) {
				me->x = Math::Lerp(me->startPos.x, me->endPos.x, me->realtime);
			}
		    if (me->startPos.y > batY) {
				me->y = Math::Lerp(me->startPos.y, me->endPos.y, me->realtime);
			}
			if(me->startPos.y < batY) {
				me->y = Math::Lerp(me->startPos.y, me->endPos.y, me->realtime);
			}

		}

		if (me->realtime > 1.f)
		{
			me->ChangeState("Idle");
		}
	}



	//박쥐 움직임
	if (me->name == "Bat") 
	{

		if (me->realtime <= 1.f)
		{
			me->x = Math::Lerp(me->startPos.x, me->endPos.x, me->realtime);
			me->y = Math::Lerp(me->startPos.y, me->endPos.y, me->realtime);
		}
		if (me->realtime > 1.f)
		{
			me->ChangeState("Idle");
		}

	}
	//파란 슬라임 움직임
	if (me->name == "BlueSlime") {

		
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
	float _TileSize = _GameWorld->GetTileManager()->GetTileSize().x;
	me->startTime = 0.f;
	me->realtime = 0.f;

	if (me->name == "Bat")
	{
		batX = me->startPos.x;
		batY = me->startPos.y;
	}

	//스켈레톤 아이덜
	if (me->name == "Skeleton") {
		me->startPos.x = me->endPos.x;
		me->startPos.y = me->endPos.y;

		if (me->startPos.x < batX)
		{
			me->endPos.x = me->startPos.x + _TileSize;
		}
		else if (me->startPos.y > batY)
		{
			me->endPos.y = me->startPos.y - _TileSize;
		}
		else if (me->startPos.x > batX)
		{
			me->endPos.x = me->startPos.x - _TileSize;
		}
		else if (me->startPos.y < batY)
		{
			me->endPos.y = me->startPos.y + _TileSize;
		}


	}




	//박쥐 아이덜
	if (me->name == "Bat") {
		me->startPos.x = me->endPos.x;
		me->startPos.y = me->endPos.y;
		int batmove= Math::Random(0, 3);
		switch (batmove) {

		case 0 :
			me->endPos.x = me->startPos.x + _TileSize;
			break;

		case 1 :
			me->endPos.x = me->startPos.x - _TileSize;
			break;

		case 2:
			me->endPos.y = me->startPos.y + _TileSize;
			break;

		case 3:
			me->endPos.y = me->startPos.y - _TileSize;
			break;


		}


	}


	//파란슬라임 아이덜
	if (me->name == "BlueSlime") {

		//if (me->firstmove) {
			D3DXVECTOR2 temp;
			temp.x = me->endPos.x;
			me->endPos.x = me->startPos.x;
			me->startPos.x = temp.x;
		//}
	}
}

void MonsterStateIdle::Update()
{
	
		me->ChangeState("Move");
	
}