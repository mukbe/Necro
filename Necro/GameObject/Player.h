#pragma once

// 할 일
// 1. 이펙트
// 2. 무기 
// 3. 

//전방선언
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

	int frameX, frameY;			// 프레임 렌더용
	float interver;				// 프레임 인터벌
	string imageName;			// 이미지 이름 
	

	D3DXVECTOR2 imagePos;		// 이미지 위치 보정
	
	D3DXVECTOR2 destination;	// 목적지
	float startTime;			// 시작 시간 
	D3DXVECTOR2 startPos;		// 시작 위치 저장용

	POINT myIndex;				// 이동할때마다 확인하기용 현제 내위치 인덱스 

	float jumpPower;			// 점프 힘
	float gravity;				// 중력

	PlayerDirection playerDirection;		// 방향


	vector<GameObject*> shownTiles;

	string EffactName;			// 공격 이팩트 이름 
	POINT attackRange;			// 공격 범위
	vector<POINT> vAttackRange;
	
	bool isSight;



public:
	Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~Player();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();

	//컨트롤 관련 -> 키입력 같은것만 넣으랬음
	virtual void ControlUpdate();

	//노트를 못 눌렀을 경우 ( Movetype_Control만 해당함)
	virtual void MissControlUpdate();

	//메인 루틴 -> 기타 업데이트 넣기 
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender();

	// 상태를 변경하는데 쓰일 함수 
	void ChangeState(string str);

	void FloodFill(POINT index , int sight);
	// 시야 
	void Sight();
	// 삽질
	void Shovel(TileNode* TilePos, vector<GameObject*> temp);
	// 이동하기 위해 초기화 하는것들 
	void InitToMove(TileNode* TilePos, float JumpPower, float Gravity);

	void setSight(bool sight) { isSight = sight; }
};



class StateBase
{
public:
	StateBase(Player* me) :me(me) {}
	~StateBase() {}

	virtual void Enter() = 0;	// 초기화

	//움직여야되는 타이밍에서 해줘야할 업데이트
	//키입력받아서 해동할 어떠한 것들 
	virtual void BeatExcute() = 0;	

	virtual void Excute() = 0;	// 박자에 맞추지 않아도 될 어떠한 업데이트
	virtual void Exit() {}		
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
};

