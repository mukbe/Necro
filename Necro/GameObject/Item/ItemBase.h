#pragma once


// 아이템 공통으로 사용하는 함수 / 변수  등  다 여기서 선언! 
// 모든 메세지 키 값은 통일로 해서 플레이어 / 맵툴도 사용가능 할 수 있게 

class ItemBase : public GameObject
{
public:
	ItemBase(string name, D3DXVECTOR2 pos,D3DXVECTOR2 size);
	~ItemBase();

public:
											// 게임 오브젝트에서  상속 받을 때 필요한 함수 그리고 Itembase에 상속 받는 클래스들은 쓸 거만 가져가면 됨!
	virtual void Init();					// 인잇!
											
	virtual void Release();					// 릴리즈!  위 두개는 필수
											
	virtual void ControlUpdate();			
											
	virtual void Update(float tick);		
											
	virtual void Render();					
											
	virtual void Init(POINT tileIndex);		

protected:
	
	bool bShow;  // 아이템 시야에 들었을때 보이게 혹은 안보이게 하는거
};

