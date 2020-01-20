#pragma once


// �ʿ��� ����
// 1. ���̵�, 2. �̵�. 3. ���� ?
// ���̵鿡�� -> �ٴ� �˻��ϰ�-> ���ݹ����������� ���� , ������ �̵� >>> �̷������� �ؾ�����������??

//���漱��
class StateBase;
class PlayerMove;
class PlayerIdle;
class PlayerAttack;

class Player : public GameObject
{
private:
	friend class StateBase;
	friend class PlayerMove;
	friend class PlayerIdle;
	friend class PlayerAttack;

	D3DXVECTOR2 _pos , _size;		//���� , ������ < �̰� �ټ����� �ҷ� �ü��ִ°Ű����ѵ� �ϴ� �׳� �־��.
	
	StateBase* currentState;
	unordered_map<string, StateBase*> stateList;

	int frameX, frameY;			// ������ ������
	string head,body;			// ������ �̸� 
	float interver;				// ������ ���͹�
	D3DXVECTOR2 destination;	// ������

public:
	Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~Player();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();

	//��Ʈ�� ���� -> Ű�Է� �����͸� ��������
	virtual void PreUpdate();
	//���� ��ƾ -> ��Ÿ ������Ʈ �ֱ� 
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender() {}

	void ChangeState(string str);

};

enum PlayerState {
	MOVELEFT,
	MOVERIGHT,
	MOVEUP,
	MOVEDOWN

};
class StateBase
{
public:
	StateBase(Player* me) :me(me) {}
	~StateBase() {}

	virtual void Enter() = 0;	// �ʱ�ȭ	
	virtual void Excute() = 0;	// ������Ʈ
	virtual void Exit() {}		// 
protected:
	Player* me;
	PlayerState PlayerState;
};

class PlayerIdle : public StateBase
{
public:
	PlayerIdle(Player* me) :StateBase(me) {}
	~PlayerIdle() {}
	virtual void Enter();
	virtual void Excute();
	virtual void Exit();
};

class PlayerMove : public StateBase
{
public:
	PlayerMove(Player* me) :StateBase(me) {}
	~PlayerMove() {}
	virtual void Enter();
	virtual void Excute();
	virtual void Exit();
};

class PlayerAttack : public StateBase
{
public:
	PlayerAttack(Player* me) :StateBase(me) {}
	~PlayerAttack() {}
	virtual void Enter();
	virtual void Excute();
	virtual void Exit();
private:


};