#include "stdafx.h"
#include "Program.h"

#include "./Scenes/TestScene.h"
#include "./Scenes/TileTestScene.h"

Program::Program()
{

	//게임정보저장 json or sql
	//jsonRoot = new Json::Value();
	//JsonHelper::ReadData(L"LevelEditor.json", jsonRoot);

	//여기서 일단 씬 관리  여기는 UI
	SceneBase* scene = new TestScene;
	_SceneManager->AddScene(scene);
	

	// 타일씬 관리 
	//SceneBase* scene = new TileTestScene;
	//_SceneManager->AddScene(scene);

	//IMGUI FONT SETUP
	//텍스트에 한 글자라고 한글이 들어간 경우 Imgui::Text(u8"테스트 TEST"); 
	//텍스트 앞에 u8을 써주어야함 유니코드 사용
	{
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("..//_Resources//TTF//Maplestory Light.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());
	}
	Shaders->CreateShader("Color", L"Color.hlsl");

	//_ImageManager->AddFrameTexture("test", ResourcePath + L"monster04_idle.png", 4, 6);
}

Program::~Program()
{
}

void Program::ControlUpdate()
{
	_GameWorld->ControlUpdate();
}

void Program::Update(float tick)
{
	_GameWorld->Update(tick);
}

void Program::PostUpdate()
{

}

void Program::Render()
{
	_GameWorld->ObjectRender();


	p2DRenderer->SetCamera(true);

	p2DRenderer->DrawLine(D3DXVECTOR2(-10000, 0), D3DXVECTOR2(10000, 0),nullptr);
	p2DRenderer->DrawLine(D3DXVECTOR2(0, -10000), D3DXVECTOR2(0, 10000),nullptr);
	//p2DRenderer->DrawRectangle(FloatRect({ 100,100 }, 100, Pivot::CENTER),nullptr);

	wstring str;
	str += L"pos.x : " + to_wstring(CAMERA->GetMousePos().x).substr(0, 6);
	str += L"pos.y : " + to_wstring(CAMERA->GetMousePos().y).substr(0, 6);
	p2DRenderer->DrawText2D(Mouse::Get()->GetPosition().x - 200, Mouse::Get()->GetPosition().y - 20, str, 20);


}

void Program::PostRender()
{
	_GameWorld->LightRender();
}

void Program::ImguiRender()
{
	static bool bLockFPS = true;
	static int fps = Time::Get()->GetLockFPS();
	ImGui::Begin("Info");
	{
		ImGui::Text("FPS : %f", Time::Get()->FPS()); ImGui::SameLine();

		if (ImGui::Checkbox("FPS Lock", &bLockFPS) || ImGui::InputInt("FPS Value", &fps))
		{
			if (bLockFPS)
				Time::Get()->SetLockFPS(fps);
			else
				Time::Get()->SetLockFPS(0.f);
		}
		ImGui::Text("Tick : %f", Time::Delta());
		ImGui::Text("PosX : %.2f, PosY : %.2f", CAMERA->GetPos().x, CAMERA->GetPos().y);
	}
	ImGui::End();


	_GameWorld->ImguiRender();

}

void Program::ResizeScreen()
{
	D3DDesc desc;
	DxRenderer::GetDesc(&desc);
}


void Program::GameUIRender()
{
	//D2D + D3D 랜더링이 가능한 영역
	//다만 순서는 D2D먼저 그려짐 이유는 Window.cpp에서 순서를 보면됨

	//따라서 랜더링을 나눌 매니져급 객체가 필요
	_GameWorld->UIRender();

}
