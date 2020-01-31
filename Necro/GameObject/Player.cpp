#include "stdafx.h"
#include "Player.h"
#include "./GameObject/Map/TileNode.h"
#include ""


Player::Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	moveType = MoveType_Control;

	frameX = frameY = 0;
	this->size = size;
	position = pos;
	imagePos = pos;
	myIndex = PosToIndex(position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
	_GameWorld->GetTileManager()->Tile(myIndex.x, myIndex.y)->AddObject(ObjectPlayer, this); // 타일에 등록
	rc = FloatRect(pos, size, Pivot::CENTER);
	destination = pos;
	interver = 0;
	imageName = "NormalPlayer";
	playerDirection = PlayerRight;
	jumpPower = 0;
	gravity = 0;
	startTime = 0;

	AddCallback("PlayerHit", [&](TagMessage msg) {

		CAMERA->Shake();
		// 이팩트가 뜨고. > 나중에 추가해 준대
		// 피를 깍아준다. > 아직 구현 안되있음. 
		// 피격음 튼다. 

	});
	// 피를 업데이트에서 계속 확인해 주고 피가 0이 되면 캐릭터 죽인다음에 죽었다고 씬메니져? 같은곳에 넘겨야 할듯 

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
	Sight();
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
	_ImageManager->FindTexture("PlayerShadow")->Render(FloatRect(D3DXVECTOR2(position.x, position.y + 5), D3DXVECTOR2(size.x, size.y / 4), Pivot::CENTER), nullptr);
	_ImageManager->FindTexture(imageName)->FrameRender(FloatRect(D3DXVECTOR2(position.x, imagePos.y - 20), size, Pivot::CENTER), nullptr, frameX, frameY);

}

