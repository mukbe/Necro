#pragma once

// 필요한 상태
// 1. 아이들, 2. 이동. 3. 공격 
// 아이들에서 -> 바닥 검사하고-> 공격범위에있으면 어택 , 없으면 이동 
// 이동과 공격에서는 정말 이동과 공격만 해야함 (목표지점에 도달했거나, 데미지를 넣었으면 바로 아이들로 돌아오게)

// 할 일
// 1. 이동 수정 >> 인덱스 말고 수치 이동으로 바꾸자 그냥 
// 2. 
// 3. 일단은 이동 범위만 확인
//    이동 범위 = 0(첫번쨰)로 두고, 공격 범위에 적이 있으면 공격 > 장애물이 있으면 장애물에 따라 삽질 , 아무것도없으면 이동 
// 4. 

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

	POINT attackrRange;						// 공격 범위



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