#include "DXUT.h"
#include "MyMath.h"

//───────────────────────────────────────────────────────//
//	The Maker of this library is 'Tipp7'
//
//  Contact
//    ▶ Email : acekimcp@gmail.com
//───────────────────────────────────────────────────────//
NAMESPACE(MyMath)

FLOAT mysqrt(const FLOAT amount)
{
	FLOAT x1 = amount;
	FLOAT x2 = 0;
	for (int i = 0; i < 10; i++)
	{
		x2 = x1 - 1 / ((2 * x1) / (pow(x1, 2) - amount));
	}
	return x2;
}

FLOAT myFloatLerp(FLOAT* pOut, const FLOAT* a1, const FLOAT* a2, const FLOAT amount)
{
	// out = start + (end - start) * time;
	*pOut = *a1 + (*a2 - *a1) * amount;
	return *pOut;
}

Vector2 myD3DXVec2Lerp(Vector2* pOut, const Vector2* p1, const Vector2* p2, const FLOAT amount)
{
	myFloatLerp(&pOut->x, &p1->x, &p2->x, amount);
	myFloatLerp(&pOut->y, &p1->y, &p2->y, amount);
	return *pOut;
}

Vector3 myD3DXVec3Lerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT amount)
{
	myFloatLerp(&pOut->x, &p1->x, &p2->x, amount);
	myFloatLerp(&pOut->y, &p1->y, &p2->y, amount);
	myFloatLerp(&pOut->z, &p1->z, &p2->z, amount);
	return *pOut;
}

FLOAT myD3DXVec2Length(const Vector2* pOut)
{
	return sqrt(myD3DXVec2LengthSq(pOut));
}

FLOAT myD3DXVec2LengthSq(const Vector2* pOut)
{
	return (pOut->x * pOut->x) + (pOut->y * pOut->y);
}

FLOAT myD3DXVec3Length(const Vector3* pOut)
{
	return sqrt(myD3DXVec3LengthSq(pOut));
}

FLOAT myD3DXVec3LengthSq(const Vector3* pOut)
{
	return (pOut->x * pOut->x) + (pOut->y * pOut->y) + (pOut->z * pOut->z);
}

Vector2 myD3DXVec2Normalize(Vector2* pOut, const Vector2* p1)
{
	*pOut = *p1 / D3DXVec2Length(p1);
	return *pOut;
}

Vector3 myD3DXVec3Normalize(Vector3* pOut, const Vector3* p1)
{
	*pOut = *p1 / myD3DXVec3Length(p1);
	return *pOut;
}

FLOAT myD3DXVec2Dot(const Vector2* p1, const Vector2* p2)
{
	return (p1->x * p2->x) + (p1->y * p2->y);
}

FLOAT myD3DXVec3Dot(const Vector3* p1, const Vector3* p2)
{
	return (p1->x * p2->x) + (p1->y * p2->y) + (p1->z * p2->z);
}

Vector3 myD3DXVec3Cross(Vector3* pOut, const Vector3* p1, const Vector3* p2)
{
	pOut->x = (p1->y * p2->z) - (p2->y * p1->z);
	pOut->y = (p1->z * p2->x) - (p2->z * p1->x);
	pOut->z = (p1->x * p2->y) - (p2->x * p1->y);
	return *pOut;
}

Vector3 myD3DXVec3Slerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT time)
{
	// 각속도 w는 1초동안 각도∂을 움직였다.. 라는 의미를 가지게 됨. 따라서 1.0을 곱하는 것이 맞다.
	FLOAT w = acosf(myD3DXVec3Dot(p1, p2) / (pow(myD3DXVec3Length(p1),2))) * 1.0f;
	pOut->x = ((sin(w * (1 - time)) / sin(w)) * p1->x) + ((sin(w * time) / sin(w)) * p2->x);
	pOut->y = ((sin(w * (1 - time)) / sin(w)) * p1->y) + ((sin(w * time) / sin(w)) * p2->y);
	pOut->z = ((sin(w * (1 - time)) / sin(w)) * p1->z) + ((sin(w * time) / sin(w)) * p2->z);
	return *pOut;
}

