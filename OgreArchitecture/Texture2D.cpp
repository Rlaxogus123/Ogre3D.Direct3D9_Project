#include "DXUT.h"
#include "Texture2D.h"

USING(Tipp7)

Texture2D::Texture2D(const Texture2D& copy)
	: Resources(copy),
	texture(copy.texture)
{
	texture->AddRef();
}

Resources* Texture2D::Clone(void)
{
	return new Texture2D(*this);
}

void Texture2D::Exit(void)
{
	SAFE_RELEASE(texture);
}
