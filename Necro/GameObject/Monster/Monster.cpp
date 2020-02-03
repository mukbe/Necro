#include "stdafx.h"
#include "Monster.h"
#include "./Systems/Manage/TileManager.h""
#include "./GameObject/Map/TileNode.h"


Monster::Monster(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: GameObject(name, pos, size)
{
	currentState = nullptr;

	states.insert(make_pair("Idle", new MonsterStateIdle(this)));
	states.insert(make_pair("Move", new MonsterStateOneStep(this)));
	states.insert(make_pair("Atk", new MonsterStateAtk(this)));
	startTime = 0.f;
	realtime = 0.f;
	//startPos = pos;
	//endPos = { pos.x+52.f, pos.y+52.f };
	//firstmove = false;
	myIndex = { 0,0 };
	//startPos = { 0,0 };
	//mynextIndex = { 0,0 };
	ChangeState("Idle");
	
	
	AddCallback("MonsterHit", [&](TagMessage msg)
	{
		CAMERA->Shake();
		EFFECTS->Fire("Playerhit", D3DXVECTOR2(position.x, position.y - 20), D3DXVECTOR2(52, 52));
		ProcessDestroy();
	});


}

Monster::~Monster()
{
}

void Monster::Init()
{
	GameObject::Init();
	_RenderPool->Request(this, RenderManager::Layer::Object);
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
}

void Monster::Release()
{
	GameObject::Release();
	_RenderPool->Remove(this, RenderManager::Layer::Object);
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}

void Monster::Update(float tick)
{
	if (currentState) // ���� ������ ������Ʈ ���Ѷ�.
		currentState->Update();
}

void Monster::ControlUpdate()
{
	
	monsterBeat--;

	
	//���� �ٸ� ��Ʈ���� �����ϼ� �ְ�
	
	if (monsterBeat == 0) 
	{
		
		
			//ChangeState("Idle");
		myIndex = PosToIndex(this->Transform().GetPos(), _TileMap->GetTileSize(), _TileMap->GetPivotPos());

		if (name.substr(2, 10) == "GreenSlime")
		{
			tempArr = _GameWorld->GetTileManager()->Tile(myIndex.x, myIndex.y)->GetObjects(ObjectPlayer);

			if (tempArr.size() > 0)
			{
				ChangeState("Atk");
			}
			else
			{
				ChangeState("Move");
			}


			monsterBeat = 1;
		}

		if (name.substr(2, 8) == "Skeleton")
		{
			monsterBeat = 2;
		}
		if (name == "Bat")
		{
			tempArr = _GameWorld->GetTileManager()->Tile(mynextIndex.x, mynextIndex.y)->GetObjects(ObjectPlayer);
			

			if (tempArr.size() > 0)
			{
				ChangeState("Atk");
			}
			else
			{
				ChangeState("Move");
			}
			monsterBeat = 2;
		}


		if (name.substr(2, 9) == "BlueSlime")
		{

			tempArr = _GameWorld->GetTileManager()->Tile(myIndex.x, myIndex.y)->GetObjects(ObjectPlayer);

			if (tempArr.size() > 0)
			{
				ChangeState("Atk");
			}
			else
			{
				ChangeState("Move");
			}
			monsterBeat = 2;
		}
		if (name.substr(2, 8) == "Minotaur")
		{
			monsterBeat = 1;
		}

	}






}

void Monster::Render()
{
}

void Monster::ImguiRender()
{

	ImGui::Begin("mon");
	{
		if (name == "Bat")
		{
			ImGui::Text("PosX : %.2f, PosY : %.2f", myIndex.x, myIndex.y);
		}

		

	}
	ImGui::End();



}




//���� ���� �ٲ��ִ� �Լ�~
void Monster::ChangeState(string key)
{
	MonsterStateBase* state = states[key];
	state->Enter();
	currentState = state;
	//aaa = key;
}

void Monster::ProcessDestroy()
{
	life--;
	if (life <= 0)
	{
		//����Ʈ �߰� �ʿ�.


		this->SetActive(false);

		POINT tempIndex = PosToIndex(this->Transform().GetPos(), _TileMap->GetTileSize(), _TileMap->GetPivotPos());
		_GameWorld->GetTileManager()->Tile(tempIndex.x, tempIndex.y)->DeleteObject(ObjectMonster, this);
		//_GameWorld->GetTileManager()->Tile(mynextIndex.x, mynextIndex.y)->DeleteObject(ObjectMonster, this);
		_GameWorld->GetObjectPool()->DeletaObject(this);
		
	}
}

//������ Ŭ����
void MonsterStateOneStep::Enter()
{
	
	me->startTime = 0.f;

}

void MonsterStateOneStep::Update()
{

	/*MonsterStateBase* state = me->states["Atk"];
			if (me->currentState == state)
			{
				return;
			}*/
	//�ð� ����
	me->startTime += Time::Tick()*4;

	//_TileSize�� Ÿ�ϻ����� �����
	float _TileSize = _GameWorld->GetTileManager()->GetTileSize().x;
	//�÷��̾� ��ġ ��������
	D3DXVECTOR2 playerPos = IndexToPos(_GameWorld->GetGameData()->GetIndex(), D3DXVECTOR2(52, 52), D3DXVECTOR2(26, 26));


	if (me->name.substr(2, 10) == "GreenSlime")
	{
		_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->DeleteObject(ObjectMonster, me);
	}

	//���̷��� ������
	if (me->name.substr(2, 8) == "Skeleton")
	{

	
				if (me->startPos.x < playerPos.x)
				{
					if (_GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y)->GetAttribute() != ObjDestructable)
					{
						me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
					}
					else
					{
						me->position.x = Math::Lerp(me->startPos.x, me->startPos.x, me->startTime);
					}
				}
				if (me->startPos.y > playerPos.y)
				{
					if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y - 1)->GetAttribute() != ObjDestructable)
					{
						me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
					}
					else
					{
						me->position.y = Math::Lerp(me->startPos.y, me->startPos.y, me->startTime);
					}
				}


			   if (me->startPos.x > playerPos.x)
				{
					if (_GameWorld->GetTileManager()->Tile(me->myIndex.x - 1, me->myIndex.y)->GetAttribute() != ObjDestructable)
					{
						me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
					}
					else
					{
						me->position.x = Math::Lerp(me->startPos.x, me->startPos.x, me->startTime);
					}
				}
				if (me->startPos.y < playerPos.y)
				{
					if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y +1)->GetAttribute() != ObjDestructable)
					{
						me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
					}
					else
					{
						me->position.y = Math::Lerp(me->startPos.y, me->startPos.y, me->startTime);
					}
				}


				_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->DeleteObject(ObjectMonster, me);
	}



	//���� ������
	if (me->name.substr(2, 3) == "Bat")
	{
		
	
				me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);


				_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->DeleteObject(ObjectMonster, me);
	}

	//�Ķ� ������ ������
	if (me->name.substr(2, 9) == "BlueSlime")
	{

		
			me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
		
			
				_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->DeleteObject(ObjectMonster, me);
			
	}


	//�̳� Ÿ��罺 ������
	if (me->name.substr(2, 8) == "Minotaur")
	{
		if (me->startPos.x < playerPos.x) {
			me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
		}
		else if (me->startPos.x > playerPos.x) {
			me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
		}
		else if (me->startPos.y > playerPos.y) {
			me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
		}
		else if (me->startPos.y < playerPos.y) {
			me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
		}

		_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectMonster, me);
	}







	//1�ʰ� �Ѿ�� ��ε� ���̴� ���·� ���ư���
	if (me->startTime > 1.f)
	{
		me->ChangeState("Idle");
	}


}



