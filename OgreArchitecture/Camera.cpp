#include "DXUT.h"
#include "Camera.h"
#include "MyMath.h"
#include "Root.h"

USING(MyMath)
USING(Tipp7)

Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{
	vUp = { 0.0f, 1.0f, 0.0f };
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 3, 1.6f, 0.9f, 5000.0f);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Camera::Update(void)
{
}

void Camera::Render(void)
{
	vLookat = { 0,0,1 };
	Vector3 pos = {0,0,0};
	D3DXVec3TransformCoord(&vLookat, &vLookat, &node->GetMatrix());
	D3DXVec3TransformCoord(&pos, &pos, &node->GetMatrix());

	D3DXVec3Normalize(&vView, &(vLookat - pos));
	D3DXVec3Cross(&vCross, &vUp, &vView);
	
	D3DXMatrixLookAtLH(&matView, &pos, &vLookat, &vUp);
	D3DXMatrixInverse(&matBill, NULL, &matView);
	matBill._41 = 0;
	matBill._42 = 0;
	matBill._43 = 0;
	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::Exit(void)
{
	cout << "!! Camera Released !! : " << movableName << endl;
}