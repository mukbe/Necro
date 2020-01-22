#include "stdafx.h"
#include "Player.h"
#include "TileNode.h"


Player::Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{

	frameX = frameY = 0;
	_pos = pos;
	_size = size;
	rc = FloatRect(pos, size, Pivot::CENTER);
	destination = pos;
	interver = 0;
	nowPos.x = nowPos.y = goPos.x = goPos.y = 0;

	head = "PlayerHeadRight";
	body = "PlayerBodyRight";
	startTime = 0;

	currentState = nullptr;
	stateList.insert(make_pair("Idle", new PlayerIdle(this)));
	stateList.insert(make_pair("Move", new PlayerMove(this)));
	stateList.insert(make_pair("Attack", new PlayerAttack(this)));
	ChangeState("Idle");

}


Player::~Player()
{
}

void Player::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
	_RenderPool->Request(this, RenderManager::Layer::Imgui);

}

void Player::Release()
{
	GameObject::Release();
	_RenderPool->Request(this, RenderManager::Layer::Object);
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
}

void Player::ControlUpdate()
{
	currentState->BeatExcute();
}

void Player::Update(float tick)
{
	GameObject::Update(tick);

	currentState->Excute();


	interver += tick * 4;

	if (interver > 0.35f) {
		frameX++;
		interver = 0;
	}
	if (frameX > 2){
		frameX = 0;
	}

	rc = FloatRect(_pos, _size, Pivot::CENTER);
}


void Player::Render()
{
	// 이미지 위치 보정 (-20);
	_ImageManager->FindTexture(body)->FrameRender(FloatRect(D3DXVECTOR2(_pos.x, _pos.y - 20), _size, Pivot::CENTER), nullptr, frameX, frameY);
	_ImageManager->FindTexture(head)->FrameRender(FloatRect(D3DXVECTOR2(_pos.x, _pos.y - 20), _size, Pivot::CENTER), nullptr, frameX, frameY);
}

void Player::ImguiRender()
{
	ImGui::Begin("Info");
	{
		//ImGui::Text("Tick : %f", Time::Delta());
		ImGui::Text("PosX : %.2f, PosY : %.2f", _pos.x, _pos.y);
		ImGui::Text("startTime : %.2f", startTime);
		ImGui::Text("destinationX : %.2f, destinationY : %.2f", destination.x, destination.y);

		POINT XY = PosToIndex(_pos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		ImGui::Text("Index : %d, %d", XY.x, XY.y);
		ImGui::Text("Index-1 : %d, %d", XY.x - 1, XY.y - 1);
		ImGui::Text("MapSize : %d, %d", _GameWorld->GetTileManager()->GetMapSize().x, _GameWorld->GetTileManager()->GetMapSize().y);

	}
	ImGui::End();

}

void Player::ChangeState(string str)
{
	// 업데이트 하던 상태를 끝내고 입력한 상태를 실행한다.

	if (currentState)
		currentState->Exit();

	currentState = stateList[str];

	if (currentState)
		currentState->Enter();
}

void PlayerIdle::Enter()
{

}

void PlayerIdle::BeatExcute()
{
	// 여기서 타일을 검사한 뒤에 결과 값에 따라 move,attact,idle 중 하나로 이동 하면 됨 
// 무기 장착 하거나 했을때 상태변화를 어떻게 줘야 할까? >> 무기는 

	me->myIndex = PosToIndex(me->_pos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());


	if (KeyCode->Down(VK_LEFT))
	{
		me->head = "PlayerHeadLeft";
		me->body = "PlayerBodyLeft";


		// 왠진 모르겠지만 이 이프문 두개를 &&로 묶어서 같이 놓으면 인덱스에 오류생겨서 터짐 
		// 갈 곳의 인덱스가 맵밖이 아니고 , 장애물이 아닌경우 > > > 움직여라!
		if (me->myIndex.x - 1 >= 0) {
			if (_GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetAttribute() != ObjStatic)
			{
				me->startTime = 0;																					  // 시작 시간 초기화
				me->startPos = me->_pos;																			  // 시작 위치 
				//me->destination.x = me->_pos.x - _GameWorld->GetTileManager()->GetTileSize().x; >> 이렇게 계산을 이곳저곳에서 하지 말자. 
				me->destination.x = _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetPos().x; // 목적지

				me->ChangeState("Move");
			}
		}

	}
	else if (KeyCode->Down(VK_RIGHT))
	{
		me->head = "PlayerHeadRight";
		me->body = "PlayerBodyRight";

		if (me->myIndex.x + 1 < _GameWorld->GetTileManager()->GetMapSize().x)
		{
			if (_GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y)->GetAttribute() != ObjStatic)
			{
				me->startTime = 0;
				me->startPos = me->_pos;
				me->destination.x = _GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y)->GetPos().x;

				me->ChangeState("Move");
			}
		}
	}
	else if (KeyCode->Down(VK_UP))
	{
		if (me->myIndex.y - 1 >= 0)
		{
			if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y - 1)->GetAttribute() != ObjStatic)
			{
				me->startTime = 0;
				me->startPos = me->_pos;
				me->destination.y = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y - 1)->GetPos().y;

				me->ChangeState("Move");
			}
		}
	}
	else if (KeyCode->Down(VK_DOWN))
	{
		if (me->myIndex.y + 1 < _GameWorld->GetTileManager()->GetMapSize().y)
		{
			if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y + 1)->GetAttribute() != ObjStatic)
			{
				me->startTime = 0;
				me->startPos = me->_pos;
				me->destination.y = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y + 1)->GetPos().y;

				me->ChangeState("Move");
			}
		}
	}
}

void PlayerIdle::Excute()
{

}

void PlayerIdle::Exit()
{
}

void PlayerMove::Enter()
{

}

void PlayerMove::BeatExcute()
{
}

void PlayerMove::Excute()
{
	// 작동 시작 시간 / 목표 시간 ==1 이 될때 마다 (= 목표 시간마다) 작동해라
	float factor = me->startTime / 0.25f;							// lerp 함수 안에 넣을 factor , 전체 시간분에 목표시간

	me->startTime += Time::Tick();									// 0으로 초기화한 startTime에 tick을 더해라 

	me->_pos = Math::Lerp(me->startPos, me->destination, factor);	// Lerp함수를 이용하여 목표 거리를(destination-startPos)  일정 비율(factor)로 이동

	if (factor >= 1.0f)												//비울(factor) >= 1  >>>> 목표지점까지 가는데 걸린 시간이 목표한 시간과 같거나 크다 = 도착했다
	{
		//me->_pos = me->destination;								// 위치 보정 할꺼면 위치보정 
		me->ChangeState("Idle");
	}

}

void PlayerMove::Exit()
{
}

void PlayerAttack::Enter()
{
}

void PlayerAttack::BeatExcute()
{
}

void PlayerAttack::Excute()
{
}

void PlayerAttack::Exit()
{
}
