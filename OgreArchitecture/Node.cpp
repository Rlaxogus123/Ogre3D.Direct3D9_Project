#include "DXUT.h"
#include "Node.h"

USING(Tipp7)

void Node::createQuaternion(void)
{
	matQuaternion = new D3DXMATRIX();
	D3DXMatrixIdentity(matQuaternion);
}

void Node::setDirection(const Vector3 _dir)
{

}

void Node::setTranslate(const float x, const float y, const float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Node::setTranslate(const Vector3 _vec)
{
	position += _vec;
}

void Node::setPosition(const float x, const float y, const float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Node::setPosition(const Vector3 _vec)
{
	position = _vec;
}

void Node::setScale(const float x, const float y, const float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void Node::yaw(const float amount)
{
	rotation.y = amount;
}

void Node::pitch(const float amount)
{
	rotation.x = amount;
}

void Node::roll(const float amount)
{
	rotation.z = amount;
}

D3DXMATRIX& Node::GetMatrix() const
{
	D3DXMATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, position.x, position.y, position.z);

	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
	D3DXMATRIX mEulerAngle;

	if (matQuaternion != nullptr)
	{
		mEulerAngle = *matQuaternion;
	}
	else
	{
		D3DXMATRIX mRotX;
		D3DXMATRIX mRotY;
		D3DXMATRIX mRotZ;
		D3DXMatrixRotationX(&mRotX, D3DXToRadian(rotation.x));
		D3DXMatrixRotationY(&mRotY, D3DXToRadian(rotation.y));
		D3DXMatrixRotationZ(&mRotZ, D3DXToRadian(rotation.z));
		mEulerAngle = mRotZ * mRotX * mRotY;
	}

	// 이동 -> 회전 -> 변환
	if (parent != nullptr)
		return (mScale * mEulerAngle * mTranslate) * parent->GetMatrix();
	return mScale * mEulerAngle * mTranslate;
}

D3DXMATRIX& Node::GetPureMatrix() const
{
	D3DXMATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, position.x, position.y, position.z);
	D3DXMATRIX mEulerAngle;

	if (matQuaternion != nullptr)
	{
		mEulerAngle = *matQuaternion;
	}
	else
	{
		D3DXMATRIX mRotX;
		D3DXMATRIX mRotY;
		D3DXMATRIX mRotZ;
		D3DXMatrixRotationX(&mRotX, D3DXToRadian(rotation.x));
		D3DXMatrixRotationY(&mRotY, D3DXToRadian(rotation.y));
		D3DXMatrixRotationZ(&mRotZ, D3DXToRadian(rotation.z));
		mEulerAngle = mRotZ * mRotX * mRotY;
	}

	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);

	// 이동 -> 회전 -> 변환
	return mScale * mEulerAngle * mTranslate;
}

D3DXMATRIX& Node::GetTransMatrix() const
{
	D3DXMATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, position.x, position.y, position.z);

	D3DXMATRIX mRotX;
	D3DXMATRIX mRotY;
	D3DXMATRIX mRotZ;
	D3DXMatrixRotationX(&mRotX, D3DXToRadian(0));
	D3DXMatrixRotationY(&mRotY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&mRotZ, D3DXToRadian(0));

	D3DXMATRIX mEulerAngle = mRotZ * mRotX * mRotY;

	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, 1, 1, 1);

	// 이동 -> 회전 -> 변환
	if (parent != nullptr)
		return (mScale * mEulerAngle * mTranslate) * parent->GetMatrix();
	return mScale * mEulerAngle * mTranslate;
}

D3DXMATRIX& Node::GetEulerMatrix() const
{
	D3DXMATRIX mRotX;
	D3DXMATRIX mRotY;
	D3DXMATRIX mRotZ;
	D3DXMatrixRotationX(&mRotX, D3DXToRadian(rotation.x));
	D3DXMatrixRotationY(&mRotY, D3DXToRadian(rotation.y));
	D3DXMatrixRotationZ(&mRotZ, D3DXToRadian(rotation.z));

	if (parent != nullptr)
		return (mRotZ * mRotX * mRotY) * parent->GetEulerMatrix();
	return mRotZ * mRotX * mRotY;
}

void Node::Update(void)
{
	foward = { 0,0,1 };
	up = { 0,1,0 };
	right = { 1,0,0 };
	D3DXVec3TransformCoord(&foward, &foward, &GetEulerMatrix());
	D3DXVec3TransformCoord(&up, &up, &GetEulerMatrix());
	D3DXVec3TransformCoord(&right, &right, &GetEulerMatrix());

	for (auto& it : childgroup)
	{
		if (it->activeSelf())
			it->Update();
	}
}

void Node::Render(void)
{
	for (auto& it : childgroup)
	{
		if (it->activeSelf())
			it->Render();
	}
}

void Node::Exit(void)
{
}
