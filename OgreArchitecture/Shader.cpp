#include "DXUT.h"
#include "Shader.h"

USING(Tipp7)

Shader::Shader(const Shader& copy) :
	Resources(copy),
	effect(copy.effect)
{
	effect->AddRef();
}

void Shader::Render(const D3DXMATRIX& _matWorld)
{
	D3DXMATRIX matView;
	D3DXMATRIX matProj;

	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);

	effect->SetMatrix((D3DXHANDLE)"gWorldMatrix", &_matWorld);
	effect->SetMatrix((D3DXHANDLE)"gViewMatrix", &matView);
	effect->SetMatrix((D3DXHANDLE)"gProjectionMatrix", &matProj);
}

Resources* Shader::Clone(void)
{
	return new Shader(*this);
}

void Shader::Exit(void)
{
	SAFE_RELEASE(effect);
}
