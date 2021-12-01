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
	return FLOAT();
}

FLOAT myFloatLerp(FLOAT* pOut, const FLOAT* a1, const FLOAT* a2, const FLOAT amount)
{
	// out = start + (end - start) * time;
	*pOut = *a1 + (*a2 - *a1) * amount;
	return *pOut;
}

Vector2* myD3DXVec2Lerp(Vector2* pOut, const Vector2* p1, const Vector2* p2, const FLOAT amount)
{
	myFloatLerp(&pOut->x, &p1->x, &p2->x, amount);
	myFloatLerp(&pOut->y, &p1->y, &p2->y, amount);
	return pOut;
}

Vector3* myD3DXVec3Lerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT amount)
{
	myFloatLerp(&pOut->x, &p1->x, &p2->x, amount);
	myFloatLerp(&pOut->y, &p1->y, &p2->y, amount);
	myFloatLerp(&pOut->z, &p1->z, &p2->z, amount);
	return pOut;
}

FLOAT myD3DXVec2Length(const Vector2* pOut)
{
	return sqrt(myD3DXVec2LengthSq(pOut));
}

FLOAT myD3DXVec2LengthSq(const Vector2* pOut)
{
	return myD3DXVec2Dot(pOut, pOut);
}

VOID __ShowVector3(const Vector3* v, const string name)
{
	cout << "■ " << name << " ■" << endl;
	cout << "[ " << v->x << " ]";
	cout << "[ " << v->y << " ]";
	cout << "[ " << v->z << " ]" << endl;
}

FLOAT myD3DXVec3Length(const Vector3* pOut)
{
	return sqrt(myD3DXVec3LengthSq(pOut));
}

FLOAT myD3DXVec3LengthSq(const Vector3* pOut)
{
	return myD3DXVec3Dot(pOut, pOut);
}

Vector2* myD3DXVec2Normalize(Vector2* pOut, const Vector2* p1)
{
	*pOut = *p1 / D3DXVec2Length(p1);
	return pOut;
}

Vector3* myD3DXVec3Normalize(Vector3* pOut, const Vector3* p1)
{
	*pOut = *p1 / myD3DXVec3Length(p1);
	return pOut;
}

FLOAT myD3DXVec2Dot(const Vector2* p1, const Vector2* p2)
{
	return (p1->x * p2->x) + (p1->y * p2->y);
}

FLOAT myD3DXVec3Dot(const Vector3* p1, const Vector3* p2)
{
	return (p1->x * p2->x) + (p1->y * p2->y) + (p1->z * p2->z);
}

Vector3* myD3DXVec3Cross(Vector3* pOut, const Vector3* p1, const Vector3* p2)
{
	pOut->x = (p1->y * p2->z) - (p2->y * p1->z);
	pOut->y = (p1->z * p2->x) - (p2->z * p1->x);
	pOut->z = (p1->x * p2->y) - (p2->x * p1->y);
	return pOut;
}

Vector3 myD3DXVec3Cross(const Vector3* p1, const Vector3* p2)
{
	return Vector3((p1->y * p2->z) - (p2->y * p1->z), (p1->z * p2->x) - (p2->z * p1->x), (p1->x * p2->y) - (p2->x * p1->y));
}

Vector3* myD3DXVec3Slerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT time)
{
	// 각속도 w는 1초동안 각도∂을 움직였다.. 라는 의미를 가지게 됨.
	FLOAT theta = acosf(myD3DXVec3Dot(p1, p2) / myD3DXVec3LengthSq(p1));
	FLOAT omega = theta / 1.0f;
	FLOAT a = sin(omega * (1.0f - time));
	FLOAT b = sin(omega * time);
	*pOut = (a * (*p1) + b * (*p2)) / sin(omega * 1.0f);
	return pOut;
}

Vector3* __Vec3RotationAxis(Vector3* pOut, const Vector3* r, const Vector3* n, const FLOAT angle)
{
	// q * p * _q
	pOut->x = (cosf(angle) * r->x) + ((1 - cosf(angle)) * (myD3DXVec3Dot(n, r)) * n->x) + (sinf(angle) * (myD3DXVec3Cross(n, r).x));
	pOut->y = (cosf(angle) * r->y) + ((1 - cosf(angle)) * (myD3DXVec3Dot(n, r)) * n->y) + (sinf(angle) * (myD3DXVec3Cross(n, r).y));
	pOut->z = (cosf(angle) * r->z) + ((1 - cosf(angle)) * (myD3DXVec3Dot(n, r)) * n->z) + (sinf(angle) * (myD3DXVec3Cross(n, r).z));
	return pOut;
}

