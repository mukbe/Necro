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
	// �̹��� ��ġ ���� (-20);
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

	me->myIndex = PosToIndex(me->_pos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());


	if (KeyCode->Down(VK_LEFT))
	{
		me->head = "PlayerHeadLeft";
		me->body = "PlayerBodyLeft";


		// ���� �𸣰����� �� ������ �ΰ��� &&�� ��� ���� ������ �ε����� �������ܼ� ���� 
		// �� ���� �ε����� �ʹ��� �ƴϰ� , ��ֹ��� �ƴѰ�� > > > ��������!
		if (me->myIndex.x - 1 >= 0) {
			if (_GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetAttribute() != ObjStatic)
			{
				me->startTime = 0;																					  // ���� �ð� �ʱ�ȭ
				me->startPos = me->_pos;																			  // ���� ��ġ 
				//me->destination.x = me->_pos.x - _GameWorld->GetTileManager()->GetTileSize().x; >> �̷��� ����� �̰��������� ���� ����. 
				me->destination.x = _GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetPos().x; // ������

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
	// �۵� ���� �ð� / ��ǥ �ð� ==1 �� �ɶ� ���� (= ��ǥ �ð�����) �۵��ض�
	float factor = me->startTime / 0.25f;							// lerp �Լ� �ȿ� ���� factor , ��ü �ð��п� ��ǥ�ð�

	me->startTime += Time::Tick();									// 0���� �ʱ�ȭ�� startTime�� tick�� ���ض� 

	me->_pos = Math::Lerp(me->startPos, me->destination, factor);	// Lerp�Լ��� �̿��Ͽ� ��ǥ �Ÿ���(destination-startPos)  ���� ����(factor)�� �̵�

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
