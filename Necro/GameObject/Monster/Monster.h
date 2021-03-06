#pragma once
static const char aaa[100];
class Monster : public GameObject
{
	friend class MonsterStateBase;
	friend class MonsterStateOneStep;
	friend class MonsterStateAtk;
	friend class MonsterStateIdle;
public:
	
	Monster(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Monster();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void ControlUpdate();

	virtual void Render();
	virtual void ImguiRender();
	void ChangeState(string key);
	virtual void ProcessDestroy();
	//시야에 따라서 실행할 함수들
	virtual void Show();
	virtual void Hide();

	//처음 시야에 들어왔을 때 실행할 함수
	virtual void Active();

protected :

	int FrameCount;
	int frameX;
	int frameY;
	unordered_map<string, class MonsterStateBase*> states;
	MonsterStateBase* currentState;
	D3DXVECTOR2 startPos;
	D3DXVECTOR2 endPos;

	int monsterBeat;
	int life;
	POINT myIndex;
	POINT mynextIndex;
	bool monkeyckeak;
	bool ismotion;
	bool bShow;
private:
	
	
	bool firstmove;
	float startTime;
	float realtime;
	vector<GameObject*> tempArr;
};




class MonsterStateBase
{
public:
	MonsterStateBase(Monster* p)
		:me(p) {}
	virtual void Enter() = 0;
	virtual void Update() = 0;
protected:
	Monster* me; // 상속한다 Monster클래스 me 값을 상속
};

class MonsterStateOneStep : public MonsterStateBase
{
public:
	MonsterStateOneStep(Monster* p) : MonsterStateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:
	
};

class MonsterStateAtk : public MonsterStateBase
{
public:
	MonsterStateAtk(Monster* p) : MonsterStateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:

};


class MonsterStateIdle : public MonsterStateBase
{
public:
	MonsterStateIdle(Monster* p) : MonsterStateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:
};