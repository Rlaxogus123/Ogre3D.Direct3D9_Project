#pragma once

NAMESPACE(MyMath)

FLOAT myFloatLerp(FLOAT* pOut, const FLOAT* a1, const FLOAT* a2, const FLOAT amount);
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Vector2
FLOAT myD3DXVec2Length(const Vector2* pOut);
FLOAT myD3DXVec2LengthSq(const Vector2* pOut);
FLOAT myD3DXVec2Dot(const Vector2* p1, const Vector2* p2);
Vector2* myD3DXVec2Lerp(Vector2* pOut, const Vector2* p1, const Vector2* p2, const FLOAT amount);
Vector2* myD3DXVec2Normalize(Vector2* pOut, const Vector2* p1);
// Vector2
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Vector3
VOID __ShowVector3(const Vector3* v, const string name = "Vector");
FLOAT myD3DXVec3Length(const Vector3* pOut);
FLOAT myD3DXVec3LengthSq(const Vector3* pOut);
FLOAT myD3DXVec3Dot(const Vector3* p1, const Vector3* p2);
Vector3* myD3DXVec3Lerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT amount);
Vector3* myD3DXVec3Normalize(Vector3* pOut, const Vector3* p1);
Vector3* myD3DXVec3Cross(Vector3* pOut, const Vector3* p1, const Vector3* p2);
Vector3 myD3DXVec3Cross(const Vector3* p1, const Vector3* p2);
Vector3* myD3DXVec3Slerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT time);
Vector3* __Vec3RotationAxis(Vector3* pOut, const Vector3* r, const Vector3* n, const FLOAT angle);
Vector3* myD3DXVec3Hermite(Vector3* pOut, const Vector3* p_0, const Vector3* T_0, const Vector3* p_1, const Vector3* T_1, FLOAT time);
Vector3* myD3DXVec3CatmullRom(Vector3* pOut, const Vector3* p_0, const Vector3* p_1, const Vector3* p_2, const Vector3* p_3, FLOAT time);
Vector3* myD3DXVec3KochanekBartels(Vector3* pOut, const Vector3* p_0, const Vector3* p_1, const Vector3* p_2, const Vector3* p_3, 
	const FLOAT t, const FLOAT b, const FLOAT c, FLOAT time);
// Vector3
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Matrix
VOID __ShowMatrix(const D3DXMATRIX* m, const string name = "Matrix");
BOOL myD3DXMatrixIsIdentity(const D3DXMATRIX* pM);
D3DXMATRIX* __MatrixRotationQuaternionAxis(D3DXMATRIX* pOut, const D3DXQUATERNION* q, const Vector3* axis);
D3DXMATRIX* myD3DXMatrixIdentity(D3DXMATRIX* pOut);
D3DXMATRIX* myD3DXMatrixMultiply(D3DXMATRIX* pOut, const D3DXMATRIX* m1, const D3DXMATRIX* m2);
D3DXMATRIX* myD3DXMatrixRotationAxis(D3DXMATRIX* pOut, const Vector3* axis, const FLOAT angle);
D3DXMATRIX* myD3DXMatrixRotationQuaternion(D3DXMATRIX* pOut, const D3DXQUATERNION* q);
//D3DXMATRIX myD3DXMatrixQuaternion();
// Matrix
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Quaternion
VOID __ShowQuaternion(const D3DXQUATERNION* q, const string name = "Quaternion");
FLOAT myD3DXQuaternionDot(const D3DXQUATERNION* q0, const D3DXQUATERNION* q1);
FLOAT myD3DXQuaternionLengthSq(const D3DXQUATERNION* q);
FLOAT myD3DXQuaternionLength(const D3DXQUATERNION* q);
D3DXQUATERNION* __QuaternionRotationAxis(D3DXQUATERNION* pOut, const D3DXQUATERNION* q, const Vector3* axis);
D3DXQUATERNION* myD3DXQuaternionConjugate(D3DXQUATERNION* pOut, const D3DXQUATERNION* q);
D3DXQUATERNION* myD3DXQuaternionNormalize(D3DXQUATERNION* pOut, const D3DXQUATERNION* q);
D3DXQUATERNION* myD3DXQuaternionMultiply(D3DXQUATERNION* pOut, const D3DXQUATERNION* q1, const D3DXQUATERNION* q2);
D3DXQUATERNION* myD3DXQuaternionInverse(D3DXQUATERNION* pOut, const D3DXQUATERNION* q);
D3DXQUATERNION* myD3DXQuaternionRotationAxis(D3DXQUATERNION* pOut, const Vector3* axis, const FLOAT angle);
D3DXQUATERNION* myD3DXQuaternionExp(D3DXQUATERNION* pOut, const D3DXQUATERNION* q);
D3DXQUATERNION* myD3DXQuaternionLn(D3DXQUATERNION* pOut, const D3DXQUATERNION* q);
D3DXQUATERNION* __QuaternionPow(D3DXQUATERNION* pOut, const D3DXQUATERNION* q, const FLOAT r);
D3DXQUATERNION* myD3DXQuaternionSlerp(D3DXQUATERNION* pOut, const D3DXQUATERNION* q0, const D3DXQUATERNION* q1, const FLOAT time);
D3DXQUATERNION* myD3DXQuaternionSquad(D3DXQUATERNION* pOut, const D3DXQUATERNION* q0, const D3DXQUATERNION* s0, const D3DXQUATERNION* s1, const D3DXQUATERNION* q1, FLOAT time);
VOID myD3DXQuaternionSquadSetup(D3DXQUATERNION* s0, D3DXQUATERNION* s1, const D3DXQUATERNION* q0, const D3DXQUATERNION* q1, const D3DXQUATERNION* q2, const D3DXQUATERNION* q3);
//D3DXQUATERNION* __QuaternionAlgebraicSlerp(D3DXQUATERNION* pOut, const D3DXQUATERNION* q0, const D3DXQUATERNION* q1);

// Quaternion
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Others
VOID myProjectileMotion(Vector3* pOut, const Vector3* p1, const Vector3* v, const FLOAT time);
VOID myProjectileMotionFunction(Vector3* pOut, const Vector3* p1, const Vector3* v, const FLOAT time);
// Others

END