#include "MapTool.h"
#include "TileManager.h"
#include "TileNode.h"

MapTool::MapTool(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	_ImageManager->AddFrameTexture("DefaultMap", ResourcePath + L"DefaultTileMap.png", 2, 2);
//	map = new TileManager(defaultMapSize, defaultTileSize, D3DXVECTOR2(0.f, 0.f));
	map = new TileManager(defaultMapSize, defaultTileSize, D3DXVECTOR2(0.f, 0.f));
	//pallete = new TileManager({ 1,1 }, D3DXVECTOR2(52.f, 52.f),
	//	D3DXVECTOR2(100.f, 100.f));

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("..//_Resources//TTF//Maplestory Light.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());

	_RenderPool->Request(this, RenderManager::Layer::Imgui);

}

MapTool::~MapTool()
{
}

void MapTool::Init()
{
}

void MapTool::ControllUpdate()
{
}

void MapTool::Update(float tick)
{
	if (Keyboard::Get()->Down(VK_LBUTTON))
	{
		TileNode* tempNode = isInCollision();

		if (tempNode != nullptr)
		{
			ProcessSetMap(tempNode);
		}
	}
}

void MapTool::Render()
{
}

void MapTool::ImguiRender()
{
	const char* currentBrushMode;
	switch (brushType)
	{
	case Brush:
		currentBrushMode = "Brush";
		break;
	case Eraser:
		currentBrushMode = "Eraser";
		break;
	default:
		currentBrushMode = "None Selected";
	}

	const char* currentPalleteMode;
	switch (palleteType)
	{
	case Terrain:
		currentPalleteMode = "Terrain";
		break;
	case Object:
		currentPalleteMode = "Object";
		break;
	default:
		currentPalleteMode = "None Selected";
	}

	ImGui::Begin(u8"Map Tool");
	{
		//ImGui::SetWindowPos(ImVec2(WinSizeX - 520.f, 10.f));
		//ImGui::SetWindowSize(ImVec2(500.f, WinSizeY - 20.f));

		ImGui::Text("Brush Mode");
		ImGui::Separator();
		ImGui::Text("Current Mode = %s", currentBrushMode);
		if (ImGui::Button("Brush", ImVec2(100, 50)))
		{
			brushType = Brush;
		}
		ImGui::SameLine();
		if (ImGui::Button("Eraser", ImVec2(100, 50)))
		{
			brushType = Eraser;
		}
		ImGui::Separator();

		ImGui::Text("Pallete Mode");
		ImGui::Separator();
		ImGui::Text("Pallete Mode = %s", currentPalleteMode);
		if (ImGui::Button("Terrain", ImVec2(100, 50)))
		{
			palleteType = Terrain;
		}
		ImGui::SameLine();
		if (ImGui::Button("Object", ImVec2(100, 50)))
		{
			palleteType = Object;
		}
		ImGui::Separator();
	}
	ImGui::End();
}

TileNode* MapTool::isInCollision()
{
	vector<TileNode*> tempMapArr = map->GetArray();
	vector<TileNode*>::iterator vecIter = tempMapArr.begin(), vecEnd = tempMapArr.end();

	for (; vecIter != vecEnd; ++vecIter)
	{
		if (Math::IsPointInAABB((*vecIter)->GetRect(), (D3DXVECTOR2)Mouse::Get()->GetPosition()))
		{
			return (*vecIter);
		}
	}
	return nullptr;
}

void MapTool::ProcessSetMap(TileNode* targetNode)
{
	switch (brushType)
	{
	case Brush:
		break;
	case Eraser:
		targetNode->Init();
		break;
	default:
		break;
	}
}