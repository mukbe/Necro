#pragma once


class Text2D : public GameObject
{
public:

	Text2D(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Text2D();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();

	void Setting(wstring str, TextManager::TextDesc desc);

	void SetText(string str);
	void SetText(wstring str);
	

	void SetColor(D3DXCOLOR c);
	void SetAlign(DWRITE_TEXT_ALIGNMENT align);
	void SetPosition(D3DXVECTOR2 pos);
	void SetLayoutSize(D3DXVECTOR2 size);
	void SetFontSize(float size);
	
private:
	wstring text;
	RenderManager::Layer layer;

	D3DXCOLOR color;
	DWRITE_TEXT_ALIGNMENT align;
	wstring font;
	float fontSize;

	ID2D1SolidColorBrush* brush;
	IDWriteTextLayout* dwLayout;
	IDWriteTextFormat* format;

	void CreateLayout();
	void CreateBrush();
	void CreateFormat();

};
