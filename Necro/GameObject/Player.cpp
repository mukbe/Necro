#include "stdafx.h"
#include "Player.h"
#include "TileHelper.h"
#include "TileNode.h"



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

	currentState->Excute();
	
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
	
	_ImageManager->FindTexture(body)->FrameRender(FloatRect(_pos, _size, Pivot::CENTER), nullptr, frameX, frameY);
	_ImageManager->FindTexture(head)->FrameRender(FloatRect(_pos, _size, Pivot::CENTER), nullptr, frameX, frameY);

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

void PlayerIdle::Excute()
{
	// ���⼭ Ÿ���� �˻��� �ڿ� ��� ���� ���� move,attact,idle �� �ϳ��� �̵� �ϸ� �� 
	// ���� ���� �ϰų� ������ ���º�ȭ�� ��� ��� �ұ�? >> ����� 
	//TileNode* tileNode;
	POINT tileNum;
	tileNum.x = (me->_pos.x - 26) / 52;
	tileNum.y = (me->_pos.y - 26) / 52;
	me->tileNode->SetIndex(tileNum);


	if (KeyCode->Down(VK_LEFT))
	{
		me-> head = "PlayerHeadLeft";
		me-> body = "PlayerBodyLeft";

		me->startTime = 0;							// ���� �ð� �ʱ�ȭ
		me->startPos = me->_pos;					// ���� ��ġ 
		me->destination.x = me->_pos.x -52;			// ������

		me->tileNode->GetIndex();

		if (me->tilemanger->Tile({ me->tileNode->GetIndex().x - 1, me->tileNode->GetIndex().y})->GetAttribute() != ObjStatic)
		{
			me->ChangeState("Move");
		}
	}
	else if (KeyCode->Down(VK_RIGHT))
	{
		me->head = "PlayerHeadRight";
		me->body = "PlayerBodyRight";

		me->startTime = 0;
		me->startPos = me->_pos;
		me->destination.x = me->_pos.x + 52; 

		if (me->tilemanger->Tile({ me->tileNode->GetIndex().x + 1, me->tileNode->GetIndex().y })->GetAttribute() != ObjStatic)
		{
			me->ChangeState("Move");
		}
	}
	else if (KeyCode->Down(VK_UP))
	{
		me->startTime = 0;
		me->startPos = me->_pos;
		me->destination.y = me->_pos.y - 52; 
		if (me->tilemanger->Tile({ me->tileNode->GetIndex().x , me->tileNode->GetIndex().y-1 })->GetAttribute() != ObjStatic)
		{
			me->ChangeState("Move");
		}
	}
	else if (KeyCode->Down(VK_DOWN))
	{
		me->startTime = 0;
		me->startPos = me->_pos;
		me->destination.y = me->_pos.y + 52; 

		if (me->tilemanger->Tile({ me->tileNode->GetIndex().x , me->tileNode->GetIndex().y +1})->GetAttribute() != ObjStatic)
		{
			me->ChangeState("Move");
		}
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

void PlayerAttack::Excute()
{
}

void PlayerAttack::Exit()
{
}
