#include "stdafx.h"
#include "Monster.h"
#include "./Systems/Manage/TileManager.h""
#include "./GameObject/Map/TileNode.h"

static float batX;
static float batY;

Monster::Monster(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: GameObject(name, pos, size)
{
	currentState = nullptr;

	states.insert(make_pair("Idle", new MonsterStateIdle(this)));
	states.insert(make_pair("Move", new MonsterStateOneStep(this)));
	startTime = 0.f;
	realtime = 0.f;
	//startPos = pos;
	//endPos = { pos.x+52.f, pos.y+52.f };
	firstmove = false;
	myIndex = { 0,0 };
	//startPos = { 0,0 };
	//mynextIndex = { 0,0 };
	ChangeState("Idle");
	
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
		ChangeState("Move");
		
		if (name == "Skeleton") 
		{
			monsterBeat = 2;
		}
		if (name == "Bat")
		{
			monsterBeat = 1;
		}
		if (name == "BlueSlime")
		{
			monsterBeat = 2;
		}
		if (name == "Minotaur")
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
}

void Monster::ProcessDestroy()
{
	life--;
	if (life <= 0)
	{
		//����Ʈ �߰� �ʿ�.


		this->SetActive(false);
	}
}

//������ Ŭ����
void MonsterStateOneStep::Enter()
{
	
	me->startTime = 0.f;
	//me->realtime = 0.f;
	

}

void MonsterStateOneStep::Update()
{

	
	//�ð� ����
	me->startTime += Time::Tick()*4;
	
	

	//���̷��� ������
	if (me->name == "Skeleton")
	{

		//for(int i=)
		//vector<GameObject*> tempArr = upTilePos->GetObjects(ObjectPlayer);


				//batX�� batY�� ������ǥ�ε� �ϴ� ���󰡰� �س�������
				if (me->startPos.x < batX) 
				{
					me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				}
			    else if (me->startPos.x > batX) 
				{
					me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				}
				else if (me->startPos.y > batY) 
				{
					me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
				}
				else if (me->startPos.y < batY) 
				{
					me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
				}


				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectMonster, me);
	}



	//���� ������
	if (me->name == "Bat") 
	{
		

				me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
				me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);


				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectMonster, me);
	}

	//�Ķ� ������ ������
	if (me->name == "BlueSlime") 
	{
			me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);	


			_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->DeleteObject(ObjectMonster, me);
	}


	//�̳� Ÿ��罺 ������
	if (me->name == "Minotaur")
	{
		if (me->startPos.x < batX) {
			me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
		}
		else if (me->startPos.x > batX) {
			me->position.x = Math::Lerp(me->startPos.x, me->endPos.x, me->startTime);
		}
		else if (me->startPos.y > batY) {
			me->position.y = Math::Lerp(me->startPos.y, me->endPos.y, me->startTime);
		}
		else if (me->startPos.y < batY) {
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

	

}

void MonsterStateAtk::Update()
{

	

}





void MonsterStateIdle::Enter()
{
	//����ġ ���
	//_GameWorld->GetTileManager()->Tile(2, 2)->AddObject(me);
	//����ġ ����
	//_GameWorld->GetTileManager()->Tile(2, 2)->DeleteObject(me);
	
	//_TileSize�� Ÿ�ϻ����� �����
	float _TileSize = _GameWorld->GetTileManager()->GetTileSize().x;
	
	//me->startTime = 0.f;
	

	//���̷��� ���̴�
	if (me->name == "Skeleton")
	{
	
		//���� ��ǥ�� �ٽ� ���� ��ǥ�� �ٲ�
				me->startPos.x = me->endPos.x;
				me->startPos.y = me->endPos.y;

				me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
				


				if (me->myIndex.x <= 0) me->myIndex.x = 1;

				if (me->myIndex.y <= 0) me->myIndex.y = 1;

				if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

				if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

				_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);
				//¬��Ÿ ��ġ���� ����
			if (me->startPos.x < batX)
			{
				me->endPos.x = me->startPos.x + _TileSize;
			}
			else if (me->startPos.y > batY)
			{
				me->endPos.y = me->startPos.y - _TileSize;
			}
			else if (me->startPos.x > batX)
			{
				me->endPos.x = me->startPos.x - _TileSize;
			}
			else if (me->startPos.y < batY)
			{
				me->endPos.y = me->startPos.y + _TileSize;
			}



		
	
	}




	//���� ���̴�
	if (me->name == "Bat") 
	{
	
		//0���� 3���� �������� �ϳ� �̾Ƽ� ����ġ������ ������ �� ��
		int batmove = Math::Random(0, 3);

		//���� ��ǥ�� �ٽ� ���� ��ǥ�� �ٲ�
			me->startPos.x = me->endPos.x;
			me->startPos.y = me->endPos.y;
			//�ӽ÷� ���� ��ǥ����(�÷��̾����ؼ� ������ ��)
			batX = me->startPos.x;
			batY = me->startPos.y;
			//���� ���� ��ǥ Ÿ�� �ε��� ���ؿ�
			me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());

			

			//�� �ε����� Ÿ�Ϲ����� ��� �������������� ����ó��
			if (me->myIndex.x <= 0 ) me->myIndex.x = 1; 
				
			if (me->myIndex.y <= 0) me->myIndex.y = 1;

			if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

			if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

			_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);

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
		
	}


	//�Ķ������� ���̴�
	if (me->name == "BlueSlime") 
	{


		me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		
		
		if (me->myIndex.x <= 0) me->myIndex.x = 1;

		if (me->myIndex.y <= 0) me->myIndex.y = 1;

		if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

		if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;


		_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);
		//���� ��ǥ�� �ٽð� ��ǥ�� �ٲ���(���Ʒ� �ݺ�)
			D3DXVECTOR2 temp;
			temp.y = me->endPos.y;
			me->endPos.y = me->startPos.y;
			me->startPos.y = temp.y;	
		
	}

	//�̳�Ÿ��罺 ���̴�
	if (me->name == "Minotaur")
	{

		//���� ��ǥ�� �ٽ� ���� ��ǥ�� �ٲ�
		me->startPos.x = me->endPos.x;
		me->startPos.y = me->endPos.y;


		me->myIndex = PosToIndex(me->startPos, _GameWorld->GetTileManager()->GetTileSize(), _GameWorld->GetTileManager()->GetPivotPos());
		

		if (me->myIndex.x <= 0) me->myIndex.x = 1;

		if (me->myIndex.y <= 0) me->myIndex.y = 1;

		if (me->myIndex.x > TileManager::mapSize.x) me->myIndex.y = TileManager::mapSize.x;

		if (me->myIndex.y > TileManager::mapSize.y) me->myIndex.y = TileManager::mapSize.y;

		_GameWorld->GetTileManager()->Tile(me->myIndex.x, me->myIndex.y)->AddObject(ObjectMonster, me);
		//¬��Ÿ ��ġ���� ����
		if (me->startPos.x < batX)
		{
			me->endPos.x = me->startPos.x + _TileSize;
		}
		else if (me->startPos.y > batY)
		{
			me->endPos.y = me->startPos.y - _TileSize;
		}
		else if (me->startPos.x > batX)
		{
			me->endPos.x = me->startPos.x - _TileSize;
		}
		else if (me->startPos.y < batY)
		{
			me->endPos.y = me->startPos.y + _TileSize;
		}


	}



}

void MonsterStateIdle::Update()
{
	
	
		//me->ChangeState("Move");
	
}