#pragma once

namespace DefaultBrush
{
	enum Enum
	{
		white = 0, black, yello, red, blue, green, gray, end
	};
}



class D2DRenderer
{
	SingletonHeader(D2DRenderer)
public:
	
	void Create2DBuffer();
	void BeginDraw();
	void EndDraw();
	void BeginDrawWithoutClear();

	HRESULT AddTextFormat(wstring fontname, float size);

	ID2D1Bitmap* CreateD2DBitmapFromFile(wstring file);


	ID2D1RenderTarget* GetRenderTarget() { return d2dRenderTarget; }
	ID2D1DeviceContext* GetDeviceContext() { return d2dDeviceContext; }
private:
	typedef unordered_map<wstring, IDWriteTextFormat*> mapTextList;
	typedef unordered_map<wstring, IDWriteTextFormat*>::iterator mapTextIter;

private:
	//== 2dRenderer
	ID2D1Factory1* d2dFactory;
	ID2D1RenderTarget * d2dRenderTarget;

	IWICImagingFactory* wicFactory;
	IDWriteFactory* dwFactory;

	ID2D1Device* d2dDevice;
	ID2D1DeviceContext* d2dDeviceContext;

	//텍스트레이아웃
	IDWriteTextLayout* dwLayout;
	ID2D1SolidColorBrush*	dwDefaultBrush[DefaultBrush::end];

	//텍스트 출력 스토리지
	mapTextList		dwTextFormats;
	
public:
	//텍스트 출력 (기본 브러쉬 사용)
	void DrawText2D(int x, int y, wstring text, int size, DefaultBrush::Enum defaultBrush = DefaultBrush::black, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"맑은고딕");
	//텍스트 출력 (원하는 색상과 알파값으로 브러쉬 생성해서 출력)
	void DrawText2D(int x, int y, wstring text, COLORREF rgb, float alpha, int size, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"맑은고딕");
	//텍스트 필드 출력 (기본 브러쉬 사용)
	void DrawTextField(int x, int y, wstring text, int size, int width, int height, DefaultBrush::Enum defaultBrush = DefaultBrush::black, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"맑은고딕");
	//텍스트 필드 출력 (원하는 색상과 알파값으로 브러쉬 생성해서 출력)
	void DrawTextField(int x, int y, wstring text, COLORREF rgb, int size, int width, int height, float alpha = 1.0f, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"맑은고딕");

	//==============================================================
	// ## 도형 그리기 함수 ##
	void DrawLine(D2D1::ColorF::Enum color, float alpha, D3DXVECTOR2 start, D3DXVECTOR2 end,  float strokeWidth = 1);
	void DrawLine(D3DXVECTOR2 start, D3DXVECTOR2 end, DefaultBrush::Enum defaultBrush = DefaultBrush::black, float strokeWidth = 1);
	void DrawRectangle(RECT rc, D2D1::ColorF::Enum color, float alpha,float strokeWidth = 1);
	void DrawRectangle(RECT rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black,float strokeWidth = 1);
	void DrawEllipse(RECT rc, D2D1::ColorF::Enum color, float alpha,  float strokeWidth = 1);
	void DrawEllipse(RECT rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black, float strokeWidth = 1);
	void FillRectangle(RECT rc, D2D1::ColorF::Enum color, float alpha);
	void FillRectangle(RECT rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black);
	void FillEllipse(RECT rc, D2D1::ColorF::Enum color, float alpha);
	void FillEllipse(RECT rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black);

	void DrawRectangle(FloatRect rc, D2D1::ColorF::Enum color, float alpha, float strokeWidth = 1);
	void DrawRectangle(FloatRect rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black, float strokeWidth = 1);
	void DrawEllipse(FloatRect rc, D2D1::ColorF::Enum color, float alpha, float strokeWidth = 1);
	void DrawEllipse(FloatRect rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black,float strokeWidth = 1);
	void FillRectangle(FloatRect rc, D2D1::ColorF::Enum color, float alpha);
	void FillRectangle(FloatRect rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black);
	void FillEllipse(FloatRect rc, D2D1::ColorF::Enum color, float alpha);
	void FillEllipse(FloatRect rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black);

	//==============================================================


	void DrawRectangle(D2D1_RECT_F rc, D2D1::ColorF::Enum color, float alpha, float strokeWidth = 1);
	void DrawRectangle(D2D1_RECT_F rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black, float strokeWidth = 1);

};

#define p2DRenderer D2DRenderer::Get()
#define DeviceContext2D D2DRenderer::Get()->GetDeviceContext()