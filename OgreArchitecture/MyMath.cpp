#include "DXUT.h"
#include "MyMath.h"

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式//
//	The owner of this library is 'Tipp7'
//
//  Contact
//    Ⅱ Email : acekimcp@gmail.com
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式//
NAMESPACE(MyMath)

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

FLOAT myD3DXVec2Length(Vector2* pOut)
{
	return sqrt(pOut->x * pOut->x + pOut->y * pOut->y);
}

FLOAT myD3DXVec3Length(Vector3* pOut)
{
	return sqrt(pOut->x * pOut->x + pOut->y * pOut->y + pOut->z * pOut->z);
}

Vector2 myD3DXVec2Normalize(Vector2* pOut, const Vector2* p1)
{
	pOut->x = pOut->x / myD3DXVec2Length(pOut);
	pOut->y = pOut->y / myD3DXVec2Length(pOut);
	return *pOut;
}

Vector3 myD3DXVec3Normalize(Vector3* pOut, const Vector3* p1)
{
	pOut->x = pOut->x / myD3DXVec3Length(pOut);
	pOut->y = pOut->y / myD3DXVec3Length(pOut);
	pOut->z = pOut->z / myD3DXVec3Length(pOut);
	return *pOut;
}

FLOAT myD3DXVec2Dot(const Vector2* p1, const Vector2* p2)
{
	return p1->x * p2->x + p1->y * p2->y;
}

FLOAT myD3DXVec3Dot(const Vector3* p1, const Vector3* p2)
{
	return p1->x * p2->x + p1->y * p2->y + p1->z * p2->z;
}

Vector3 myD3DXVec3Cross(Vector3* pOut, const Vector3 p1, const Vector3 p2)
{
	pOut->x = (p1.y * p2.z) - (p2.y * p1.z);
	pOut->y = (p1.z * p2.x) - (p2.z * p1.x);
	pOut->z = (p1.x * p2.y) - (p2.x * p1.y);
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

END