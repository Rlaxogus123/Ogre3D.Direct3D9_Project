#include "DXUT.h"
#include "Font2D.h"
#include "FontRenderer.h"

USING(Tipp7)

Font2D::Font2D()
{
	memset(buff, '\0', sizeof(buff));
	D3DXCreateFont(DXUTGetD3D9Device(), 20, 0, 700, 1, 0, 1, 0, 0, 0 | FF_DONTCARE, L"Arial", &font);
	FontRenderer::GetInstance()->AddFont(this);
}

Font2D::Font2D(LPCWSTR path, float scale, float weight, Vector2 pos, Color co)
{
	position = Vector3(pos.x, pos.y, 0);
	color = co;
	D3DXCreateFont(DXUTGetD3D9Device(), 20 * scale, 0, weight, 1, 0, 1, 0, 0, 0 | FF_DONTCARE, path, &font);
	FontRenderer::GetInstance()->AddFont(this);
}

void Font2D::SetString(char* string)
{
	sprintf(buff, string);
}

void Font2D::Render()
{
	if (!activeSelf()) return;
	if (font == nullptr) return;

	RECT r;
	r = { (long)position.x, (long)position.y, 0, 0 };
	font->DrawTextA(nullptr, buff, -1, &r, DT_NOCLIP, color);
}

void Font2D::CreateMyFont(float scale, float weight, LPCWSTR path)
{
	D3DXCreateFont(DXUTGetD3D9Device(), 20 * scale, 0, weight, 1, 0, 1, 0, 0, 0 | FF_DONTCARE, path, &font);
}