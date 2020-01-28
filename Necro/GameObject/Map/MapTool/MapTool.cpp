#include "MapTool.h"
#include "./Systems/Manage/TileManager.h""
#include "./GameObject/Map/TileNode.h"
#include "Pallete.h"

MapTool::MapTool(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	TileManager::SetMapInfo(defaultMapSize, defaultTileSize, D3DXVECTOR2(defaultTileSize.x / 2.f, defaultTileSize.y / 2.f));
	map = new TileManager;

	pallete = new Pallete(D3DXVECTOR2(defaultMapSize.x * defaultTileSize.x, 0.f));

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("..//_Resources//TTF//Maplestory Light.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());

	_RenderPool->Request(this, RenderManager::Layer::Imgui);

	MapSize[0] = 1;
	MapSize[1] = 1;
	oldMapSize[0] = 1;
	oldMapSize[1] = 1;

	map->CreateMap();
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
			ProcessSetMap(tempNode);
		}
	}

	switch (palleteType)
	{
	case ObjectAll:
		break;
	case ObjectTerrain:
		pallete->ReleasePallete();
		pallete->CreatePallete(ObjectTerrain, D3DXVECTOR2(50, 50));
		break;
	case ObjectPlayer:
		pallete->ReleasePallete();
		pallete->CreatePallete(ObjectPlayer, D3DXVECTOR2(50, 50));
		break;
	case ObjectMonster:
		pallete->ReleasePallete();
		pallete->CreatePallete(ObjectMonster, D3DXVECTOR2(50, 50));
		break;
	case ObjectItem:
		pallete->ReleasePallete();
		pallete->CreatePallete(ObjectItem, D3DXVECTOR2(50, 50));
		break;
	case ObjectNPC:
		pallete->ReleasePallete();
		pallete->CreatePallete(ObjectNPC, D3DXVECTOR2(50, 50));
		break;
	case ObjectWall:
		pallete->ReleasePallete();
		pallete->CreatePallete(ObjectWall, D3DXVECTOR2(50, 50));
		break;
	default:
		pallete->ReleasePallete();
		break;
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
	case ObjectAll:
		currentPalleteMode = "AllObjects";
		break;
	case ObjectTerrain:
		currentPalleteMode = "Terrain";
		break;
	case ObjectPlayer:
		currentPalleteMode = "Player";
		break;
	case ObjectMonster:
		currentPalleteMode = "Monster";
		break;
	case ObjectItem:
		currentPalleteMode = "Item";
		break;
	case ObjectNPC:
		currentPalleteMode = "NPC";
		break;
	case ObjectWall:
		currentPalleteMode = "Wall";
		break;
	default:
		currentPalleteMode = "None Selected";
		break;
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
		if (ImGui::Button("All", ImVec2(100, 50)))
		{
			palleteType = ObjectAll;
		}
		ImGui::SameLine();
		if (ImGui::Button("Terrain", ImVec2(100, 50)))
		{
			palleteType = ObjectTerrain;
		}
		if (ImGui::Button("Player", ImVec2(100, 50)))
		{
			palleteType = ObjectPlayer;
		}
		ImGui::SameLine();
		if (ImGui::Button("Monster", ImVec2(100, 50)))
		{
			palleteType = ObjectMonster;
		}
		ImGui::SameLine();
		if (ImGui::Button("Item", ImVec2(100, 50)))
		{
			ImGui::SameLine();
			palleteType = ObjectItem;
		}
		if (ImGui::Button("NPC", ImVec2(100, 50)))
		{
			palleteType = ObjectNPC;
		}
		ImGui::SameLine();
		if (ImGui::Button("Wall", ImVec2(100, 50)))
		{
			palleteType = ObjectWall;
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