#pragma once

// 필요한 상태
// 1. 아이들, 2. 이동. 3. 공격 
// 아이들에서 -> 바닥 검사하고-> 공격범위에있으면 어택 , 없으면 이동 
// 이동과 공격에서는 정말 이동과 공격만 해야함 (목표지점에 도달했거나, 데미지를 넣었으면 바로 아이들로 돌아오게)

// 20200121 오늘 할 일
// 0. 타일 검출 부터 해보자
// 1. 플레이어 위치 조정						  >>>>>>> 완료
// 3. 아이템에 따른 상태 만들기  ( 다른 오브젝트나 에너미에 붙여도 되게 만들라고 하던데 뭘까
//    아이템 담당자한테 머만들지 함 물어보기
// 4. 심장 템포에 캐릭터 움직임을 약간 제어 할수있을ㅈ ㅣ 보자 
// 2. 플레이어 이동(점프)로 바꾸기				  
// 


//전방선언
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

	D3DXVECTOR2 _pos , _size;		//중점 , 사이즈 < 이거 겟셋으로 불러 올수있는거같긴한데 일단 그냥 넣어놈.
	
	StateBase* currentState;
	unordered_map<string, StateBase*> stateList;


	int frameX, frameY;			// 프레임 렌더용
	string head,body;			// 프레임 이름 
	float interver;				// 프레임 인터벌
	D3DXVECTOR2 destination;	// 목적지
	float startTime;			// 시작 시간 
	D3DXVECTOR2 startPos;		// 시작 위치 저장용

	POINT nowPos;				// 현제 위치 
	POINT goPos;				// 이동할 타일 위치 

public:
	Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~Player();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();

	//컨트롤 관련 -> 키입력 같은것만 넣으랬음
	virtual void PreUpdate();
	//메인 루틴 -> 기타 업데이트 넣기 
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender();

	// 상태를 변경하는데 쓰일 함수 
	void ChangeState(string str);

};



class StateBase
{
public:
	StateBase(Player* me) :me(me) {}
	~StateBase() {}

	virtual void Enter() = 0;	// 초기화	
	virtual void Excute() = 0;	// 업데이트
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