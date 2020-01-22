#pragma once

class Monster : public GameObject
{
	friend class MonsterStateBase;
	friend class MonsterStateOneStep;
	friend class MonsterStateIdle;
public:
	
	Monster(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Monster();

	virtual void Init();
	virtual void Release();
	virtual void PreUpdate();
	virtual void Update(float tick);
	virtual void ControlUpdate();

	virtual void Render();
	virtual void ImguiRender();
	virtual void SettingCenterXY(float tilesize);
	virtual void MoveAndCheck();
	void ChangeState(string key);
	
	//void setMapMemoryAddressLink(TileManager* tm) { tilemanger = tm; }

protected :

	int FrameCount;
	int frameX;
	int frameY;
	float tilesize;
	float x;
	float y;
	D3DXVECTOR2 speed;
	int tileX, tileY;
	//TileManager *tilemanger;
	unordered_map<string, class MonsterStateBase*> states;
	MonsterStateBase* currentState;
	D3DXVECTOR2 startPos;
	D3DXVECTOR2 endPos;

	float batX;
	float batY;

private:
	bool firstmove;
	float startTime;
	float realtime;
	
	
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
	float time;
};
class MonsterStateIdle : public MonsterStateBase
{
public:
	MonsterStateIdle(Monster* p) : MonsterStateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:
};