void Player::ImguiRender()
{
	ImGui::Begin("Player");
	{
		//ImGui::Text("Tick : %f", Time::Delta());
		ImGui::Text("PosX : %.2f, PosY : %.2f", position.x, position.y);
		ImGui::Text("startTime : %.2f", startTime);
		ImGui::Text("destinationX : %.2f, destinationY : %.2f", destination.x, destination.y);

		POINT XY = PosToIndex(position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		ImGui::Text("Index : %d, %d", XY.x, XY.y);
		ImGui::Text("playerDirection : %d", playerDirection);

	}
	ImGui::End();

}

vector<vector<int> > GetDistance(int x, int y, vector<vector<int> > cells)
{
	const int INF = 0x7FFFFF;
	vector<vector<int> > distance(cells.size());

	for (int i = 0; i < distance.size(); i++)
		distance[i].assign(cells[i].size(), INF);  // size만큼 INF 를 할당한다
	
	queue<pair<int, int> > q;

	q.push(make_pair(x, y));
	distance[x][y] = 0;

	while (!q.empty())
	{
		pair<int, int> curPoint = q.front();
		q.pop();
		int curDistance = distance[curPoint.first][curPoint.second];
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				if ((i + j) % 2 == 0) continue;
				pair<int, int> nextPoint(curPoint.first + i, curPoint.second + j);
				if (nextPoint.first >= 0 && nextPoint.first < cells.size()
					&& nextPoint.second >= 0 && nextPoint.second < cells[nextPoint.first].size()
					//&& cells[nextPoint.first][nextPoint.second] != BARRIER
					&& distance[nextPoint.first][nextPoint.second] > curDistance + 1)
				{
					distance[nextPoint.first][nextPoint.second] = curDistance + 1;
					q.push(nextPoint);
				}
			}
	}
	return distance;
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

void Player::FloodFill(POINT index, int sight)
{
	// index에 플레이어의 인덱스가 들어와야 함.  
	vector<GameObject*> temp;
	TileNode* tile = _TileMap->Tile(index.x, index.y);

	if (tile == nullptr)return;
	if (sight <= 0) return;

	int proveX[4] = { 0,-1,0,1 };
	int proveY[4] = { -1,0,1,0 };
	

	shownTiles.push_back(tile);

	if (!tile->IsActive())
	{
		_MessagePool->ReserveMessage(tile, "Active");
	}
	else
	{
			if (tile->IsShow()) // 조건을 더 걸어야함. 지금은 갔던데 가면 그뒤 탐색을 무시해서 탐색을 안하는 공간이 생김. 
			{
				return;
			}
		_MessagePool->ReserveMessage(tile, "Show");
	}

	// 바닥인 경우
	if (tile->GetAttribute() == ObjNone)
	{
		for (int i = 0; i < 4; i++)
		{
			POINT tempIndex;
			tempIndex.x = index.x + proveX[i];
			tempIndex.y = index.y + proveY[i];
			// 중복 처리 해야함 방향? 조절 할수있다던데 
			
			FloodFill(tempIndex, sight - 1);
		}

	}
	if (_GameWorld->GetTileManager()->Tile(index.x, index.y)->GetAttribute() == ObjDestructable)
	{
		
	}

}

void Player::Sight()
{
	for (size_t t = 0; t < shownTiles.size(); t++)
		_MessagePool->ReserveMessage(shownTiles[t], "Hide");
	shownTiles.clear();

	FloodFill(myIndex, 10);
}


void PlayerIdle::Enter()
{

}

void PlayerIdle::BeatExcute()
{
	// 여기서 타일을 검사한 뒤에 결과 값에 따라 move,attact,idle 중 하나로 이동 하면 됨 
	// 무기 장착 하거나 했을때 상태변화를 어떻게 줘야 할까? >> 무기는 

	me->myIndex = PosToIndex(me->position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
	vector<GameObject*> tempArr; 
	_GameWorld->GetGameData()->PosRedefinition(me->myIndex);

	

	if (KeyCode->Down(VK_LEFT))
	{
		me->frameY = 1;
		me->playerDirection = PlayerLeft;


		// 갈 곳의 인덱스가 맵밖이 아니고 , 장애물이 아닌경우 > > > 움직여라!
		if (me->myIndex.x - 1 >= 0) {
			// _GameWorld->GetTileManager .... 같이 외부에서 참조하는 애를 여러번 호출 하기 싫으면 
			// temp 같은 변수 선언해서 거기에 담아 놓고 쓰면 한번만 호출하게 되서 훨씬 빠르고, if 밖으로 나가게되면 자연스럽게 삭제된다.
			TileNode* leftTilePos;
			leftTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y);

			if (leftTilePos->GetAttribute() == ObjNone) // 지나갈수있는 타일이면 
			{
				// 여기서 타일 검사 해서 에너민지 봐야할거같은데
				// ObjectMonster
				tempArr = leftTilePos->GetObjects(ObjectMonster);
				if (tempArr.size() > 0)
				{
					me->ChangeState("Attack");
					return;
				}

				me->startTime = 0; // 시작 시간 초기화
				me->startPos = me->position; // 시작 위치 

				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectPlayer, me); // 원래 있던 타일 삭제하고
				leftTilePos->AddObject(ObjectPlayer, me); // 플레이어를 타일에 등록한다.

				me->destination.x = leftTilePos->GetPos().x; // 목적지

				me->jumpPower = 4.5f;
				me->gravity = 0.6f;

				me->ChangeState("Move");
			}

			// 이게 이동 위에 있으면 부순뒤 - 이동이 됨으로 전진하면서 부숨 ( 창 )
			if (leftTilePos->GetAttribute() == ObjDestructable)
			{
				// 해당 오브젝트 찾아서 조지는듯 
				tempArr = leftTilePos->GetObjects(ObjectWall);
				for (int i = 0; i < tempArr.size(); ++i)
				{
					_MessagePool->ReserveMessage(tempArr[i], "ShovelHit");
				}
			}
		}

	}
	else if (KeyCode->Down(VK_RIGHT))
	{
		me->frameY = 0;
		me->playerDirection = PlayerRight;

		if (me->myIndex.x + 1 < TileManager::mapSize.x)
		{
			TileNode* rightTilePos;
			rightTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y);


			if (rightTilePos->GetAttribute() == ObjNone)
			{
				tempArr = rightTilePos->GetObjects(ObjectMonster);
				if (tempArr.size() > 0)
				{
					me->ChangeState("Attack");
					return;
				}

				me->startTime = 0;
				me->startPos = me->position;

				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectPlayer, me);
				rightTilePos->AddObject(ObjectPlayer, me);

				me->destination.x = rightTilePos->GetPos().x;

				me->jumpPower = 4.5f;
				me->gravity = 0.6f;

				me->ChangeState("Move");
			}
			if (rightTilePos->GetAttribute() == ObjDestructable)
			{
				tempArr = rightTilePos->GetObjects(ObjectWall);
				for (int i = 0; i < tempArr.size(); ++i)
				{
					_MessagePool->ReserveMessage(tempArr[i], "ShovelHit");
				}
			}
		}
	}
	else if (KeyCode->Down(VK_UP))
	{
		me->playerDirection = PlayerUp;

		if (me->myIndex.y - 1 >= 0)
		{
			TileNode* upTilePos;
			upTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y - 1);

			if (upTilePos->GetAttribute() == ObjNone)
			{
				tempArr = upTilePos->GetObjects(ObjectMonster);
			if (tempArr.size() > 0) 
			{
				me->ChangeState("Attack");
				return;
			}

				me->startTime = 0;
				me->startPos = me->position;

				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectPlayer, me);
				upTilePos->AddObject(ObjectPlayer, me);

				me->destination.y = upTilePos->GetPos().y;

				me->jumpPower = 9.5f;
				me->gravity = 0.6f;
				me->ChangeState("Move");
			}

			if (upTilePos->GetAttribute() == ObjDestructable)
			{
				 tempArr = upTilePos->GetObjects(ObjectWall);
				for (int i = 0; i < tempArr.size(); ++i)
				{
					_MessagePool->ReserveMessage(tempArr[i], "ShovelHit");
				}
			}
		}
	}
	else if (KeyCode->Down(VK_DOWN))
	{
		me->playerDirection = PlayerDown;

		if (me->myIndex.y + 1 < TileManager::mapSize.y)
		{
			TileNode* downTilePos;
			downTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y + 1);


			if (downTilePos->GetAttribute() == ObjNone)
			{
				tempArr = downTilePos->GetObjects(ObjectMonster);
				if (tempArr.size() > 0) 
				{
					me->ChangeState("Attack");
					return;
				}

				me->startTime = 0;
				me->startPos = me->position;

				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectPlayer, me);
				downTilePos->AddObject(ObjectPlayer, me);

				me->destination.y = downTilePos->GetPos().y;

				me->jumpPower = 0.6f;
				me->gravity = 0.6f;
				me->ChangeState("Move");
			}

			if (downTilePos->GetAttribute() == ObjDestructable)
			{
				 tempArr = downTilePos->GetObjects(ObjectWall);
				for (int i = 0; i < tempArr.size(); ++i)
				{
					_MessagePool->ReserveMessage(tempArr[i], "ShovelHit");
				}
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

	me->startTime += Time::Tick()*1.5f;								// 0으로 초기화한 startTime에 tick을 더해라 
	float factor = me->startTime / 0.25f;							// lerp 함수 안에 넣을 factor , 전체 시간분에 목표시간

	me->position = Math::Lerp(me->startPos, me->destination, factor);	// Lerp함수를 이용하여 목표 거리를(destination-startPos)  일정 비율(factor)로 이동

	// 점프 
	if (factor <= 1.0f)
	{
		me->imagePos.y -= me->jumpPower;
		me->jumpPower -= me->gravity;
	}

	if (factor >= 1.0f)										//비울(factor) >= 1  >>>> 목표지점까지 가는데 걸린 시간이 목표한 시간과 같거나 크다 = 도착했다
	{
		me->imagePos.y = me->destination.y;
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


	// 아이템 범위 받으면 좀더 예쁘게 만들 수 있지 않을까??
	if (me->playerDirection == PlayerLeft)
	{
		vector<GameObject*> tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetObjects(ObjectMonster);
		for (int i = 0; i < tempArr.size(); ++i)
		{
			_MessagePool->ReserveMessage(tempArr[i], "BatHit");
		}
	}
	if (me->playerDirection == PlayerRight)
	{
		vector<GameObject*> tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y)->GetObjects(ObjectMonster);
		for (int i = 0; i < tempArr.size(); ++i)
		{
			_MessagePool->ReserveMessage(tempArr[i], "BatHit");
		}
	}
	if (me->playerDirection == PlayerUp)
	{
		vector<GameObject*> tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y-1)->GetObjects(ObjectMonster);

		for (int i = 0; i < tempArr.size(); ++i)
		{
			_MessagePool->ReserveMessage(tempArr[i], "BatHit");
		}
	}
	if (me->playerDirection == PlayerDown)
	{
		vector<GameObject*> tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y+1)->GetObjects(ObjectMonster);

		for (int i = 0; i < tempArr.size(); ++i)
		{
			_MessagePool->ReserveMessage(tempArr[i], "BatHit");
		}
	}

	CAMERA->Shake(); // 몬스터 피격시가 아니라 여기서 해주는게 나을거같대 
	me->ChangeState("Idle");
}

void PlayerAttack::Exit()
{
}
