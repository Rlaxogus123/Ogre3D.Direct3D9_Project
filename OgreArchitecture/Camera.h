#pragma once

#include "MovableObject.h"

NAMESPACE(Tipp7)

class Camera
	: public MovableObject
{
public:
	explicit Camera(void);
	virtual ~Camera(void);

	Vector3 vUp; // ī�޶��� ��溤��
	Vector3 vView;// ī�޶� ���ϴ� �������⺤��	
	Vector3 vCross; // ī�޶��� ���麤��cross ( view,up )
	Vector3 vLookat = { 0,0,-1 }; // ī�޶� �ٶ󺸴� ����

	D3DXMATRIX matView; // ī�޶� ���
	D3DXMATRIX matBill; // ������ ��� ( ����� )

	void Init(void) override;
	void Update(void) override;
	void Render(void) override;
	void Exit(void) override;
};

END