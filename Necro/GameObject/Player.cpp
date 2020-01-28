#include "stdafx.h"
#include "Player.h"
#include "./GameObject/Map/TileNode.h"


Player::Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	 moveType = MoveType_Control;

	frameX = frameY = 0;
	this->size = size;
	position = pos;
	imagePos = pos;
	rc = FloatRect(pos, size, Pivot::CENTER);
	destination = pos;
	interver = 0;
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
	_RenderPool->Remove(this, RenderManager::Layer::Object);
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}

void Player::ControlUpdate()
{
	currentState->BeatExcute();
}

void Player::MissControlUpdate()
{

}

void Player::Update(float tick)
{
	GameObject::Update(tick);

	currentState->Excute();


	interver += tick * 4;

	if (interver > 0.5f) {
		frameX++;
		interver = 0;
	}
	if (frameX > 2) {
		frameX = 0;
	}

	rc = FloatRect(position, size, Pivot::CENTER);
}


void Player::Render()
{
	
	
	// 이미지 위치 보정 (-20);
	// 이미지만 점프 시킬꺼면 변수를 _포즈 말고 다른거 써야됨 . >> 포즈는 인덱스 검출하고 그래서 그냥 중점에 박혀있는게 좋기 때문.. 
	_ImageManager->FindTexture("PlayerShadow")->Render(FloatRect(D3DXVECTOR2(position.x, position.y), D3DXVECTOR2(size.x, size.y / 4), Pivot::CENTER), nullptr);
	_ImageManager->FindTexture(body)->FrameRender(FloatRect(D3DXVECTOR2(imagePos.x, imagePos.y - 20), size, Pivot::CENTER), nullptr, frameX, frameY);
	_ImageManager->FindTexture(head)->FrameRender(FloatRect(D3DXVECTOR2(imagePos.x, imagePos.y - 20), size, Pivot::CENTER), nullptr, frameX, frameY);
}

