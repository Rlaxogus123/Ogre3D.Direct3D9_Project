#pragma once
#include "Singleton.h"
#include "Font2D.h"

NAMESPACE(Tipp7)

class FontRenderer : public Singleton<FontRenderer>
{
private:
	list<Font2D*> fontList;
public:
	void AddFont(Font2D* font);
	Font2D* GetFont(string fontName);

	void RenderFont();
	void Exit();
};

END