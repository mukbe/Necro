#pragma once

// �ʿ��� ����
// 1. ���̵�, 2. �̵�. 3. ���� 
// ���̵鿡�� -> �ٴ� �˻��ϰ�-> ���ݹ����������� ���� , ������ �̵� 
// �̵��� ���ݿ����� ���� �̵��� ���ݸ� �ؾ��� (��ǥ������ �����߰ų�, �������� �־����� �ٷ� ���̵�� ���ƿ���)

// �� ��
// 1. �̵� ���� >> �ε��� ���� ��ġ �̵����� �ٲ��� �׳� 
// 2. 
// 3. �ϴ��� �̵� ������ Ȯ��
//    �̵� ���� = 0(ù����)�� �ΰ�, ���� ������ ���� ������ ���� > ��ֹ��� ������ ��ֹ��� ���� ���� , �ƹ��͵������� �̵� 
// 4. 

//���漱��
class StateBase;
class PlayerMove;
class PlayerIdle;
class PlayerAttack;

enum PlayerDirection
{
	PlayerLeft,
	PlayerRight,
	PlayerUp,
	PlayerDown
};

class Player : public GameObject
{
private:
	friend class StateBase;
	friend class PlayerMove;
	friend class PlayerIdle;
	friend class PlayerAttack;


	
	StateBase* currentState;
	unordered_map<string, StateBase*> stateList;

	int frameX, frameY;			// ������ ������
	float interver;				// ������ ���͹�
	string imageName;			// �̹��� �̸� 

	D3DXVECTOR2 imagePos;		// �̹��� ��ġ ����
	
	D3DXVECTOR2 destination;	// ������
	float startTime;			// ���� �ð� 
	D3DXVECTOR2 startPos;		// ���� ��ġ �����

	POINT myIndex;				// �̵��Ҷ����� Ȯ���ϱ�� ���� ����ġ �ε��� 

	float jumpPower;			// ���� ��
	float gravity;				// �߷�

	PlayerDirection playerDirection;		// ����

	POINT attackrRange;						// ���� ����



public:
	Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~Player();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();

	//��Ʈ�� ���� -> Ű�Է� �����͸� ��������
	virtual void ControlUpdate();

	//��Ʈ�� �� ������ ��� ( Movetype_Control�� �ش���)
	virtual void MissControlUpdate();

	//���� ��ƾ -> ��Ÿ ������Ʈ �ֱ� 
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender();

	// ���¸� �����ϴµ� ���� �Լ� 
	void ChangeState(string str);

	void FloodFill(POINT index , int sight);

};



class StateBase
{
public:
	StateBase(Player* me) :me(me) {}
	~StateBase() {}

	virtual void Enter() = 0;	// �ʱ�ȭ

	//�������ߵǴ� Ÿ�ֿ̹��� ������� ������Ʈ
	//Ű�Է¹޾Ƽ� �ص��� ��� �͵� 
	virtual void BeatExcute() = 0;	

	virtual void Excute() = 0;	// ���ڿ� ������ �ʾƵ� �� ��� ������Ʈ
	virtual void Exit() {}		// 
protected:
	Player* me;
};

class PlayerIdle : public StateBase
{
public:
	PlayerIdle(Player* me) :StateBase(me) {}
	~PlayerIdle() {}
	virtual void Enter();
	virtual void BeatExcute();
	virtual void Excute();
	virtual void Exit();
};

class PlayerMove : public StateBase
{
public:
	PlayerMove(Player* me) :StateBase(me) {}
	~PlayerMove() {}
	virtual void Enter();

	virtual void BeatExcute();
	virtual void Excute();
	virtual void Exit();
};

class PlayerAttack : public StateBase
{
public:
	PlayerAttack(Player* me) :StateBase(me) {}
	~PlayerAttack() {}
	virtual void Enter();

	virtual void BeatExcute();
	virtual void Excute();
	virtual void Exit();
private:


};