void myD3DXMatrixShow(const D3DXMATRIX* pOut)
{
	cout << "[ " << pOut->_11 << " ]";
	cout << "[ " << pOut->_12 << " ]";
	cout << "[ " << pOut->_13 << " ]";
	cout << "[ " << pOut->_14 << " ]" << endl;
	cout << "[ " << pOut->_21 << " ]";
	cout << "[ " << pOut->_22 << " ]";
	cout << "[ " << pOut->_23 << " ]";
	cout << "[ " << pOut->_24 << " ]" << endl;
	cout << "[ " << pOut->_31 << " ]";
	cout << "[ " << pOut->_32 << " ]";
	cout << "[ " << pOut->_33 << " ]";
	cout << "[ " << pOut->_34 << " ]" << endl;
	cout << "[ " << pOut->_41 << " ]";
	cout << "[ " << pOut->_42 << " ]";
	cout << "[ " << pOut->_43 << " ]";
	cout << "[ " << pOut->_44 << " ]" << endl;
}

D3DXMATRIX myD3DXMatrixIdentity(D3DXMATRIX* pOut)	
{
	ZeroMemory(pOut, sizeof(D3DXMATRIX));
	pOut->_11 = 1;
	pOut->_22 = 1;
	pOut->_33 = 1;
	pOut->_44 = 1;
	return *pOut;
}

BOOL myD3DXMatrixIsIdentity(const D3DXMATRIX* pM)
{
	bool b = true;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j) {
				if (pM->m[i][j] != 1) b = false;
			} else {
				if (pM->m[i][j] != 0) b = false;
			}
		}
	}
	return b;
}

D3DXMATRIX myD3DXMatrixMultiply(D3DXMATRIX* pOut, const D3DXMATRIX* m1, const D3DXMATRIX* m2)
{
	return D3DXMATRIX();
}

D3DXQUATERNION* myD3DXQuaternionRotationAxis(D3DXQUATERNION* pOut, const Vector3* N, const FLOAT radian)
{
	Vector3 n = myD3DXVec3Normalize(&n, N);
	FLOAT s = cos(radian / 2.0f);
	Vector3 v = sin(radian / 2.0f) * n;
	*pOut = D3DXQUATERNION(v.x, v.y, v.z, s);
	return pOut;
}

D3DXQUATERNION* myD3DXQuaternionConjugate(D3DXQUATERNION* pOut, const D3DXQUATERNION* q)
{
	FLOAT s = q->w;
	Vector3 v(Vector3(q->x, q->y, q->z));
	Vector3 _v(v * -1);
	*pOut = D3DXQUATERNION(_v.x, _v.y, _v.z, s);
	return pOut;
}

FLOAT myD3DXQuaternionLengthSq(const D3DXQUATERNION* q)
{
	FLOAT s = q->w;
	Vector3 v(Vector3(q->x, q->y, q->z));

	return s * s + D3DXVec3LengthSq(&v);
}

FLOAT myD3DXQuaternionLength(const D3DXQUATERNION* q)
{
	return sqrt(myD3DXQuaternionLengthSq(q));
}

VOID myProjectileMotion(Vector3* pOut, const Vector3* p1, const Vector3* v, const FLOAT time)
{
	float angle = atan2(v->y, v->x);
	float power = myD3DXVec3Length(v);

	pOut->x = p1->x + (power * time * cos(angle));
	pOut->y = p1->y + ((power * time * sin(angle)) - (9.807f*(time*time)/2));
}

VOID myProjectileMotionFunction(Vector3* pOut, const Vector3* p1, const Vector3* v, const FLOAT time)
{
	float angle = atan2(v->y, v->x);
	float power = myD3DXVec3Length(v);

	pOut->x = power * time * cos(angle);
	pOut->y = (-9.807f / 2 * (power * power) * pow(cos(angle), 2)) * pow(pOut->x, 2) + (tan(angle) * pOut->x);
	return VOID();
}

END