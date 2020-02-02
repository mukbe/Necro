#include "stdafx.h"
#include "Player.h"
#include "./GameObject/Map/TileNode.h"
#include "./GameObject/Item/ItemBase.h"



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
	isSight = false;
	isAttack = false;
	AddCallback("PlayerHit", [&](TagMessage msg) {

		CAMERA->Shake();
		EFFECTS->Fire("Playerhit", D3DXVECTOR2(position.x, position.y-20) , D3DXVECTOR2(52,52));
		SOUNDMANAGER->Play("playerHurt", 0.6f);

		// 피를 깍아준다. >> 애너미에서 게임 데이터로 쏴야 하지않나? 
		// 다하고 함수로 빼주기 

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

	wstring path = ResourcePath + L"Sound/playerHurt.ogg";
	SOUNDMANAGER->AddSound("playerHurt", String::WStringToString(path), true, false);
	attackRange = _GameWorld->GetGameData()->GetWeaponData().Range;
	EFFECTS->AddEffect("Playerhit", "Playerhit");



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
	
	if (isSight)Sight();
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

//vector<vector<int> > GetDistance(int x, int y, vector<vector<int> > cells)
//{
//	const int INF = 0x7FFFFF;
//	vector<vector<int> > distance(cells.size());
//
//	for (int i = 0; i < distance.size(); i++)
//		distance[i].assign(cells[i].size(), INF);  // size만큼 INF 를 할당한다
//	
//	queue<pair<int, int> > q;
//
//	q.push(make_pair(x, y));
//	distance[x][y] = 0;
//
//	while (!q.empty())
//	{
//		pair<int, int> curPoint = q.front();
//		q.pop();
//		int curDistance = distance[curPoint.first][curPoint.second];
//		for (int i = -1; i <= 1; i++)
//			for (int j = -1; j <= 1; j++)
//			{
//				if ((i + j) % 2 == 0) continue;
//				pair<int, int> nextPoint(curPoint.first + i, curPoint.second + j);
//				if (nextPoint.first >= 0 && nextPoint.first < cells.size()
//					&& nextPoint.second >= 0 && nextPoint.second < cells[nextPoint.first].size()
//					//&& cells[nextPoint.first][nextPoint.second] != BARRIER
//					&& distance[nextPoint.first][nextPoint.second] > curDistance + 1)
//				{
//					distance[nextPoint.first][nextPoint.second] = curDistance + 1;
//					q.push(nextPoint);
//				}
//			}
//	}
//	return distance;
//}

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
		//if (tile->IsShow()) // 조건을 더 걸어야함. 지금은 갔던데 가면 그뒤 탐색을 무시해서 탐색을 안하는 공간이 생김. 
		//{
		//	return;
		//}
		_MessagePool->ReserveMessage(tile, "Show");
	}
}

void Player::Sight()
{
	for (size_t t = 0; t < shownTiles.size(); t++)
		_MessagePool->ReserveMessage(shownTiles[t], "Hide");
	shownTiles.clear();

	FloodFill(myIndex, 5);
}


void Player::Shovel(TileNode* TilePos, vector<GameObject*> temp)
{
	if (TilePos->GetAttribute() == ObjDestructable)
	{
		// 해당 오브젝트 찾아서 조지는듯 
		temp = TilePos->GetObjects(ObjectWall);
		for (int i = 0; i < temp.size(); ++i)
		{
			_MessagePool->ReserveMessage(temp[i], "ShovelHit");
		}
	}
}

void Player::InitToMove(TileNode * TilePos, float JumpPower, float Gravity)
{
	startTime = 0; // 시작 시간 초기화
	startPos = position; // 시작 위치 
	_GameWorld->GetTileManager()->Tile(myIndex.x, myIndex.y)->DeleteObject(ObjectPlayer, this); // 원래 있던 타일 삭제하고
	TilePos->AddObject(ObjectPlayer, this); // 플레이어를 타일에 등록한다.
	destination = TilePos->GetPos(); // 목적지
	jumpPower = JumpPower;
	gravity = Gravity;
}

