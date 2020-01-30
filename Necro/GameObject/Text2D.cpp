#include "stdafx.h"
#include "Text2D.h"



Text2D::Text2D(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	brush = nullptr;
	format = nullptr;
	dwLayout = nullptr;

	position = D3DXVECTOR2(0, 0);
	rc = FloatRect(position, D3DXVECTOR2(100, 100), Pivot::CENTER);
	fontSize = 15;
	font = L"¸¼Àº°íµñ";
	align = DWRITE_TEXT_ALIGNMENT_CENTER;
	layer = RenderManager::Layer::GameText;
}

Text2D::~Text2D()
{
}

void Text2D::Init()
{
}

void Text2D::Release()
{
	brush->Release();
	format->Release();
	dwLayout->Release();
	
	_RenderPool->Remove(this, layer);

}

void Text2D::Update(float tick)
{

}

void Text2D::Render()
{
	if (text.empty() != false)
		p2DRenderer->GetRenderTarget()->DrawTextLayout(D2D1::Point2F(position.x, position.y), dwLayout, brush);
}

void Text2D::Setting(wstring str, TextManager::TextDesc desc)
{
	text = str;

	font = desc.Font;
	fontSize = desc.FontSize;
	CreateFormat();

	rc = desc.Area;
	CreateLayout();

	SetAlign(desc.Align);

	color = desc.Color;
	CreateBrush();

	layer = desc.Layer;
	_RenderPool->Request(this, layer);

}

void Text2D::SetText(string str)
{
	text = String::StringToWString(str);
	CreateLayout();
}

void Text2D::SetText(wstring str)
{
	text = str;
	CreateLayout();
}

void Text2D::SetColor(D3DXCOLOR c)
{
	color = c;
	CreateBrush();
}

void Text2D::SetAlign(DWRITE_TEXT_ALIGNMENT align)
{
	this->align = align;
	if (dwLayout)
		dwLayout->SetTextAlignment(align);
}

void Text2D::SetPosition(D3DXVECTOR2 pos)
{
	position = pos;
	rc.Update(position, size, Pivot::CENTER);
}

void Text2D::SetLayoutSize(D3DXVECTOR2 size)
{
	this->size = size;
	rc.Update(position, size, Pivot::CENTER);
	CreateLayout();
}

void Text2D::SetFontSize(float size)
{
	fontSize = size;
	CreateFormat();
	CreateLayout();
}


void Text2D::CreateLayout()
{
	p2DRenderer->GetDWriteFactory()->CreateTextLayout(
		text.c_str(),
		text.length(),
		format,
		(float)(rc.right - rc.left),
		(float)(rc.bottom - rc.top),
		&dwLayout
	);

	SetAlign(align);
}

void Text2D::CreateBrush()
{
	if (brush != nullptr)
		brush->Release();

	p2DRenderer->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);
}

void Text2D::CreateFormat()
{
	if (format != nullptr)
		format->Release();

	p2DRenderer->GetDWriteFactory()->CreateTextFormat(
		font.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"ko",
		&format
	);
}

