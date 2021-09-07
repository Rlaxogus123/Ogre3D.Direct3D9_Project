#pragma once
#include "Node.h"

NAMESPACE(Tipp7)

class Font2D : public Node
{
public:
	Font2D();
	Font2D(LPCWSTR path, float scale = 1, float weight = 700, Vector2 pos = { 0,0 }, Color co = Color(1, 1, 1, 1));
	virtual ~Font2D() {};

	string fontName = "default";
	Color color = Color(1,1,1,1);
	LPD3DXFONT font;

	char buff[255];

	void SetString(char* string);
	void Render() override;
	void CreateMyFont(float scale, float weight, LPCWSTR path);
};

END