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
	D3DXMATRIX matWorld;

	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	DEVICE->GetTransform(D3DTS_WORLD, &matWorld);

	D3DXMATRIX matWorldView = *D3DXMatrixMultiply(&matWorldView, &matWorld, &matView);
	D3DXMATRIX matWorldViewProj = *D3DXMatrixMultiply(&matWorldViewProj, &matWorldView, &matProj);

	effect->SetMatrix((D3DXHANDLE)"gWorldMatrix", &matWorld);
	effect->SetMatrix((D3DXHANDLE)"gWorldViewProjMatrix", &matWorldViewProj);

	D3DXMATRIX invView = *D3DXMatrixInverse(&invView, NULL, &matView);
	Vector4 camPos = Vector4(invView._41, invView._42, invView._43, 1);	

	effect->SetVector((D3DXHANDLE)"gCameraPosition", &camPos);
}

Resources* Shader::Clone(void)
{
	return new Shader(*this);
}

void Shader::Exit(void)
{
	SAFE_RELEASE(effect);
}
