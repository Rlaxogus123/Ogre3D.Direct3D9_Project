#pragma once

#include "Resources.h"

NAMESPACE(Tipp7)

class Texture2D
	: public Resources
{
public:
	explicit Texture2D() {};
	explicit Texture2D(const Texture2D& copy);
	virtual ~Texture2D() {};

	LPDIRECT3DTEXTURE9 texture = nullptr;
	D3DXIMAGE_INFO info;

	Resources* Clone(void) override;
	void Exit(void) override;
};

END