void Player::ImguiRender()
{
	ImGui::Begin("Info");
	{
		//ImGui::Text("Tick : %f", Time::Delta());
		ImGui::Text("PosX : %.2f, PosY : %.2f", position.x, position.y);
		ImGui::Text("startTime : %.2f", startTime);
		ImGui::Text("destinationX : %.2f, destinationY : %.2f", destination.x, destination.y);

		POINT XY = PosToIndex(position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
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

	me->myIndex = PosToIndex(me->position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());


	if (KeyCode->Down(VK_LEFT))
	{
		me->head = "PlayerHeadLeft";
		me->body = "PlayerBodyLeft";

		//_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(me);// 원래 있던 타일 삭제하고
		//leftTilePos->AddObject(me); // 플레이어를 타일에 등록한다.

		// 플레이어가 돌아다니는 발판 마다 이거 해줘야됨 ( 등록 / 삭제 
		// 그럼 일단 시작할때 INIT?에서 플레이어 발판 등록 해주고 이동할때마다 삭제 - 등록 해주면 될거같음
		// 1. 플레이어 수치이동으로 다시 바꾸고 ? 일단 인덱스 해보자 -> 수정 했음 
		// 2. 발판 등록 해주고 
		// 3. 삽 되는거 확인한 다음에 >> 되면 인덱스 검출 되는거니까 
		// 4. 공격 하는거 확인 하자 
		// -> 일단은 이동 범위로 하기. 0번쨰 검출할 타일이 이거인거임 .

	
		// 왠진 모르겠지만 이 이프문 두개를 &&로 묶어서 같이 놓으면 인덱스에 오류생겨서 터짐 
		// 갈 곳의 인덱스가 맵밖이 아니고 , 장애물이 아닌경우 > > > 움직여라!
		if (me->myIndex.x - 1 >= 0) {
			// _GameWorld->GetTileManager .... 같이 외부에서 참조하는 애를 여러번 호출 하기 싫으면 
			// temp 같은 변수 선언해서 거기에 담아 놓고 쓰면 한번만 호출하게 되서 훨씬 빠르고, if 밖으로 나가게되면 자연스럽게 삭제된다.
			TileNode* leftTilePos;
			leftTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x , me->myIndex.y);
			
			if (leftTilePos->GetAttribute() == ObjDestructable)leftTilePos->SendCallbackMessage("ShovelHit");
			
			if (leftTilePos->GetAttribute() != ObjDestructable)
			{
				me->startTime = 0;																					  // 시작 시간 초기화
				me->startPos = me->position;																			  // 시작 위치 
				//_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(me);// 원래 있던 타일 삭제하고
				//leftTilePos->AddObject(me); // 플레이어를 타일에 등록한다.
				me->destination.x = leftTilePos->GetPos().x; // 목적지
				me->jumpPos = D3DXVECTOR2(me->destination.x + 26, me->startPos.y - 40); 

				me->ChangeState("Move");
			}
		}

	}
	else if (KeyCode->Down(VK_RIGHT))
	{
		me->head = "PlayerHeadRight";
		me->body = "PlayerBodyRight";

		// mapSize 멀리 돌아갈 필요 없이 바로 소환할수있으면 소환해서 하는게 좋다 . 
		if (me->myIndex.x + 1 < TileManager::mapSize.x)
		{
			TileNode* rightTilePos;
			rightTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x+2 , me->myIndex.y);

			if (rightTilePos->GetAttribute() == ObjDestructable)rightTilePos->SendCallbackMessage("ShovelHit");
			
			if (rightTilePos->GetAttribute() != ObjDestructable)
			{
				me->startTime = 0;
				me->startPos = me->position;
				me->destination.x = rightTilePos->GetPos().x;
				me->jumpPos = D3DXVECTOR2(me->destination.x-26, me->startPos.y-40); 

				me->ChangeState("Move");
			}
		}
	}
	else if (KeyCode->Down(VK_UP))
	{
		if (me->myIndex.y - 1 >= 0)
		{
			TileNode* upTilePos;
			upTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x , me->myIndex.y-1);
			
			//upTilePos->GetObjects();




			if (upTilePos->GetAttribute() != ObjDestructable)
			{
				me->startTime = 0;
				me->startPos = me->position;
				me->destination.y = upTilePos->GetPos().y;
				me->jumpPos = D3DXVECTOR2(me->destination.x , me->startPos.y - 78); 
				
				me->ChangeState("Move");
			}

			// 이게 아래 있어야 부수기만함. 서순이 이동 전에 있으면 부수자마자 이동으로 가기때문에 이동 가능한 타일이라 부수는 동시에 이동함(이거 완전 창 아니냐)
			if (upTilePos->GetAttribute() == ObjDestructable)
			{
				// 해당 오브젝트 찾아서 조지는듯 
				vector<GameObject*> tempArr = upTilePos->GetObjects();
				for (int i = 0; i < tempArr.size(); ++i)
				{
					tempArr[i]->SendCallbackMessage("ShovelHit");
				}
			}
		}
	}
	else if (KeyCode->Down(VK_DOWN))
	{
		if (me->myIndex.y + 1 < TileManager::mapSize.y)
		{
			TileNode* downTilePos;
			downTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y + 1);

			if (downTilePos->GetAttribute() == ObjDestructable)downTilePos->SendCallbackMessage("ShovelHit");

			if (downTilePos->GetAttribute() != ObjDestructable)
			{
				me->startTime = 0;
				me->startPos = me->position;
				me->destination.y = downTilePos->GetPos().y;
				me->jumpPos = D3DXVECTOR2(me->destination.x, me->startPos.y - 13);

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

	me->position = Math::Lerp(me->startPos, me->destination, factor);	// Lerp함수를 이용하여 목표 거리를(destination-startPos)  일정 비율(factor)로 이동

	// 점프 왤케 이상하지
	if (factor <= 0.4f)												
	{
		me->imagePos = Math::Lerp(me->startPos, me->jumpPos, factor);
	}
	if (factor > 0.4f && factor < 1.0f)
	{
		me->imagePos = Math::Lerp(me->startPos, me->destination, factor);
	}


	if (factor >= 1.0f)										//비울(factor) >= 1  >>>> 목표지점까지 가는데 걸린 시간이 목표한 시간과 같거나 크다 = 도착했다
	{
		me->position = me->destination;						// 위치 보정 할꺼면 위치보정 
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
