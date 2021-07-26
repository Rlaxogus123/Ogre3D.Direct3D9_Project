#include "DXUT.h"
#include "Node.h"

USING(Tipp7)

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
	if(parent != nullptr)
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
