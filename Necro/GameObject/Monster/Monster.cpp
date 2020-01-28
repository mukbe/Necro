#include "stdafx.h"
#include "Monster.h"
//#include "TileNode.h"
#include "./Systems/Manage/TileManager.h""
#include "./GameObject/Map/TileNode.h"

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
	myIndex = { 0,0 };
	startPos = { 0,0 };
	//mynextIndex = { 0,0 };
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

void Monster::Update(float tick)
{
	if (currentState) // 값이 있으면 업데이트 시켜라.
		currentState->Update();
}

void Monster::ControlUpdate()
{
	//mynextIndex = PosToIndex(endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
	
	monsterBeat--;

	

	
	if (monsterBeat == 0) {
		ChangeState("Move");
		if (name == "BlueSlime") 
		{
			monsterBeat = 2;
		}
		if (name == "Skeleton") 
		{
			monsterBeat = 2;
		}
		if (name == "Bat")
		{
			monsterBeat = 2;
		}

	}






}

void Monster::Render()
{
}

void Monster::ImguiRender()
{
}




//현재 상태 바꿔주는 함수~
void Monster::ChangeState(string key)
{
	MonsterStateBase* state = states[key];
	state->Enter();
	currentState = state;
}

//움직임 클래쓰
void MonsterStateOneStep::Enter()
{
	
	me->startTime = 0.f;
	//me->realtime = 0.f;

}

void MonsterStateOneStep::Update()
{

	
	//시간 연산
	//me->realtime = me->startTime;
	me->startTime += Time::Tick()*4;
	
	
	//스켈레톤 움직임
	if (me->name == "Skeleton")
	{
		

			if (me->realtime <= 1.f)
			{

				//batX랑 batY는 박쥐좌표인데 일단 따라가게 해놓은거임
				if (me->startPos.x < batX) {
					me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				}
				if (me->startPos.x > batX) {
					me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				}
				if (me->startPos.y > batY) {
					me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
				}
				if (me->startPos.y < batY) {
					me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
				}

			}
		
		if (me->startTime > 1.f)
		{
			me->ChangeState("Idle");
		}
	}



	//박쥐 움직임
	if (me->name == "Bat") 
	{
		

			if (me->startTime <= 1.f)
			{
				me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
			}
		
		if (me->startTime > 1.f)
		{
			me->ChangeState("Idle");
		}

	}
	//파란 슬라임 움직임
	if (me->name == "BlueSlime") {

		
		if (me->startTime <= 1.f)
		{
			me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
			me->firstmove = true;
			
		}
		if (me->startTime > 1.f)
		{
			me->ChangeState("Idle");
		}

	}


	




}

