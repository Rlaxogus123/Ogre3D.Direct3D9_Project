#include "DXUT.h"
#include "Camera.h"

USING(Tipp7)

Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{
}

void Camera::Update(void)
{
}

void Camera::Render(void)
{
	D3DXVec3TransformCoord(&vLookat, &vLookat, &node->GetMatrix());
	D3DXVec3Normalize(&vView, &(vLookat - node->position));
	D3DXVec3Cross(&vCross, &vUp, &vView);
	D3DXMatrixLookAtLH(&matView, &node->position, &vLookat, &vUp);
	D3DXMatrixInverse(&matBill, NULL, &matView);
	matBill._41 = 0;
	matBill._42 = 0;
	matBill._43 = 0;

	DXUTGetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &matView);
	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	cout << "Camera Rendering" << endl;
}

void Camera::Exit(void)
{
}