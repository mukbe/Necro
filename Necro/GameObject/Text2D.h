#pragma once


class Text2D : public GameObject
{
public:
	enum TextInterpolationType : short
	{
		Interpolate_None = 0,
		Interpolate_Position = 1 << 0,
		Interpolate_Alpha = 1 << 1,
		Interpolate_Color = 1 << 2,
	};

	struct TextInterpolateDesc
	{
		TextInterpolationType Type;
		D3DXVECTOR2 DestPosition;
		D3DXCOLOR DestColor;
		float ShownTime;
		TextInterpolateDesc()
			:Type(Interpolate_None), DestPosition(0, 0), DestColor(0, 0, 0, 0), ShownTime(-500) {}
	};

	struct TextDesc
	{
		wstring Font;
		float FontSize;
		
		RenderManager::Layer Layer;

		FloatRect Area;
		DWRITE_TEXT_ALIGNMENT Align;

		D3DXCOLOR Color;

		D3DXVECTOR2 Position;

		TextInterpolateDesc LerpDesc;
		TextDesc()
			: Font(L"¸¼Àº°íµñ"), FontSize(15.f), Align(DWRITE_TEXT_ALIGNMENT_LEADING), Color(1, 1, 1, 1), Position(0, 0) {}
	};

	Text2D(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Text2D();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();

	void Setting(wstring str, TextDesc desc);

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

//class Interpolation
//{
//public:
//
//public:
//	Interpolation(TextInterpolationType type, D3DXVECTOR2 destPos, D3DXCOLOR destColor) {}
//	virtual~Interpolation() {}
//
//	void Update(Text2D& myText);
//
//private:
//	D3DXVECTOR2 destPosition;
//	D3DXCOLOR destColor;
//	TextInterpolationType interpolateType;
//};
