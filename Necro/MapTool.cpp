#include "MapTool.h"
#include "TileManager.h"
#include "TileNode.h"

MapTool::MapTool(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	_ImageManager->AddFrameTexture("DefaultMap", ResourcePath + L"DefaultTileMap.png", 2, 2);

	
	/*map = new TileManager({ 10, 10 }, defaultTileSize, D3DXVECTOR2(defaultTileSize.x / 2.f, defaultTileSize.y / 2.f));
	pallete = new TileManager({ 1,1 }, D3DXVECTOR2(52.f, 52.f), D3DXVECTOR2(map->GetMapSize().x * (defaultTileSize.x), defaultTileSize.y / 2.f ));*/

	TileManager::SetMapInfo(defaultMapSize, defaultTileSize, D3DXVECTOR2(0.f, 0.f));
	TileManager::SetTexture();
	map = new TileManager;

	TileManager::SetMapInfo({ 1,1 }, defaultTileSize, D3DXVECTOR2(520.f, 520.f));
	TileManager::SetTexture();
	pallete = new TileManager;

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("..//_Resources//TTF//Maplestory Light.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());

	_RenderPool->Request(this, RenderManager::Layer::Imgui);

	MapSize[0] = 1;
	MapSize[1] = 1;
	oldMapSize[0] = 1;
	oldMapSize[1] = 1;
}

MapTool::~MapTool()
{
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
}

void MapTool::Init()
{
}

void MapTool::ControllUpdate()
{
}

void MapTool::Update(float tick)
{
	if (oldMapSize[0] != MapSize[0] || oldMapSize[1] != MapSize[1])
	{
		map->SetMapSize({ MapSize[0], MapSize[1] });
		oldMapSize[0] = MapSize[0];
		oldMapSize[1] = MapSize[1];
	}

	if (Keyboard::Get()->Down(VK_LBUTTON))
	{
		TileNode* tempNode = isInCollision();

		if (tempNode != nullptr)
		{
			
			//ProcessSetMap(tempNode);
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
		
		//ImGui::SliderInt2("Map Size", MapSize, 5, 100);
		
		ImGui::InputInt2("Map Size", MapSize, ImGuiInputTextFlags_EnterReturnsTrue);
	}
	ImGui::End();
}

TileNode* MapTool::isInCollision()
{
	vector<TileNode*> tempMapArr = map->GetArray();
	vector<TileNode*>::iterator vecIter = tempMapArr.begin(), vecEnd = tempMapArr.end();

	for (; vecIter != vecEnd; ++vecIter)
	{
		if (Math::IsPointInAABB((*vecIter)->GetRect(), CAMERA->GetMousePos()))
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