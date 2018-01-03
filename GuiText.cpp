#include "Precompiled.h"

GuiText::GuiText(std::string text)
{
    this->text = text;
}

GuiText::~GuiText()
{
}

void GuiText::Init(IDirect3DDevice9* pDevice)
{
    D3DXFONT_DESC fontDesc;
	fontDesc.Height = 24;
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	strcpy(fontDesc.FaceName, "Times New Roman");
	D3DXCreateFontIndirect(pDevice, &fontDesc, &font);
}

void GuiText::Draw()
{
	RECT R = { (LONG)position.x, (LONG)position.y, (LONG)position.x + 100, (LONG)position.y + 24 };
	font->DrawText(0, this->text.c_str(), -1, &R, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void GuiText::Destroy()
{
    if (font != NULL) {
		font->Release();
		font = NULL;
	}
}
