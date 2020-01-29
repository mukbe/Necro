#include "stdafx.h"
#include "Monster.h"
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
	//startPos = { 0,0 };
	//mynextIndex = { 0,0 };
	ChangeState("Idle");
	
}

Monster::~Monster()
{
}

void Monster::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
}

void Monster::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}

void Monster::Update(float tick)
{
	if (currentState) // 값이 있으면 업데이트 시켜라.
		currentState->Update();
}

void Monster::ControlUpdate()
{
	
	monsterBeat--;

	
	//각자 다른 비트마다 움직일수 있게
	
	if (monsterBeat == 0) 
	{
		ChangeState("Move");
		
		if (name == "Skeleton") 
		{
			monsterBeat = 2;
		}
		if (name == "Bat")
		{
			monsterBeat = 1;
		}
		if (name == "BlueSlime")
		{
			monsterBeat = 2;
		}
		if (name == "Minotaur")
		{
			monsterBeat = 1;
		}

	}






}

void Monster::Render()
{
}

void Monster::ImguiRender()
{

	ImGui::Begin("mon");
	{
		if (name == "Bat")
		{
			ImGui::Text("PosX : %.2f, PosY : %.2f", myIndex.x, myIndex.y);
		}

		

	}
	ImGui::End();



}




//현재 상태 바꿔주는 함수~
void Monster::ChangeState(string key)
{
	MonsterStateBase* state = states[key];
	state->Enter();
	currentState = state;
}

void Monster::ProcessDestroy()
{
	life--;
	if (life <= 0)
	{
		//이펙트 추가 필요.


		this->SetActive(false);
	}
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
	me->startTime += Time::Tick()*4;
	
	

	//스켈레톤 움직임
	if (me->name == "Skeleton")
	{

		//for(int i=)
		//vector<GameObject*> tempArr = upTilePos->GetObjects(ObjectPlayer);


				//batX랑 batY는 박쥐좌표인데 일단 따라가게 해놓은거임
				if (me->startPos.x < batX) 
				{
					me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				}
			    else if (me->startPos.x > batX) 
				{
					me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				}
				else if (me->startPos.y > batY) 
				{
					me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
				}
				else if (me->startPos.y < batY) 
				{
					me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
				}


				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectMonster, me);
	}



	//박쥐 움직임
	if (me->name == "Bat") 
	{
		

				me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);


				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectMonster, me);
	}

	//파란 슬라임 움직임
	if (me->name == "BlueSlime") 
	{
			me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);	


			_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectMonster, me);
	}


	//미노 타우루스 움직임
	if (me->name == "Minotaur")
	{
		if (me->startPos.x < batX) {
			me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
		}
		else if (me->startPos.x > batX) {
			me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
		}
		else if (me->startPos.y > batY) {
			me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
		}
		else if (me->startPos.y < batY) {
			me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
		}

		_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectMonster, me);
	}







	//1초가 넘어가면 모두들 아이덜 상태로 돌아가연
	if (me->startTime > 1.f)
	{
		me->ChangeState("Idle");
	}


}



void MonsterStateAtk::Enter()
{

	

}

void MonsterStateAtk::Update()
{

	

}





void MonsterStateIdle::Enter()
{
	//내위치 등록
	//_GameWorld->GetTileManager()->Tile(2, 2)->AddObject(me);
	//내위치 삭제
	//_GameWorld->GetTileManager()->Tile(2, 2)->DeleteObject(me);
	
	//_TileSize로 타일사이즈 쓸고얌
	float _TileSize = _GameWorld->GetTileManager()->GetTileSize().x;
	
	//me->startTime = 0.f;
	

	//스켈레톤 아이덜
	if (me->name == "Skeleton")
	{
	
		//끝난 좌표를 다시 시작 좌표로 바꿈
				me->startPos.x = me->endPos.x;
				me->startPos.y = me->endPos.y;

				me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
				


				if (me->myIndex.x <= 0) me->myIndex.x = 1;

				if (me->myIndex.y <= 0) me->myIndex.y = 1;

				if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

				if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);
				//짭스타 위치비교후 추적
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
	
		//0에서 3까지 랜덤으로 하나 뽑아서 스위치문에서 움직일 곳 줌
		int batmove = Math::Random(0, 3);

		//끝난 좌표를 다시 시작 좌표로 바꿈
			me->startPos.x = me->endPos.x;
			me->startPos.y = me->endPos.y;
			//임시로 박쥐 좌표저장(플레이어대신해서 추적할 곳)
			batX = me->startPos.x;
			batY = me->startPos.y;
			//박쥐 현재 좌표 타일 인덱스 구해옴
			me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());

			

			//내 인덱스가 타일범위를 벗어나 터질수도있으니 예외처리
			if (me->myIndex.x <= 0 ) me->myIndex.x = 1; 
				
			if (me->myIndex.y <= 0) me->myIndex.y = 1;

			if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

			if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

			_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);

			//0~3중에 하나 뽑는다
			switch (batmove) {

			case 0:
				//못가는 오브젝트 타입아니라면 이동
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x-1, me->myIndex.y)->GetAttribute() != ObjDestructable)
				{
					me->endPos.x = me->startPos.x - _TileSize;
				}
				//못가는 오브젝트 타입이면 반대로이동
				else 
				{
					me->endPos.x = me->startPos.x + _TileSize;
				}
				break;

			case 1:

				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x+1, me->myIndex.y)->GetAttribute() != ObjDestructable)
				{
					me->endPos.x = me->startPos.x + _TileSize;
				}
				else
				{
					me->endPos.x = me->startPos.x - _TileSize;
					
				}
				break;

			case 2:
				
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y+1)->GetAttribute() != ObjDestructable)
				{
					me->endPos.y = me->startPos.y + _TileSize;
				}
				else
				{
					me->endPos.y = me->startPos.y - _TileSize;
					
				}
				break;

			case 3:
				
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y-1)->GetAttribute() != ObjDestructable)
				{
					me->endPos.y = me->startPos.y - _TileSize;
				}
				else
				{
					me->endPos.y = me->startPos.y + _TileSize;
					
				}

				break;


				}
		
	}


	//파란슬라임 아이덜
	if (me->name == "BlueSlime") 
	{


		me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		
		
		if (me->myIndex.x <= 0) me->myIndex.x = 1;

		if (me->myIndex.y <= 0) me->myIndex.y = 1;

		if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

		if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;


		_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);
		//갔던 좌표와 다시갈 좌표를 바꿔줌(위아래 반복)
			D3DXVECTOR2 temp;
			temp.y = me->endPos.y;
			me->endPos.y = me->startPos.y;
			me->startPos.y = temp.y;	
		
	}

	//미노타우루스 아이덜
	if (me->name == "Minotaur")
	{

		//끝난 좌표를 다시 시작 좌표로 바꿈
		me->startPos.x = me->endPos.x;
		me->startPos.y = me->endPos.y;


		me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		

		if (me->myIndex.x <= 0) me->myIndex.x = 1;

		if (me->myIndex.y <= 0) me->myIndex.y = 1;

		if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

		if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

		_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);
		//짭스타 위치비교후 추적
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



}

void MonsterStateIdle::Update()
{
	
	
		//me->ChangeState("Move");
	
}