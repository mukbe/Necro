#include "stdafx.h"
#include "Program.h"

#include "./Scenes/TestScene.h"
#include "./Scenes/TileTestScene.h"
#include "./Scenes/MapToolScene.h"
#include "./Scenes/GameScene.h"

Program::Program()
{
	//게임정보저장 json or sql
	//jsonRoot = new Json::Value();
	//JsonHelper::ReadData(L"LevelEditor.json", jsonRoot);


	bGrid = false;
	gridColor = ColorWhite;

	SceneBase* scene = new MapToolScene;
	_SceneManager->AddScene("Map", scene);
	scene = new TileTestScene;
	_SceneManager->AddScene("TileTest", scene);
	scene = new TestScene;
	_SceneManager->AddScene("Test", scene);
	scene = new GameScene;
	_SceneManager->AddScene("Game", scene);

	_SceneManager->ChangeScene("Game");

	CAMERA->ModeTargetPlayer();
	//CAMERA->ModeFreeCamera();


	_ImageManager->AddFrameTexture("Test", ResourcePath + L"Effect/Swipe_Broadsword.png", 3);
	EFFECTS->AddEffect("Test", "Test");

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

void Program::PreUpdate()
{
	if (Keyboard::Get()->Down(VK_F1))
		bGrid = !bGrid;
	if (Keyboard::Get()->Down(VK_F2))
		CAMERA->Shake();
	if (Keyboard::Get()->Down(VK_F6))
		EFFECTS->Fire("Test", D3DXVECTOR2(WinSizeX*0.5f, WinSizeY * 0.5f), D3DXVECTOR2(100, 100),Math::Random(0.f, Math::PI * 2.f));


	//if (Keyboard::Get()->Down(VK_F9))
	//{
	//	_SceneManager->ChangeScene("Map");
	//}
	//if (Keyboard::Get()->Down(VK_F10))
	//{
	//	_SceneManager->ChangeScene("TileTest");

	//}
	//if (Keyboard::Get()->Down(VK_F11))
	//{
	//	_SceneManager->ChangeScene("Test");

	//}


}

void Program::Update(float tick)
{
	EFFECTS->Update(tick);

	_GameWorld->Update(tick);

}

void Program::PostUpdate()
{

}

void Program::Render()
{
	if(bGrid)
		MakeGrid();


	p2DRenderer->SetCamera(true);

	_GameWorld->ObjectRender();
	//_ImageManager->FindTexture("test")->FrameRender(FloatRect({ 100,100 }, 100, Pivot::CENTER), nullptr);
	EFFECTS->Render();

	//wstring str;
	//str += L"pos.x : " + to_wstring(CAMERA->GetMousePos().x).substr(0, 6);
	//str += L"pos.y : " + to_wstring(CAMERA->GetMousePos().y).substr(0, 6);
	//p2DRenderer->SetCamera(false);
	//p2DRenderer->DrawText2D(D3DXVECTOR2((Mouse::Get()->GetPosition().x - 200.f), (Mouse::Get()->GetPosition().y - 20.f)), str, 20, gridColor);

}

void Program::PostRender()
{
	_GameWorld->LightRender();
}

void Program::ImguiRender()
{
	static bool bLockFPS = true;
	static int fps = (int)Time::Get()->GetLockFPS();
	ImGui::Begin("Info");
	{
		ImGui::Text("FPS : %f", Time::Get()->FPS()); ImGui::SameLine();

		if (ImGui::Checkbox("FPS Lock", &bLockFPS) || ImGui::InputInt("FPS Value", &fps))
		{
			if (bLockFPS)
				Time::Get()->SetLockFPS((float)fps);
			else
				Time::Get()->SetLockFPS(0.f);
		}
		ImGui::Text("Tick : %f", Time::Delta());
		ImGui::Text("PosX : %.2f, PosY : %.2f", CAMERA->GetPos().x, CAMERA->GetPos().y);
		ImGui::Checkbox("Grid View", &bGrid);
		
	
		if (ImGui::ColorEdit3("Clear Color", &p2DRenderer->clearColor.r))
		{
			gridColor.r = 1.f - p2DRenderer->clearColor.r;
			gridColor.g = 1.f - p2DRenderer->clearColor.g;
			gridColor.b = 1.f - p2DRenderer->clearColor.b;
		}
		if (ImGui::ColorEdit4("Grid Color", &gridColor.r))
		{
			p2DRenderer->clearColor.r = 1.f - gridColor.r;
			p2DRenderer->clearColor.g = 1.f - gridColor.g;
			p2DRenderer->clearColor.b = 1.f - gridColor.b;

		}

	}
	ImGui::End();


	_GameWorld->ImguiRender();

}

void Program::ResizeScreen()
{
	D3DDesc desc;
	DxRenderer::GetDesc(&desc);
}

//void Program::TestFunc()
//{
	//IGraphBuilder* graph = nullptr;
	//IMediaControl* control = nullptr;
	//IMediaEvent* eventMedia = nullptr;
	//HRESULT hr;
	//hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	//hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)graph);
	//graph->QueryInterface(IID_IMediaControl, (void**)eventMedia);

	//graph->RenderFile(L"../_Resources/intro.avi", nullptr);
	//if (SUCCEEDED(control->Run()))
	//{
	//	long ev;
	//	eventMedia->WaitForCompletion(INFINITE, &ev);
	//}


	//eventMedia->Release();
	//control->Release();
	//graph->Release();
	//CoUninitialize();

//}

void Program::MakeGrid()
{
	vector<pair<D3DXVECTOR2, D3DXVECTOR2>> grid;
	vector<float> arrayX, arrayY;

	FloatRect rc = CAMERA->GetRenderRect();
	D3DXVECTOR2 tilesize = TileManager::tileSize;
	int starty = (int)(rc.top / tilesize.y);
	int endy = (int)(rc.bottom / tilesize.y);

	for (int y = starty-1; y <= endy + 1; y++)
	{
		arrayY.push_back(y * tilesize.y);
	}

	int startx = (int)(rc.left / tilesize.x);
	int endx = (int)(rc.right / tilesize.x);
	for (int x = startx-1; x <= endx + 1; x++)
	{
		arrayX.push_back(x * tilesize.x);
	}

	p2DRenderer->SetCamera(true);

	//가로
	for (int i = 0; i < arrayY.size(); i++)
	{
		if (arrayY[i] == 0)
		{
			p2DRenderer->DrawLine(D3DXVECTOR2(arrayX[0], arrayY[i]), D3DXVECTOR2(arrayX[arrayX.size() - 1], arrayY[i]), nullptr, gridColor, 3.f);
			continue;
		}

		p2DRenderer->DrawLine(D3DXVECTOR2(arrayX[0] , arrayY[i] ), D3DXVECTOR2(arrayX[arrayX.size() - 1] , arrayY[i] ), nullptr, gridColor);
	}
	//세로
	for (int i = 0; i < arrayX.size(); i++)
	{
		if (arrayX[i] == 0)
		{
			p2DRenderer->DrawLine(D3DXVECTOR2(arrayX[i], arrayY[0]), D3DXVECTOR2(arrayX[i], arrayY[arrayY.size() - 1]), nullptr, gridColor,3.f);
			continue;
		}

		p2DRenderer->DrawLine(D3DXVECTOR2(arrayX[i] , arrayY[0] ), D3DXVECTOR2(arrayX[i] , arrayY[arrayY.size() - 1]) , nullptr, gridColor);
	}

	p2DRenderer->DrawText2D(D3DXVECTOR2(0, 0), L"0", 20, gridColor);

}


void Program::GameUIRender()
{
	//D2D + D3D 랜더링이 가능한 영역
	//다만 순서는 D2D먼저 그려짐 이유는 Window.cpp에서 순서를 보면됨

	//따라서 랜더링을 나눌 매니져급 객체가 필요
	_GameWorld->UIRender();

}
