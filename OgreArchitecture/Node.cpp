#include "DXUT.h"
#include "Node.h"

USING(Tipp7)

void Node::setPosition(const float x, const float y, const float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
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

D3DXMATRIX& Node::GetWorldMatrix(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale) const
{
	D3DXMATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, _position.x, _position.y, _position.z);

	D3DXMATRIX mRotX;
	D3DXMATRIX mRotY;
	D3DXMATRIX mRotZ;
	D3DXMatrixRotationX(&mRotX, D3DXToRadian(_rotation.x));
	D3DXMatrixRotationY(&mRotY, D3DXToRadian(_rotation.y));
	D3DXMatrixRotationZ(&mRotZ, D3DXToRadian(_rotation.z));

	D3DXMATRIX mEulerAngle = mRotZ * mRotX * mRotY;

	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, _scale.x, _scale.y, _scale.z);

	// 이동 -> 회전 -> 변환
	return mScale * mEulerAngle * mTranslate;
}

D3DXMATRIX& Node::GetMatrix() const
{
	D3DXMATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, position.x, position.y, position.z);

	D3DXMATRIX mRotX;
	D3DXMATRIX mRotY;
	D3DXMATRIX mRotZ;
	D3DXMatrixRotationX(&mRotX, D3DXToRadian(rotation.x));
	D3DXMatrixRotationY(&mRotY, D3DXToRadian(rotation.y));
	D3DXMatrixRotationZ(&mRotZ, D3DXToRadian(rotation.z));

	D3DXMATRIX mEulerAngle = mRotZ * mRotX * mRotY;

	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);

	// 이동 -> 회전 -> 변환
	return mScale * mEulerAngle * mTranslate;
}
void Node::Update(void)
{
	if (parent != nullptr)
		worldToMatrix = parent->GetMatrix() * GetWorldMatrix(position, rotation, scale);
	else worldToMatrix = GetWorldMatrix(position, rotation, scale);

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
