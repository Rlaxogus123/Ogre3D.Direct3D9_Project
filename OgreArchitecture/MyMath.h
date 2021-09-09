#pragma once

NAMESPACE(MyMath)

FLOAT mysqrt(const FLOAT amount);
FLOAT myFloatLerp(FLOAT* pOut, const FLOAT* a1, const FLOAT* a2, const FLOAT amount);
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Vector2
Vector2 myD3DXVec2Lerp(Vector2* pOut, const Vector2* p1, const Vector2* p2, const FLOAT amount);
FLOAT myD3DXVec2Length(const Vector2* pOut);
Vector3 myD3DXVec3Lerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT amount);
FLOAT myD3DXVec2Length(const Vector2* pOut);
FLOAT myD3DXVec3Length(const Vector3* pOut);
Vector2 myD3DXVec2Normalize(Vector2* pOut, const Vector2* p1);
FLOAT myD3DXVec2Dot(const Vector2* p1, const Vector2* p2);
// Vector2
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Vector3
Vector3 myD3DXVec3Lerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT amount);
FLOAT myD3DXVec3Length(const Vector3* pOut);
Vector3 myD3DXVec3Normalize(Vector3* pOut, const Vector3* p1);
FLOAT myD3DXVec3Dot(const Vector3* p1, const Vector3* p2);
Vector3 myD3DXVec3Cross(Vector3* pOut, const Vector3* p1, const Vector3* p2);
// Vector3
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Matrix
VOID myD3DXMatrixShow(const D3DXMATRIX* pOut);
D3DXMATRIX myD3DXMatrixIdentity(D3DXMATRIX* pOut);
BOOL myD3DXMatrixIsIdentity(const D3DXMATRIX* pM);
D3DXMATRIX myD3DXMatrixMultiply(D3DXMATRIX* pOut, const D3DXMATRIX* m1, const D3DXMATRIX* m2);
// Matrix
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Quaternion
D3DXQUATERNION* myD3DXQuaternionRotationAxis(D3DXQUATERNION* pOut, Vector3* N, const FLOAT radian);
D3DXQUATERNION* myD3DXQuaternionConjugate(D3DXQUATERNION* pOut, const D3DXQUATERNION* q);
FLOAT myD3DXQuaternionLength(const D3DXQUATERNION* q);
// Quaternion
// 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 //
// Others
VOID myProjectileMotion(Vector3* pOut, const Vector3* p1, const Vector3* v, const FLOAT time);
VOID myProjectileMotionFunction(Vector3* pOut, const Vector3* p1, const Vector3* v, const FLOAT time);
// Others

END