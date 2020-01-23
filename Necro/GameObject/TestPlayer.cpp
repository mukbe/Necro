#include "stdafx.h"
#include "TestPlayer.h"






TestPlayer::TestPlayer(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	moveType = MoveType_Control;
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void TestPlayer::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void TestPlayer::ControlUpdate()
{
	if (Keyboard::Get()->Down(VK_RIGHT))
	{
		position.x += 30.f;
		rc += D3DXVECTOR2(30,0);
	}
	else if (Keyboard::Get()->Down(VK_LEFT))
	{
		position.x -= 30.f;
		rc += D3DXVECTOR2(-30, 0);
	}
	else if (Keyboard::Get()->Down(VK_UP))
	{
		position.y -= 30.f;
		rc += D3DXVECTOR2(0, -30);
	}
	else if (Keyboard::Get()->Down(VK_DOWN))
	{
		position.y += 30.f;
		rc += D3DXVECTOR2(0, 30);
	}

}

void TestPlayer::Update(float tick)
{
}

void TestPlayer::Render()
{
	p2DRenderer->FillRectangle(rc, nullptr);
}