void Player::PosIdentify(int direction)
{
	vector<GameObject*> tempArr;
	attackRange = _GameWorld->GetGameData()->GetWeaponData().Range;
	myIndex = PosToIndex(position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
	
	vAttackRange.clear();

	if (attackRange.y == 0)
	{
		for (int i = 1; i < attackRange.x + 1;i++)
		{
			int proveX[4] = { -1,1,0,0 };
			int proveY[4] = { 0,0,-1, 1 };
			// proveX proveY변수는 대입해서 넣게 
			POINT sour;
			sour.x = myIndex.x +i * proveX[direction];
			sour.y = myIndex.y +i * proveY[direction];
			tempArr = _GameWorld->GetTileManager()->Tile(sour)->GetObjects(ObjectMonster);
			// 여기서 백터에 넣어 
			vAttackRange.push_back(sour);
			if (tempArr.size() > 0)
			{
				ChangeState("Attack");
				isAttack = true;
				return;
			}
		}
	}
	if (attackRange.y > 0)
	{

		for (int i = -1; i < attackRange.y - 1;i++)
		{
			POINT sour;
			// 0 1 2 여기다 -1만 하면 범윈데 
			int proveX[4] = { -1,1,0,0 };
			int proveY[4] = { 0,0,-1, 1 };
		
			if (direction == 0)
			{
				sour.x = myIndex.x -1;
				sour.y = myIndex.x + i;
				tempArr = _GameWorld->GetTileManager()->Tile(sour)->GetObjects(ObjectMonster);
				// 여기서 백터에 넣어 
				vAttackRange.push_back(sour);
				if (tempArr.size() > 0)
				{
					ChangeState("Attack");
					isAttack = true;
					return;
				}

			}
			if (direction == 1)
			{
				
				sour.x = myIndex.x +1;
				sour.y = myIndex.y +i;

				tempArr = _GameWorld->GetTileManager()->Tile(sour)->GetObjects(ObjectMonster);
				// 여기서 백터에 넣어 
				vAttackRange.push_back(sour);
				if (tempArr.size() > 0)
				{
					ChangeState("Attack");
					isAttack = true;
					return;
				}

			}
			if (direction == 2)
			{
				sour.x = myIndex.x + i;
				sour.y = myIndex.y -1;
				tempArr = _GameWorld->GetTileManager()->Tile(sour)->GetObjects(ObjectMonster);
				// 여기서 백터에 넣어 
				vAttackRange.push_back(sour);
				if (tempArr.size() > 0)
				{
					ChangeState("Attack");
					isAttack = true;
					return;
				}

			}
			if (direction == 3)
			{
				sour.x = myIndex.x+ i;
				sour.y = myIndex.y + 1;
				tempArr = _GameWorld->GetTileManager()->Tile(sour)->GetObjects(ObjectMonster);
				// 여기서 백터에 넣어 
				vAttackRange.push_back(sour);
				if (tempArr.size() > 0)
				{
					ChangeState("Attack");
					isAttack = true;
					return;
				}

			}

			tempArr = _GameWorld->GetTileManager()->Tile(sour)->GetObjects(ObjectMonster);

		}
	}
}

void PlayerIdle::Enter()
{

}

void PlayerIdle::BeatExcute()
{
	// 여기서 타일을 검사한 뒤에 결과 값에 따라 move,attact,idle 중 하나로 이동 하면 됨 
	// 무기 장착 하거나 했을때 상태변화를 어떻게 줘야 할까? >> 무기는 

	me->myIndex = PosToIndex(me->position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
	ItemBase* item;
	vector<GameObject*> tempArr;
	_GameWorld->GetGameData()->PosRedefinition(me->myIndex);


	if (KeyCode->Down(VK_LEFT))
	{
		me->frameY = 1;
		me->playerDirection = PlayerLeft;


		// 갈 곳의 인덱스가 맵밖이 아니고 , 장애물이 아닌경우 > > > 움직여라!
		if (me->myIndex.x - 1 >= 0) {

			TileNode* leftTilePos;
			leftTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y);

			if (leftTilePos->GetAttribute() == ObjNone) // 지나갈수있는 타일이면 
			{
				// 몬스터 확인
				//tempArr.clear();

				//tempArr = leftTilePos->GetObjects(ObjectMonster);
				//if (tempArr.size() > 0)
				//{
				//	me->ChangeState("Attack");
				//	return;
				//}
				
				me->PosIdentify(0);
				if (me->isAttack ==true) return;

				// 아이템 확인 
				tempArr.clear();
				tempArr = leftTilePos->GetObjects(ObjectItem);
				if (tempArr.size() > 0)
				{
				item = static_cast<ItemBase *>(tempArr[0]);

					if (item->CanBuyItem())
					{

						for (int i = 0; i < tempArr.size(); ++i)
						{
							_MessagePool->ReserveMessage(tempArr[i], "EatItem");
						}

					}
					if (!item->CanBuyItem())return; // return이 있는 애들은 함수로 정리X
				}


				me->InitToMove(leftTilePos, 4.5f, 0.6f);


				me->ChangeState("Move");
			}

			me->Shovel(leftTilePos, tempArr);

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

				me->PosIdentify(1);
				if (me->isAttack) return;


				tempArr.clear();
				tempArr = rightTilePos->GetObjects(ObjectItem);
				if (tempArr.size() > 0)
				{

					item = static_cast<ItemBase *>(tempArr[0]);

					if (item->CanBuyItem())
					{

						for (int i = 0; i < tempArr.size(); ++i)
						{
							_MessagePool->ReserveMessage(tempArr[i], "EatItem");
						}

					}
					if (!item->CanBuyItem())return; // return이 있는 애들은 함수로 정리X
				}

				me->InitToMove(rightTilePos, 4.5f, 0.6f);

				me->ChangeState("Move");
			}

			me->Shovel(rightTilePos, tempArr);

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

				
				me->PosIdentify(2);
				if (me->isAttack) return;

				tempArr.clear();
				tempArr = upTilePos->GetObjects(ObjectItem);
				if (tempArr.size() > 0)
				{

					item = static_cast<ItemBase *>(tempArr[0]);

					if (item->CanBuyItem())
					{

						for (int i = 0; i < tempArr.size(); ++i)
						{
							_MessagePool->ReserveMessage(tempArr[i], "EatItem");
						}

					}
					if (!item->CanBuyItem())return; // return이 있는 애들은 함수로 정리X
				}
				me->InitToMove(upTilePos, 9.5f, 0.6f);

				me->ChangeState("Move");
			}

			me->Shovel(upTilePos, tempArr);

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

				me->PosIdentify(3);
				if (me->isAttack) return;

				tempArr.clear();
				tempArr = downTilePos->GetObjects(ObjectItem);
				if (tempArr.size() > 0)
				{

					item = static_cast<ItemBase *>(tempArr[0]);

					if (item->CanBuyItem())
					{

						for (int i = 0; i < tempArr.size(); ++i)
						{
							_MessagePool->ReserveMessage(tempArr[i], "EatItem");
						}

					}
					if (!item->CanBuyItem())return; // return이 있는 애들은 함수로 정리X
				}

				me->InitToMove(downTilePos, 0.6f, 0.6f);

				me->ChangeState("Move");
			}

			me->Shovel(downTilePos, tempArr);

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
	// 여기는 어택만 하셔야 하구욘 
	me->EffactName = _GameWorld->GetGameData()->GetWeaponData().EffactImagekey;
	//me->vAttackRange 
	vector<GameObject*> tempArr;
	for (int i = 0; i < me->vAttackRange.size(); i++)
	{
		tempArr = _GameWorld->GetTileManager()->Tile(me->vAttackRange[i])->GetObjects(ObjectMonster);

		for (int i = 0; i < tempArr.size(); ++i)
		{
			_MessagePool->ReserveMessage(tempArr[i], "MonsterHit");
			CAMERA->Shake(); // 몬스터 피격시가 아니라 여기서 해주는게 나을거같대 
			me->ChangeState("Idle");
			me->isAttack = false;
			return;
		}
	}


	//if (me->playerDirection == PlayerLeft)
	//{
	//	vector<GameObject*> tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetObjects(ObjectMonster);
	//	for (int i = 0; i < tempArr.size(); ++i)
	//	{
	//		_MessagePool->ReserveMessage(tempArr[i], "MonsterHit");

	//	}
	//}
	//if (me->playerDirection == PlayerRight)
	//{
	//	vector<GameObject*> tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y)->GetObjects(ObjectMonster);
	//	for (int i = 0; i < tempArr.size(); ++i)
	//	{
	//		_MessagePool->ReserveMessage(tempArr[i], "MonsterHit");
	//	}
	//}
	//if (me->playerDirection == PlayerUp)
	//{
	//	vector<GameObject*> tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y - 1)->GetObjects(ObjectMonster);

	//	for (int i = 0; i < tempArr.size(); ++i)
	//	{
	//		_MessagePool->ReserveMessage(tempArr[i], "MonsterHit");
	//	}
	//}
	//if (me->playerDirection == PlayerDown)
	//{
	//	vector<GameObject*> tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y + 1)->GetObjects(ObjectMonster);

	//	for (int i = 0; i < tempArr.size(); ++i)
	//	{
	//		_MessagePool->ReserveMessage(tempArr[i], "MonsterHit");
	//	}
	//}


}

void PlayerAttack::Exit()
{
}