Vector3* myD3DXVec3Hermite(Vector3* pOut, const Vector3* p_0, const Vector3* T_0, const Vector3* p_1, const Vector3* T_1, FLOAT time)
{
	D3DXMATRIX A = {
		0,0,0,1,
		1,1,1,1,
		0,0,1,0,
		3,2,1,0
	};
	D3DXMATRIX C = {
		p_0->x,p_0->y,p_0->z,0,
		p_1->x,p_1->y,p_1->z,0,
		T_0->x,T_0->y,T_0->z,0,
		T_1->x,T_1->y,T_1->z,0
	};

	D3DXMATRIX mOut;
	D3DXMatrixInverse(&A, NULL, &A);
	D3DXMatrixMultiply(&mOut, &A, &C);

	Vector3 a, b, c, d;
	a = { mOut._11, mOut._12, mOut._13 };
	b = { mOut._21, mOut._22, mOut._23 };
	c = { mOut._31, mOut._32, mOut._33 };
	d = { mOut._41, mOut._42, mOut._43 };

	*pOut = a * pow(time, 3) + b * pow(time, 2) + (c * time) + d;
	return pOut;
}

Vector3* myD3DXVec3CatmullRom(Vector3* pOut, const Vector3* p_0, const Vector3* p_1, const Vector3* p_2, const Vector3* p_3, FLOAT time)
{
	Vector3 T_0 = (*p_2 - *p_0) / 2;
	Vector3 T_1 = (*p_3 - *p_1) / 2;
	
	myD3DXVec3Hermite(pOut, p_1, &T_0, p_2, &T_1, time);
	return pOut;
}

Vector3* myD3DXVec3KochanekBartels(Vector3* pOut, const Vector3* p_0, const Vector3* p_1, const Vector3* p_2, const Vector3* p_3, const FLOAT t, const FLOAT b, const FLOAT c, FLOAT time)
{
	Vector3 T_0 = 0.5f * (1.0f - t) * ((1.0f + b) * (1.0f - c) * (*p_1 - *p_0) + (1.0f - b) * (1.0 + c) * (*p_2 - *p_1));
	Vector3 T_1 = 0.5f * (1.0f - t) * ((1.0f + b) * (1.0f + c) * (*p_2 - *p_1) + (1.0f - b) * (1.0 - c) * (*p_3 - *p_2));

	myD3DXVec3Hermite(pOut, p_1, &T_0, p_2, &T_1, time);
	return pOut;
}

VOID __ShowMatrix(const D3DXMATRIX* m, const string name)
{
	cout << "■ " << name << " ■" << endl;
	cout << "[ " << m->_11 << " ]";
	cout << "[ " << m->_12 << " ]";
	cout << "[ " << m->_13 << " ]";
	cout << "[ " << m->_14 << " ]" << endl;
	cout << "[ " << m->_21 << " ]";
	cout << "[ " << m->_22 << " ]";
	cout << "[ " << m->_23 << " ]";
	cout << "[ " << m->_24 << " ]" << endl;
	cout << "[ " << m->_31 << " ]";
	cout << "[ " << m->_32 << " ]";
	cout << "[ " << m->_33 << " ]";
	cout << "[ " << m->_34 << " ]" << endl;
	cout << "[ " << m->_41 << " ]";
	cout << "[ " << m->_42 << " ]";
	cout << "[ " << m->_43 << " ]";
	cout << "[ " << m->_44 << " ]" << endl;
}