void MonsterStateIdle::Enter()
{
	
	//몬스터 현재 위치 타일인덱스

	//me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
	
	//_TileSize로 타일사이즈 쓸고얌
	float _TileSize = _GameWorld->GetTileManager()->GetTileSize().x;
	me->startTime = 0.f;
	//me->realtime = 0.f;
	
	//모든 몬스터는 갈위치에 벽이 있으면 못움직이게 할꼬얌
	//오른쪽에 있으면 


	//_GameWorld->GetTileManager()->Tile(me->myIndex.x+1, me->myIndex.y);
	//TileNode * currentPos=_GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y)

	
	/*

	//왼쪽에있으면
	BlockPos = _GameWorld->GetTileManager()->Tile(me->myIndex.x -1, me->myIndex.y);
	if (BlockPos->GetAttribute() != ObjStatic)
	{
		me->endPos.x = me->startPos.x + _TileSize;
	}
	//위에있으면
	BlockPos = _GameWorld->GetTileManager()->Tile(me->myIndex.x , me->myIndex.y-1);
	if (BlockPos->GetAttribute() != ObjStatic)
	{
		me->endPos.y = me->startPos.y + _TileSize;
	}
	//아래있으면
		BlockPos = _GameWorld->GetTileManager()->Tile(me->myIndex.x , me->myIndex.y+1);
		if (BlockPos->GetAttribute() != ObjStatic)
		{
			me->endPos.y = me->startPos.y - _TileSize;
		}
	*/

	/*
	if (_GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y)->GetAttribute() != ObjStatic
		&& _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetAttribute() != ObjStatic
		&& _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y + 1)->GetAttribute() != ObjStatic
		&& _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y -1)->GetAttribute() != ObjStatic)
	
	*/

	//스켈레톤 아이덜
	if (me->name == "Skeleton")
	{
	
			

			

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
	if (me->name == "Bat") 
	{
		/*me->startPos.x = me->endPos.x;
		me->startPos.y = me->endPos.y;*/
		int batmove = Math::Random(0, 3);

		me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		me->mynextIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		
		

		//_GameWorld->GetTileManager()->Tile(me->myIndex)->AddObject(me);

			me->startPos.x = me->endPos.x;
			me->startPos.y = me->endPos.y;
			batX = me->startPos.x;
			batY = me->startPos.y;


			switch (batmove) {

				if (me->myIndex.x <= 0 || me->myIndex.y <= 0) {
					me->myIndex = POINT{ 1,1 };
				}
				

			case 0:
				me->endPos.x = me->startPos.x + _TileSize;
				//me->endPos.x = me->startPos.x + _TileSize;
				//if (_GameWorld->GetTileManager()->Tile(me->myIndex.x-1, me->myIndex.y)->GetAttribute() != ObjDestructable)
				//{
					//me->endPos.x = me->startPos.x - _TileSize;
				//}
				/*else 
				{
					me->endPos.x = me->startPos.x + _TileSize;
				}*/
				break;

			case 1:
				me->endPos.x = me->startPos.x - _TileSize;
				//me->endPos.x = me->startPos.x - _TileSize;
				//if (_GameWorld->GetTileManager()->Tile(me->myIndex.x+1, me->myIndex.y)->GetAttribute() != ObjDestructable)
				//{
					//me->endPos.x = me->startPos.x + _TileSize;
				//}
				/*else
				{
					me->endPos.x = me->startPos.x - _TileSize;
					
				}*/
				break;

			case 2:
				me->endPos.y = me->startPos.y - _TileSize;
				//me->endPos.y = me->startPos.y + _TileSize;
				//if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y+1)->GetAttribute() != ObjDestructable)
				//{
					//me->endPos.y = me->startPos.y + _TileSize;
				//}
				/*else
				{
					me->endPos.y = me->startPos.y - _TileSize;
					
				}*/
				break;

			case 3:
				me->endPos.y = me->startPos.y + _TileSize;
				//me->endPos.y = me->startPos.y - _TileSize;
				//if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y-1)->GetAttribute() != ObjDestructable)
				//{
					//me->endPos.y = me->startPos.y - _TileSize;
				//}
				//else
				//{
					//me->endPos.y = me->startPos.y + _TileSize;
					
				//}

				break;


				}

			//내위치가 타일안에 있을때만 움직임

			

			if (me->mynextIndex.x < 0 )
			{
				me->endPos.x = me->startPos.x + _TileSize;
			}
			if (me->mynextIndex.x >= TileManager::mapSize.x)
			{
				me->endPos.x = me->startPos.x - _TileSize ;
			}
			if (me->mynextIndex.y < 0)
			{
				me->endPos.y = me->startPos.y + _TileSize ;
				}
			if (me->mynextIndex.y >= TileManager::mapSize.y)
			{
				me->endPos.y = me->startPos.y - _TileSize ;
				}
			
			
			
			/*
			if (_GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetAttribute() == ObjStatic)
			{
				me->endPos.x = me->startPos.x + _TileSize;
			}
			if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y + 1)->GetAttribute() == ObjStatic)
			{
				me->endPos.y = me->startPos.y - _TileSize;
			}
			if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y - 1)->GetAttribute() == ObjStatic)
			{
				me->endPos.y = me->startPos.y + _TileSize;
			}
*/
		
			
			

		
	}


	//파란슬라임 아이덜
	if (me->name == "BlueSlime") 
	{

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
	

	//me->ChangeState("Move");
		//me->ChangeState("Move");
	
		//me->ChangeState("Move");
	
}