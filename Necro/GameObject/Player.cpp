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
	myIndex = PosToIndex(position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
	_GameWorld->GetTileManager()->Tile(myIndex.x, myIndex.y)->AddObject(ObjectPlayer, this); // Ÿ�Ͽ� ���
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
		// ����Ʈ�� �߰�. > ���߿� �߰��� �ش�
		// �Ǹ� ����ش�. > ���� ���� �ȵ�����. 
		// �ǰ��� ư��. 

	});
	// �Ǹ� ������Ʈ���� ��� Ȯ���� �ְ� �ǰ� 0�� �Ǹ� ĳ���� ���δ����� �׾��ٰ� ���޴���? �������� �Ѱܾ� �ҵ� 

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
	// �̹��� ��ġ ���� (-20);
	// �̹����� ���� ��ų���� ������ _���� ���� �ٸ��� ��ߵ� . >> ����� �ε��� �����ϰ� �׷��� �׳� ������ �����ִ°� ���� ����.. 
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


void Player::ChangeState(string str)
{
	// ������Ʈ �ϴ� ���¸� ������ �Է��� ���¸� �����Ѵ�.
	if (currentState)
		currentState->Exit();

	currentState = stateList[str];

	if (currentState)
		currentState->Enter();
}

void Player::FloodFill(POINT index, int sight)
{
	// index�� �÷��̾��� �ε����� ���;� ��.  
	vector<GameObject*> temp;

	if (sight <= 0) return;
	int proveX[4] = { 0,0,-1,1 };
	int proveY[4] = { -1,1,0,0 };

	// �ٴ��� ���
	if (_GameWorld->GetTileManager()->Tile(index.x, index.y)->GetAttribute() == ObjNone)
	{
		_MessagePool->ReserveMessage(_GameWorld->GetTileManager()->Tile(index.x, index.y), "Active");

		for (int i = 0; i < 4; i++)
		{
			POINT tempIndex;
			tempIndex.x = index.x + proveX[i];
			tempIndex.y = index.y + proveY[i];
			FloodFill(tempIndex, sight - 1);
		}

	}
	//else
	//{
	//  // �� �� ��� 
	//	if (_GameWorld->GetTileManager()->Tile(index.x, index.y)->GetAttribute() == ObjDestructable)
	//	{
	//		
	//	}
	//}

	//for (int i = 0; i < 4; i++)
	//{
	//	POINT tempIndex;
	//	tempIndex.x = index.x + proveX[i];
	//	tempIndex.y = index.y + proveY[i];

	//	//sight �� 5 �ְ� sight�� ���� ��⸦ �ٸ��� �ش�. 

	//	// Ÿ���� ���϶� 
	//	if (_GameWorld->GetTileManager()->Tile(tempIndex.x, tempIndex.y)->GetAttribute() == ObjDestructable)
	//	{
	//		// �굵 �Ƹ� ó�� �þ� ������ ���°Ÿ� ��ȯ �϶�� �ؾ��� 
	//		FloodFill(tempIndex, sight - 1);
	//		// ���̸� �� ���ְ� 
	//		// �׹������δ� ���̻� ������ �ؾ��ϴµ� 
	//	}
	//	else
	//	{
	//		// Ÿ���� �׳� ���϶� 
	//		if (_GameWorld->GetTileManager()->Tile(index.x, index.y)->GetAttribute() == ObjNone)
	//		{
	//			_MessagePool->ReserveMessage(_GameWorld->GetTileManager()->Tile(tempIndex.x, tempIndex.y), "Active");
	//		}

	//		//// Ÿ���� �����϶�
	//		//temp = _GameWorld->GetTileManager()->Tile(tempIndex.x, tempIndex.y)->GetObjects(ObjectMonster);
	//		//if (temp.size() > 0)
	//		//{
	//		//	// �ֳʹ� ������ �޼��� ���� �� Ű��� 
	//		//	// ó�� �þ� ������ ���°Ÿ� ��ȯ? �϶�� �ؾ���.
	//		//}

	//	}
	// }
}


void PlayerIdle::Enter()
{

}

