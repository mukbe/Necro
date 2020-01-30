#pragma once
class ShopKeeper : public GameObject
{

	int frameX, frameY;			// 프레임 렌더용
	float interver;				// 프레임 인터벌 
	float loudness;				// 소리 크기 
	D3DXVECTOR2 distance;		// 플레이어와의 거리 

public:
	ShopKeeper(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	 ~ShopKeeper();
	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();

	//메인 루틴 -> 기타 업데이트 넣기 
	virtual void Update(float tick);

	virtual void Render();
};