D3DXMATRIX* myD3DXMatrixIdentity(D3DXMATRIX* pOut)	
{
	ZeroMemory(pOut, sizeof(D3DXMATRIX));
	pOut->_11 = 1;
	pOut->_22 = 1;
	pOut->_33 = 1;
	pOut->_44 = 1;
	return pOut;
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

D3DXMATRIX* __MatrixRotationQuaternionAxis(D3DXMATRIX* pOut, const D3DXQUATERNION* q, const Vector3* axis)
{
	D3DXVECTOR3 y = *axis;
	D3DXVECTOR3 v(q->x, q->y, q->z);

	FLOAT angle = acosf(D3DXVec3Dot(&y, &v) / (D3DXVec3Length(&y) * D3DXVec3Length(&v)));

	D3DXVECTOR3 _axis;
	D3DXVec3Cross(&_axis, &y, &v);

	D3DXQUATERNION Q;
	D3DXQuaternionRotationAxis(&Q, &_axis, angle);

	D3DXMatrixRotationQuaternion(pOut, &Q);
	return pOut;
}

D3DXMATRIX* myD3DXMatrixMultiply(D3DXMATRIX* pOut, const D3DXMATRIX* m1, const D3DXMATRIX* m2)
{
	return &D3DXMATRIX();
}

D3DXMATRIX* myD3DXMatrixRotationAxis(D3DXMATRIX* pOut, const Vector3* axis, const FLOAT angle)
{
	//FLOAT a = axis->x;
	//FLOAT b = axis->y;
	//FLOAT c = axis->z;
	//FLOAT R = sqrt((b * b) + (c * c));
	//
	//D3DXMATRIX R_x = {
	//	1,0,0,0,
	//	0,(c / R),-(b / R),0,
	//	0,(b / R), (c / R),0,
	//	0,0,0,1
	//};
	//D3DXMATRIX R_y = {
	//	R,0,-a,0,
	//	0,1,0,0,
	//	a,0,R,0,
	//	0,0,0,1
	//};
	//D3DXMATRIX R_z = *D3DXMatrixRotationZ(&R_z, angle);
	//
	//D3DXMATRIX invR_x = {
	//	1,0,0,0,
	//	0,(c / R),(b / R),0,
	//	0,-(b / R), (c / R),0,
	//	0,0,0,1
	//};
	//D3DXMATRIX invR_y = {
	//	R,0,a,0,
	//	0,1,0,0,
	//	-a,0,R,0,
	//	0,0,0,1
	//};
	//
	//*pOut = invR_x * invR_y * R_z * R_y * R_x;
	//return pOut;
	FLOAT a = axis->x;
	FLOAT b = axis->y;
	FLOAT c = axis->z;

	pOut->_11 = a * a * (1 - cosf(angle)) + cosf(angle);
	pOut->_12 = a * b * (1 - cosf(angle)) - c * sinf(angle);
	pOut->_13 = a * c * (1 - cosf(angle)) + b * sinf(angle);
	pOut->_14 = 0;

	pOut->_21 = a * b * (1 - cosf(angle)) + c * sinf(angle);
	pOut->_22 = b * b * (1 - cosf(angle)) + cosf(angle);
	pOut->_23 = b * c * (1 - cosf(angle)) - a * sinf(angle);
	pOut->_24 = 0;

	pOut->_31 = a * c * (1 - cosf(angle)) - b * sinf(angle);
	pOut->_32 = b * c * (1 - cosf(angle)) + a * sinf(angle);
	pOut->_33 = c * c * (1 - cosf(angle)) + cosf(angle);
	pOut->_34 = 0;

	pOut->_41 = 0;
	pOut->_42 = 0;
	pOut->_43 = 0;
	pOut->_44 = 1;
	return pOut;
}

D3DXMATRIX* myD3DXMatrixRotationQuaternion(D3DXMATRIX* pOut, const D3DXQUATERNION* q)
{
	FLOAT x = q->x;
	FLOAT y = q->y;
	FLOAT z = q->z;
	FLOAT w = q->w;

	pOut->_11 = 1 - (2 * y * y) - (2 * z * z);
	pOut->_12 = (2 * x * y) - (2 * w * z);
	pOut->_13 = (2 * x * z) + (2 * w * y);
	pOut->_14 = 0;

	pOut->_21 = (2 * x * y) + (2 * w * z);
	pOut->_22 = 1 - (2 * x * x) - (2 * z * z);
	pOut->_23 = (2 * y * z) - (2 * w * x);
	pOut->_24 = 0;

	pOut->_31 = (2 * x * z) - (2 * w * y);
	pOut->_32 = (2 * y * z) + (2 * w * x);
	pOut->_33 = 1 - (2 * x * x) - (2 * y * y);
	pOut->_34 = 0;

	pOut->_41 = 0;
	pOut->_42 = 0;
	pOut->_43 = 0;
	pOut->_44 = 1;

	return pOut;
}

FLOAT myD3DXQuaternionDot(const D3DXQUATERNION* q0, const D3DXQUATERNION* q1)
{
	FLOAT s1 = q0->w;
	FLOAT s2 = q1->w;
	Vector3 v1(q0->x, q0->y, q0->z);
	Vector3 v2(q1->x, q1->y, q1->z);
	return s1 * s2 + myD3DXVec3Dot(&v1,&v2);
}

VOID __ShowQuaternion(const D3DXQUATERNION* q, const string name)
{
	cout << name << " ▶";
	cout << "[ " << q->x << " ] ";
	cout << "[ " << q->y << " ] ";
	cout << "[ " << q->z << " ] / ";
	cout << "[ " << q->w << " ] " << endl;
}

D3DXQUATERNION* myD3DXQuaternionRotationAxis(D3DXQUATERNION* pOut, const Vector3* N, const FLOAT radian)
{
	Vector3 n = *myD3DXVec3Normalize(&n, N);
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

D3DXQUATERNION* myD3DXQuaternionSlerp(D3DXQUATERNION* pOut, const D3DXQUATERNION* q0, const D3DXQUATERNION* q1, const FLOAT time)
{
	D3DXQUATERNION invQ0 = *myD3DXQuaternionInverse(&invQ0, q0);
	D3DXQUATERNION productQ = invQ0 * *q0;
	D3DXQUATERNION powQ; //= __QuaternionPow(&powQ, productQ, time);
	*pOut = *q0 * powQ;
	return pOut;
}

D3DXQUATERNION* myD3DXQuaternionNormalize(D3DXQUATERNION* pOut, const D3DXQUATERNION* q)
{
	*pOut = *q / myD3DXQuaternionLength(q);
	return pOut;
}

D3DXQUATERNION* myD3DXQuaternionMultiply(D3DXQUATERNION* pOut, const D3DXQUATERNION* q1, const D3DXQUATERNION* q2)
{
	FLOAT s1 = q1->w;
	FLOAT s2 = q2->w;

	Vector3 v1(q1->x, q1->y, q1->z);
	Vector3 v2(q2->x, q2->y, q2->z);

	FLOAT fs(s1 * s2 - (myD3DXVec3Dot(&v1, &v2)));
	Vector3 fv((s1 * v2) + (s2 * v1) + myD3DXVec3Cross(&v1, &v2));
	pOut->w = fs;
	pOut->x = fv.x;
	pOut->y = fv.y;
	pOut->z = fv.z;

	return pOut;
}

D3DXQUATERNION* myD3DXQuaternionInverse(D3DXQUATERNION* pOut, const D3DXQUATERNION* q)
{
	D3DXQUATERNION _q = *myD3DXQuaternionConjugate(&_q, q);
	float amount = myD3DXQuaternionLength(&_q);
	pOut->w = _q.w / (amount * amount);
	pOut->x = _q.x / (amount * amount);
	pOut->y = _q.y / (amount * amount);
	pOut->z = _q.z / (amount * amount);
	return pOut;
}

D3DXQUATERNION* myD3DXQuaternionExp(D3DXQUATERNION* pOut, const D3DXQUATERNION* q)
{
	Vector3 v(pOut->x, pOut->y, pOut->z);

	FLOAT _v = myD3DXVec3Length(&v);
	Vector3 n = sinf(_v) * *myD3DXVec3Normalize(&n, &v);

	pOut->w = cosf(_v);
	pOut->x = n.x;
	pOut->y = n.y;
	pOut->z = n.z;
	return pOut;
}

D3DXQUATERNION* myD3DXQuaternionLn(D3DXQUATERNION* pOut, const D3DXQUATERNION* q)
{
	// log(g) = log(|g|)+acosf(s/|g|)*n
	// n = v / ||v||
	FLOAT _q = myD3DXQuaternionLength(q);
	Vector3 n = *myD3DXVec3Normalize(&n, &Vector3(q->x, q->y, q->z));

	pOut->w = log(_q);
	pOut->x = acosf(pOut->w / _q) * n.x;
	pOut->y = acosf(pOut->w / _q) * n.y;
	pOut->z = acosf(pOut->w / _q) * n.z;

	return pOut;
}

D3DXQUATERNION* __QuaternionPow(D3DXQUATERNION* pOut, const D3DXQUATERNION* q, const FLOAT r)
{

	return nullptr;
}

FLOAT myD3DXQuaternionLengthSq(const D3DXQUATERNION* q)
{
	return myD3DXQuaternionDot(q, q);
}

FLOAT myD3DXQuaternionLength(const D3DXQUATERNION* q)
{
	return sqrt(myD3DXQuaternionLengthSq(q));
}

D3DXQUATERNION* __QuaternionRotationAxis(D3DXQUATERNION* pOut, const D3DXQUATERNION* q, const Vector3* axis)
{
	D3DXVECTOR3 y = *axis;
	D3DXVECTOR3 v(q->x, q->y, q->z);

	FLOAT angle = acosf(D3DXVec3Dot(&y, &v) / (D3DXVec3Length(&y) * D3DXVec3Length(&v)));

	D3DXVECTOR3 _axis;
	D3DXVec3Cross(&_axis, &y, &v);

	D3DXQuaternionRotationAxis(pOut, &_axis, angle);
	return pOut;
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