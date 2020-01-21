#pragma once

enum ObjectType
{
	ObjectTypeBegin = 0,
	Player,
	Monster,
	Item,
	NPC,
	Wall,
	ObjectTypeEnd
};

class Pallete
{
public:
	Pallete();
	~ Pallete();

	void Init();

	void Release();

	void Update();

	void AddObject();
	void DeleteObject();

	void CreatePallete();
private:
	unordered_map<ObjectType, vector<GameObject*>> objectStorages;
	typedef vector<GameObject*> vecStorage;
};

