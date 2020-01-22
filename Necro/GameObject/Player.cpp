#include "stdafx.h"
#include "Player.h"



Player::Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	_ImageManager->AddFrameTexture("PlayerHeadRight", ResourcePath + L"Player/PlayerHeadRight.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerBodyRight", ResourcePath + L"Player/PlayerBodyRight.png", 4, 10);
	_ImageManager->AddFrameTexture("PlayerHeadLeft", ResourcePath + L"Player/PlayerHeadLeft.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerBodyLeft", ResourcePath + L"Player/PlayerBodyLeft.png", 4, 10);

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

	_RenderPool->Request(this, RenderManager::Layer::Object);
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
}


Player::~Player()
{
}

void Player::Init()
{
	GameObject::Init();
}

void Player::Release()
{
	GameObject::Release();
	_RenderPool->Request(this, RenderManager::Layer::Object);
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
}

void Player::PreUpdate()
{

}

void Player::Update(float tick)
{
	if (bActive == false) return;

	GameObject::Update(tick);

	//currentState->Excute();
	
	interver += tick * 4;

	if (interver > 1.f) {
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
	if (bActive == false) return;
	
	// 이미지 위치 보정 (-20);
	_ImageManager->FindTexture(body)->FrameRender(FloatRect(D3DXVECTOR2(_pos.x,_pos.y-20), _size, Pivot::CENTER), nullptr, frameX, frameY);
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

void PlayerIdle::Excute()
{
	// 여기서 타일을 검사한 뒤에 결과 값에 따라 move,attact,idle 중 하나로 이동 하면 됨 
	// 무기 장착 하거나 했을때 상태변화를 어떻게 줘야 할까? >> 무기는 

	_GameWorld->GetTileManager()->Tile(2, 3);	//이걸로 해당씬의 타일을 불러올 수 있음 
	//_GameWorld->GetBeatManager();				// 이거는 비트용

	if (KeyCode->Down(VK_LEFT))
	{
		me-> head = "PlayerHeadLeft";
		me-> body = "PlayerBodyLeft";

		me->startTime = 0;							// 시작 시간 초기화
		me->startPos = me->_pos;					// 시작 위치 
		me->destination.x = me->_pos.x -52;			// 목적지

		
		//_GameWorld->GetTileManager()
		//if (me->tilemanger->Tile({ me->tileNode->GetIndex().x - 1, me->tileNode->GetIndex().y})->GetAttribute() != ObjStatic)
		//{
		//	me->ChangeState("Move");
		//}
	}
	else if (KeyCode->Down(VK_RIGHT))
	{
		me->head = "PlayerHeadRight";
		me->body = "PlayerBodyRight";

		me->startTime = 0;
		me->startPos = me->_pos;
		me->destination.x = me->_pos.x + 52; 

		me->ChangeState("Move");
	}
	else if (KeyCode->Down(VK_UP))
	{
		me->startTime = 0;
		me->startPos = me->_pos;
		me->destination.y = me->_pos.y - 52; 

		me->ChangeState("Move");
	
	}
	else if (KeyCode->Down(VK_DOWN))
	{
		me->startTime = 0;
		me->startPos = me->_pos;
		me->destination.y = me->_pos.y + 52; 

		me->ChangeState("Move");
	}
}

void PlayerIdle::Exit()
{
}

void PlayerMove::Enter()
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

void PlayerAttack::Excute()
{
}

void PlayerAttack::Exit()
{
}