void PlayerIdle::BeatExcute()
{
	// ���⼭ Ÿ���� �˻��� �ڿ� ��� ���� ���� move,attact,idle �� �ϳ��� �̵� �ϸ� �� 
	// ���� ���� �ϰų� ������ ���º�ȭ�� ��� ��� �ұ�? >> ����� 

	// ��������������������������������������������� ���� �Ұ� �������������������������������������������

	// �������������������������������������������������������������������������������������������������
	// �����Ҷ� init���� ��ġ ��� > �÷��̾ �̵��Ҽ������� ��ϵȰ�(����) ���� > �̵� ���� ��� �ϸ� �ɵ�. 


	me->myIndex = PosToIndex(me->position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
	vector<GameObject*> tempArr; 
	_GameWorld->GetGameData()->PosRedefinition(me->myIndex);

	me->FloodFill(me->myIndex, 5);

	if (KeyCode->Down(VK_LEFT))
	{
		me->frameY = 1;
		me->playerDirection = PlayerLeft;


		// �� ���� �ε����� �ʹ��� �ƴϰ� , ��ֹ��� �ƴѰ�� > > > ��������!
		if (me->myIndex.x - 1 >= 0) {
			// _GameWorld->GetTileManager .... ���� �ܺο��� �����ϴ� �ָ� ������ ȣ�� �ϱ� ������ 
			// temp ���� ���� �����ؼ� �ű⿡ ��� ���� ���� �ѹ��� ȣ���ϰ� �Ǽ� �ξ� ������, if ������ �����ԵǸ� �ڿ������� �����ȴ�.
			TileNode* leftTilePos;
			leftTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y);

			if (leftTilePos->GetAttribute() == ObjNone) // ���������ִ� Ÿ���̸� 
			{
				// ���⼭ Ÿ�� �˻� �ؼ� ���ʹ��� �����ҰŰ�����
				// ObjectMonster
				tempArr = leftTilePos->GetObjects(ObjectMonster);
				if (tempArr.size() > 0)
				{
					me->ChangeState("Attack");
					return;
				}

				me->startTime = 0; // ���� �ð� �ʱ�ȭ
				me->startPos = me->position; // ���� ��ġ 

				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectPlayer, me); // ���� �ִ� Ÿ�� �����ϰ�
				leftTilePos->AddObject(ObjectPlayer, me); // �÷��̾ Ÿ�Ͽ� ����Ѵ�.

				me->destination.x = leftTilePos->GetPos().x; // ������

				me->jumpPower = 4.5f;
				me->gravity = 0.6f;

				me->ChangeState("Move");
			}

			// �̰� �̵� ���� ������ �μ��� - �̵��� ������ �����ϸ鼭 �μ� ( â )
			if (leftTilePos->GetAttribute() == ObjDestructable)
			{
				// �ش� ������Ʈ ã�Ƽ� �����µ� 
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
	// �۵� ���� �ð� / ��ǥ �ð� ==1 �� �ɶ� ���� (= ��ǥ �ð�����) �۵��ض�

	me->startTime += Time::Tick()*1.5f;								// 0���� �ʱ�ȭ�� startTime�� tick�� ���ض� 
	float factor = me->startTime / 0.25f;							// lerp �Լ� �ȿ� ���� factor , ��ü �ð��п� ��ǥ�ð�

	me->position = Math::Lerp(me->startPos, me->destination, factor);	// Lerp�Լ��� �̿��Ͽ� ��ǥ �Ÿ���(destination-startPos)  ���� ����(factor)�� �̵�

	// ���� 
	if (factor <= 1.0f)
	{
		me->imagePos.y -= me->jumpPower;
		me->jumpPower -= me->gravity;
	}

	if (factor >= 1.0f)										//���(factor) >= 1  >>>> ��ǥ�������� ���µ� �ɸ� �ð��� ��ǥ�� �ð��� ���ų� ũ�� = �����ߴ�
	{
		me->imagePos.y = me->destination.y;
		me->position = me->destination;						// ��ġ ���� �Ҳ��� ��ġ���� 
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


	// ������ ���� ������ ���� ���ڰ� ���� �� ���� ������??
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

	CAMERA->Shake(); // ���� �ǰݽð� �ƴ϶� ���⼭ ���ִ°� �����Ű��� 
	me->ChangeState("Idle");
}

void PlayerAttack::Exit()
{
}