void MonsterStateAtk::Enter()
{


	if (me->name.substr(2, 8) == "Skeleton")
	{

		me->tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->GetObjects(ObjectPlayer);

		for (int i = 0; i < me->tempArr.size(); ++i)
		{
			_MessagePool->ReserveMessage(me->tempArr[i], "PlayerHit");
		}

		
		
	
	}

	if (me->name.substr(2, 9) == "BlueSlime")
	{

		me->tempArr = _GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y )->GetObjects(ObjectPlayer);

		for (int i = 0; i < me->tempArr.size(); ++i)
		{
			_MessagePool->ReserveMessage(me->tempArr[i], "PlayerHit");
		}

	}
	

	if (me->name.substr(2, 3) == "Bat")
	{

		me->tempArr = _GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->GetObjects(ObjectPlayer);

		for (int i = 0; i < me->tempArr.size(); ++i)
		{
			_MessagePool->ReserveMessage(me->tempArr[i], "PlayerHit");
		}

	}


}

void MonsterStateAtk::Update()
{
	

}





void MonsterStateIdle::Enter()
{
	me->startTime = 0.f;
	
	
	//_TileSize�� Ÿ�ϻ����� �����
	float _TileSize = _GameWorld->GetTileManager()->GetTileSize().x;
	
	//me->startTime = 0.f;
	
	//�ʷ� ������ ���̴� 

	if (me->name.substr(2, 10) == "GreenSlime")
	{

		me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		me->mynextIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());

		if (me->myIndex.x <= 0) me->myIndex.x = 1;

		if (me->myIndex.y <= 0) me->myIndex.y = 1;

		if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

		if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

		if (me->mynextIndex.x <= 0) me->mynextIndex.x = 1;

		if (me->mynextIndex.y <= 0) me->mynextIndex.y = 1;

		if (me->mynextIndex.x > TileManager::mapSize.x) me->mynextIndex.y = TileManager::mapSize.x;

		if (me->mynextIndex.y > TileManager::mapSize.y) me->mynextIndex.y = TileManager::mapSize.y;

		
		_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->AddObject(ObjectMonster, me);

	}

	//���̷��� ���̴�
	if (me->name.substr(2, 8) == "Skeleton")
	{

		

	
		//���� ��ǥ�� �ٽ� ���� ��ǥ�� �ٲ�
				me->startPos.x = me->endPos.x;
				me->startPos.y = me->endPos.y;


				//me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
				//me->mynextIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());


				if (me->myIndex.x <= 0) me->myIndex.x = 1;

				if (me->myIndex.y <= 0) me->myIndex.y = 1;

				if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

				if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;
				if (me->mynextIndex.x <= 0) me->mynextIndex.x = 1;

				if (me->mynextIndex.y <= 0) me->mynextIndex.y = 1;

				if (me->mynextIndex.x > TileManager::mapSize.x) me->mynextIndex.y = TileManager::mapSize.x;

				if (me->mynextIndex.y > TileManager::mapSize.y) me->mynextIndex.y = TileManager::mapSize.y;
								
				
				D3DXVECTOR2 playerPos = IndexToPos(_GameWorld->GetGameData()->GetIndex(), D3DXVECTOR2(52, 52), D3DXVECTOR2(26, 26));

				//¬��Ÿ ��ġ���� ����
			if (me->startPos.x < playerPos.x )
			{
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x + 1, me->myIndex.y)->GetAttribute() != ObjDestructable)
				{
					me->endPos.x = me->startPos.x + _TileSize;
				}
				
			}
			else if (me->startPos.y > playerPos.y )
			{
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x , me->myIndex.y-1)->GetAttribute() != ObjDestructable)
				{
					me->endPos.y = me->startPos.y - _TileSize;
				}
			
			}
			else if (me->startPos.x > playerPos.x )
			{
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x-1, me->myIndex.y )->GetAttribute() != ObjDestructable)
				{
					me->endPos.x = me->startPos.x - _TileSize;
				}
				
			}
			else if (me->startPos.y < playerPos.y )
			{
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x , me->myIndex.y+1)->GetAttribute() != ObjDestructable)
				{
					me->endPos.y = me->startPos.y + _TileSize;
				}
				
			}

			if (me->startPos.x > 0)
			{

				//me->myIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
				me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
				me->mynextIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
			}
			_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);
	
	}




	//���� ���̴�
	if (me->name.substr(2, 3) == "Bat")
	{
	
		//0���� 3���� �������� �ϳ� �̾Ƽ� ����ġ������ ������ �� ��
		int batmove = Math::Random(0, 3);

		//���� ��ǥ�� �ٽ� ���� ��ǥ�� �ٲ�
			me->startPos.x = me->endPos.x;
			me->startPos.y = me->endPos.y;
			
			//���� ���� ��ǥ Ÿ�� �ε��� ���ؿ�
			me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
			me->mynextIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
			//_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->AddObject(ObjectMonster, me);
			

			//�� �ε����� Ÿ�Ϲ����� ��� �������������� ����ó��
			if (me->myIndex.x <= 0 ) me->myIndex.x = 1; 
				
			if (me->myIndex.y <= 0) me->myIndex.y = 1;

			if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

			if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

			if (me->mynextIndex.x <= 0) me->mynextIndex.x = 1;

			if (me->mynextIndex.y <= 0) me->mynextIndex.y = 1;

			if (me->mynextIndex.x > TileManager::mapSize.x) me->mynextIndex.y = TileManager::mapSize.x;

			if (me->mynextIndex.y > TileManager::mapSize.y) me->mynextIndex.y = TileManager::mapSize.y;

			

			//0~3�߿� �ϳ� �̴´�
			switch (batmove) {

			case 0:
				//������ ������Ʈ Ÿ�Ծƴ϶�� �̵�
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x-1, me->myIndex.y)->GetAttribute() != ObjDestructable)
				{
					me->endPos.x = me->startPos.x - _TileSize;
				}
				//������ ������Ʈ Ÿ���̸� �ݴ���̵�
				else 
				{
					me->endPos.x = me->startPos.x + _TileSize;
				}
				break;

			case 1:

				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x+1, me->myIndex.y)->GetAttribute() != ObjDestructable)
				{
					me->endPos.x = me->startPos.x + _TileSize;
				}
				else
				{
					me->endPos.x = me->startPos.x - _TileSize;
					
				}
				break;

			case 2:
				
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y+1)->GetAttribute() != ObjDestructable)
				{
					me->endPos.y = me->startPos.y + _TileSize;
				}
				else
				{
					me->endPos.y = me->startPos.y - _TileSize;
					
				}
				break;

			case 3:
				
				if (_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y-1)->GetAttribute() != ObjDestructable)
				{
					me->endPos.y = me->startPos.y - _TileSize;
				}
				else
				{
					me->endPos.y = me->startPos.y + _TileSize;
					
				}

				break;


				}

			_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->AddObject(ObjectMonster, me);
			//_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->AddObject(ObjectMonster, me);
			
	}


	//�Ķ������� ���̴�
	if (me->name.substr(2, 9) == "BlueSlime")
	{

		me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		//me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		//me->mynextIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		me->mynextIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());

		

		if (me->myIndex.x <= 0) me->myIndex.x = 1;

		if (me->myIndex.y <= 0) me->myIndex.y = 1;

		if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

		if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

		if (me->mynextIndex.x <= 0) me->mynextIndex.x = 1;

		if (me->mynextIndex.y <= 0) me->mynextIndex.y = 1;

		if (me->mynextIndex.x > TileManager::mapSize.x) me->mynextIndex.y = TileManager::mapSize.x;

		if (me->mynextIndex.y > TileManager::mapSize.y) me->mynextIndex.y = TileManager::mapSize.y;


		


		


		
		
		//���� ��ǥ�� �ٽð� ��ǥ�� �ٲ���(���Ʒ� �ݺ�)




			D3DXVECTOR2 temp;
			temp.y = me->endPos.y;
			me->endPos.y = me->startPos.y;
			me->startPos.y = temp.y;
 
			if (me->startPos.x > 0)
			{

				//me->myIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
				
				//me->mynextIndex = PosToIndex(me->endPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
			}
			
			
			_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->AddObject(ObjectMonster, me);
	

	}

	//�̳�Ÿ��罺 ���̴�
	if (me->name.substr(2, 8) == "Minotaur")
	{

		//���� ��ǥ�� �ٽ� ���� ��ǥ�� �ٲ�
		me->startPos.x = me->endPos.x;
		me->startPos.y = me->endPos.y;


		me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		

		if (me->myIndex.x <= 0) me->myIndex.x = 1;

		if (me->myIndex.y <= 0) me->myIndex.y = 1;

		if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

		if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

		D3DXVECTOR2 playerPos = IndexToPos(_GameWorld->GetGameData()->GetIndex(), D3DXVECTOR2(52, 52), D3DXVECTOR2(26, 26));
		_GameWorld->GetTileManager()->Tile(me->mynextIndex.x, me->mynextIndex.y)->AddObject(ObjectMonster, me);
		//¬��Ÿ ��ġ���� ����
		if (me->startPos.x < playerPos.x)
		{
			me->endPos.x = me->startPos.x + _TileSize;
		}
		else if (me->startPos.y > playerPos.y)
		{
			me->endPos.y = me->startPos.y - _TileSize;
		}
		else if (me->startPos.x > playerPos.x)
		{
			me->endPos.x = me->startPos.x - _TileSize;
		}
		else if (me->startPos.y < playerPos.y)
		{
			me->endPos.y = me->startPos.y + _TileSize;
		}


	}
	


}

void MonsterStateIdle::Update()
{
	
	//me->startTime += Time::Tick() * 4;
	//if (me->startTime > 1.f)
	//{
		//	if (me->currentState != me->states["Atk"] )
		//	{
		//		me->ChangeState("Move");
		//	}

	//	me->ChangeState("Move");
	//}
}