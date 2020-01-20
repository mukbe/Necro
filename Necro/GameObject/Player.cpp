#include "stdafx.h"
#include "Player.h"
#include "TileHelper.h"
#include "TileNode.h"
#include "TileManager.h"



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

	interver = 0;
	head = "PlayerHeadRight";
	body = "PlayerBodyRight";
	
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
}

void Player::Release()
{
	GameObject::Release();
}

void Player::PreUpdate()
{

}

void Player::Update(float tick)
{
	if (bActive == false) return;

	GameObject::Update(tick);

	rc = FloatRect(position, 100, 100, Pivot::CENTER);


	currentState->Excute();
	
	interver += tick * 4;

	if (interver > 1.f) {
		frameX++;
		interver = 0;
	}
	if (frameX > 2) 
	{
		frameX = 0;
	}
}


void Player::Render()
{
	if (bActive == false) return;
	
	_ImageManager->FindTexture(body)->FrameRender(FloatRect(_pos, _size, Pivot::CENTER), nullptr, frameX, frameY);
	_ImageManager->FindTexture(head)->FrameRender(FloatRect(_pos, _size, Pivot::CENTER), nullptr, frameX, frameY);

	//_ImageManager->FindTexture(head)->FrameRender(rc, &this->transform, frameX, frameY);
	
	// 우리애 어디있지
	wstring str;
	str += L"pos.x : " + to_wstring(destination.x).substr(0, 6);
	str += L"pos.y : " + to_wstring(destination.y).substr(0, 6);
	p2DRenderer->DrawText2D(WinSizeX -600,200, str, 20);


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
	// 여기서 타일을 검사한 뒤에 결과 값에 따라 move,attact,idle 중 하나로 이동 하면 될거같음 
	// 타일 사이즈 26.f ? 정도 
	
	if (KeyCode->Down(VK_LEFT))
	{
		me-> head = "PlayerHeadLeft";
		me-> body = "PlayerBodyLeft";
		me->ChangeState("Move");
	}
	else if (KeyCode->Down(VK_RIGHT))
	{
		me->head = "PlayerHeadRight";
		me->body = "PlayerBodyRight";
		me->ChangeState("Move");
	}
	else if (KeyCode->Down(VK_UP))
	{
		me->ChangeState("Move");
	}
	else if (KeyCode->Down(VK_DOWN))
	{
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
	float speed = Time::Tick() * 100;
	
	//transform;
	// 타일 중점으로 이동 하게 해 -> 지금은 그냥 절대값으로 이동 하게 했음 ㅇㅅㅇ. 
	// 이거 다운 누르면 바로 가니까 알아서 해라..

	if (KeyCode->Down(VK_LEFT))
	{
		PlayerState == MOVELEFT;
		me->destination.x = me->_pos.x - 50; // 목표지 
		//me->_pos.x += 10 * Time::Tick();
	}
	else if (KeyCode->Down(VK_RIGHT))
	{
		PlayerState == MOVERIGHT;
		me->destination.x = me->_pos.x + 50; // 목표지 
		
	}
	else if (KeyCode->Press(VK_UP))
	{
		PlayerState == MOVEUP;
		//me->_pos.y -= speed;
		//me->_pos.y -= 50;
	}
	else if (KeyCode->Press(VK_DOWN))
	{
		PlayerState == MOVEDOWN;
		me->_pos.y += 50;
	}

	

	if (PlayerState == MOVELEFT)
	{
		if (me->destination.x < me->_pos.x) {
			me->_pos.x -= 50;
		}
		else {
			speed = 0;
			float delta = me->destination.x - me->_pos.x;
			me->_pos.x += delta;
			me->ChangeState("Idle");
		}

	}
	if (PlayerState == MOVERIGHT)
	{
		if (me->destination.x > me->_pos.x) {
			me->_pos.x += 50;
		}
		else {
			speed = 0;
			float delta = me->destination.x - me->_pos.x;
			me->_pos.x += delta;
			me->ChangeState("Idle");
		}

	}
	if (PlayerState == MOVEUP)
	{

	}
	if (PlayerState == MOVEDOWN)
	{

	}
	

	//if (KeyCode->Up(VK_LEFT))
	//{
	//	me->ChangeState("Idle");
	//}
	//else if (KeyCode->Up(VK_RIGHT))
	//{
	//	me->ChangeState("Idle");
	//}
	//else if (KeyCode->Up(VK_UP))
	//{
	//	me->ChangeState("Idle");
	//}
	//else if (KeyCode->Up(VK_DOWN))
	//{
	//	me->ChangeState("Idle");
	//}
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
