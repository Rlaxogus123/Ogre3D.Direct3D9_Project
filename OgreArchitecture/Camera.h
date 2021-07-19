#pragma once

#include "MovableObject.h"

NAMESPACE(Tipp7)

class Camera
	: public MovableObject
{
public:
	explicit Camera(void);
	virtual ~Camera(void);

	Vector3 vUp; // 카메라의 상방벡터
	Vector3 vView;// 카메라가 향하는 단위방향벡터	
	Vector3 vCross; // 카메라의 측면벡터cross ( view,up )
	Vector3 vLookat = { 0,0,-1 }; // 카메라가 바라보는 방향

	D3DXMATRIX matView; // 카메라 행렬
	D3DXMATRIX matBill; // 빌보드 행렬 ( 역행렬 )

	void Init(void) override;
	void Update(void) override;
	void Render(void) override;
	void Exit(void) override;
};

END