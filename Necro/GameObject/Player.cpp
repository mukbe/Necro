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
	
	
	// �̹��� ��ġ ���� (-20);
	// �̹����� ���� ��ų���� ������ _���� ���� �ٸ��� ��ߵ� . >> ����� �ε��� �����ϰ� �׷��� �׳� ������ �����ִ°� ���� ����.. 
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
	// ������Ʈ �ϴ� ���¸� ������ �Է��� ���¸� �����Ѵ�.

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
	// ���⼭ Ÿ���� �˻��� �ڿ� ��� ���� ���� move,attact,idle �� �ϳ��� �̵� �ϸ� �� 
	// ���� ���� �ϰų� ������ ���º�ȭ�� ��� ��� �ұ�? >> ����� 

	me->myIndex = PosToIndex(me->position, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());


	if (KeyCode->Down(VK_LEFT))
	{
		me->head = "PlayerHeadLeft";
		me->body = "PlayerBodyLeft";


		// ���� �𸣰����� �� ������ �ΰ��� &&�� ��� ���� ������ �ε����� �������ܼ� ���� 
		// �� ���� �ε����� �ʹ��� �ƴϰ� , ��ֹ��� �ƴѰ�� > > > ��������!
		if (me->myIndex.x - 1 >= 0) {
			// _GameWorld->GetTileManager .... ���� �ܺο��� �����ϴ� �ָ� ������ ȣ�� �ϱ� ������ 
			// temp ���� ���� �����ؼ� �ű⿡ ��� ���� ���� �ѹ��� ȣ���ϰ� �Ǽ� �ξ� ������, if ������ �����ԵǸ� �ڿ������� �����ȴ�.
			TileNode* leftTilePos;
			leftTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y);

			if (leftTilePos->GetAttribute() != ObjStatic)
			{
				me->startTime = 0;																					  // ���� �ð� �ʱ�ȭ
				me->startPos = me->position;																			  // ���� ��ġ 
				//me->destination.x = me->_pos.x - _GameWorld->GetTileManager()->GetTileSize().x; >> �̷��� ����� �̰��������� ���� ����. 
				me->destination.x = leftTilePos->GetPos().x; // ������
				me->jumpPos = D3DXVECTOR2(me->destination.x + 26, me->startPos.y - 40); 

				me->ChangeState("Move");
			}
		}

	}
	else if (KeyCode->Down(VK_RIGHT))
	{
		me->head = "PlayerHeadRight";
		me->body = "PlayerBodyRight";

		// mapSize �ָ� ���ư� �ʿ� ���� �ٷ� ��ȯ�Ҽ������� ��ȯ�ؼ� �ϴ°� ���� . 
		if (me->myIndex.x + 1 < TileManager::mapSize.x)
		{
			TileNode* rightTilePos;
			rightTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y);

			if (rightTilePos->GetAttribute() != ObjStatic)
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

			if (upTilePos->GetAttribute() != ObjStatic)
			{
				me->startTime = 0;
				me->startPos = me->position;
				me->destination.y = upTilePos->GetPos().y;
				me->jumpPos = D3DXVECTOR2(me->destination.x , me->startPos.y - 75); 

				me->ChangeState("Move");
			}
		}
	}
	else if (KeyCode->Down(VK_DOWN))
	{
		if (me->myIndex.y + 1 < TileManager::mapSize.y)
		{
			TileNode* downTilePos;
			downTilePos = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y + 1);

			if (downTilePos->GetAttribute() != ObjStatic)
			{
				me->startTime = 0;
				me->startPos = me->position;
				me->destination.y = downTilePos->GetPos().y;
				me->jumpPos = D3DXVECTOR2(me->destination.x, me->startPos.y - 10);

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
	// �۵� ���� �ð� / ��ǥ �ð� ==1 �� �ɶ� ���� (= ��ǥ �ð�����) �۵��ض�
	float factor = me->startTime / 0.25f;							// lerp �Լ� �ȿ� ���� factor , ��ü �ð��п� ��ǥ�ð�

	me->startTime += Time::Tick();									// 0���� �ʱ�ȭ�� startTime�� tick�� ���ض� 

	me->position = Math::Lerp(me->startPos, me->destination, factor);	// Lerp�Լ��� �̿��Ͽ� ��ǥ �Ÿ���(destination-startPos)  ���� ����(factor)�� �̵�

	// y�� ������ ���� �ϴ���.. 
	// Lerp �Ⱦ��°� ������. �̲��������� �����̰Եȴ�. �߷� �־ �����ϴ°�ó�� ����°� ������.. 
	// ���� ���� �Ѵ� �Ӥ���.. 
	if (factor <= 0.55f)												
	{
		me->imagePos = Math::Lerp(me->startPos, me->jumpPos, factor);
	}
	if (factor > 0.55f && factor < 1.0f)
	{
		me->imagePos = Math::Lerp(me->startPos, me->destination, factor);
	}




	if (factor >= 1.0f)												//���(factor) >= 1  >>>> ��ǥ�������� ���µ� �ɸ� �ð��� ��ǥ�� �ð��� ���ų� ũ�� = �����ߴ�
	{
		//me->_pos = me->destination;								// ��ġ ���� �Ҳ��� ��ġ���� 
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
