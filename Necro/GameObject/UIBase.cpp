#include "stdafx.h"
#include "UIBase.h"





UIBase::UIBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);

	_ImageManager->AddFrameTexture("HeartTemp", ResourcePath + L"UI/TempHeart.png", 2,1 );
	
	frameX = 0;
}

UIBase::~UIBase()
{
}


void UIBase::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);


}

void UIBase::PreUpdate()
{

}

void UIBase::Update(float tick)
{
	// ----------심장 노트 
	rc = FloatRect::MoveRect(rc, D3DXVECTOR2(5.f, 0));
	if (rc.right > WinSizeX * 0.5f)
		rc.Update(D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70), Pivot::CENTER);
	//---------------
	
	frameX++;
	if (frameX > 1) {
		frameX = 0;
	}
}


void UIBase::Render()
{
	p2DRenderer->SetCamera(false);
	p2DRenderer->DrawRectangle(rc, nullptr);

	
	//_ImageManager->FrameRender("HeartTemp", FloatRect({ WinSizeX / 2 ,830 },130,Pivot::CENTER),nullptr, 2, 1, 0, { 0,0 });
	_ImageManager->FrameRender("HeartTemp", FloatRect({ WinSizeX / 2.f , 830.f }, { 130.f,140.f }, Pivot::CENTER), nullptr, frameX, 0);
	


	/**프레임 랜더 외 않되
	_ImageManager->FindTexture("test")->FrameRender(FloatRect({ 100,100 }, 100, Pivot::CENTER), nullptr);
	Texture::FrameRender(FloatRect rc, Matrix2D * transform, UINT frameX, UINT frameY, float alpha, D3DXVECTOR2 offset)
	실패 1 _ImageManager->FindTexture("HeartTemp")->FrameRender(FloatRect({ WinSizeX / 2 ,830 }, 125, Pivot::CENTER), nullptr);
	실패 2 Texture::FrameRender("HeartTemp")->FrameRender(rc,10, 2, 0, 1, {0,0});
	실패 3 _ImageManager->FrameRender("HeartTemp")->FrameRender(rc, nullptr, 2, 1, 1, { 0,0 });
	실패 4 이거는 뭘까요~?> p2DRenderer->IASet(nullptr);
	실패 5 _ImageManager->FrameRender("HeartTemp", rc, nullptr, 2, 1, 1, { 0,0 });
	실패 6 _ImageManager->FindTexture("HeartTemp")->FrameRender(rc, nullptr, 2, 1, 0, { 0,0 });
	하ㅅㅂ _ImageManager->FindTexture("HeartTemp")->FrameRender(FloatRect({ WinSizeX /2,830 }, 130, Pivot::CENTER), nullptr);
	8   _ImageManager->FrameRender("HeartTemp", rc, nullptr, 2, 1, 1, { 0,0 });
	*/
}
