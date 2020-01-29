#pragma once



class Text2D;
class TextManager
{
	friend class SceneBase;
public:
	void TextGame(Text2D::TextDesc desc);
	void TextUI();

private:
	vector<Text2D*> freeList;
	vector<Text2D*> textGame;
	vector<Text2D*> textUI;

	TextManager() {}
	~TextManager() {}

};

#define _TextManager TextManager::Get()
