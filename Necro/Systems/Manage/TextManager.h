#pragma once



class Text2D;
class TextManager
{
	friend class SceneBase;
public:
	struct TextDesc
	{
		wstring Font;
		float FontSize;

		RenderManager::Layer Layer;

		FloatRect Area;
		DWRITE_TEXT_ALIGNMENT Align;

		D3DXCOLOR Color;

		D3DXVECTOR2 Position;

		TextDesc()
			: Font(L"¸¼Àº°íµñ"), FontSize(15.f), Align(DWRITE_TEXT_ALIGNMENT_LEADING), Color(1, 1, 1, 1), Position(0, 0) {}
	};

	void TextGame(wstring str, TextManager::TextDesc desc);
	void TextUI();

private:
	queue<Text2D*> freeList;
	vector<Text2D*> textGame;
	vector<Text2D*> textUI;

	TextManager();
	~TextManager();

};

