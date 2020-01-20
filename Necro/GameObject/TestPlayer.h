#pragma once
class TestPlayer : public GameObject
{
public:
	TestPlayer(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~TestPlayer();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//컨트롤 관련
	virtual void ControlUpdate();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();


};

