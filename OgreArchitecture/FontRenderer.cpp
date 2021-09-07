#include "DXUT.h"
#include "FontRenderer.h"

USING(Tipp7)

void FontRenderer::AddFont(Font2D* font)
{
	if (find(fontList.begin(), fontList.end(), font) != fontList.end())
	{
		cout << "Font is Already Added!";
		return;
	}
	fontList.push_back(font);
}

Font2D* FontRenderer::GetFont(string fontName)
{
	for (auto& it : fontList)
	{
		if (it->fontName._Equal(fontName));
			return it;
	}
	return nullptr;
}

void FontRenderer::RenderFont()
{
	for (auto& it : fontList)
		it->Render();
}

void FontRenderer::Exit()
{
	for (auto& it : fontList)
	{
		SAFE_RELEASE(it->font);
		SAFE_DELETE(it);
	}
	fontList.clear();
}
