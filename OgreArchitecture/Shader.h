#pragma once

#include "Resources.h"

NAMESPACE(Tipp7)

class Shader
	: public Resources
{
public:
	explicit Shader(void) {};
	explicit Shader(const Shader& copy);
	virtual ~Shader(void) {};

	LPD3DXEFFECT effect;

	void Render(const D3DXMATRIX& _matWorld);

	Resources* Clone(void) override;
	void Exit(void) override;
};

END