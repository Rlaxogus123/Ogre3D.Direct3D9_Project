#pragma once

NAMESPACE(MyMath)
	
FLOAT myFloatLerp(FLOAT* pOut, const FLOAT* a1, const FLOAT* a2, const FLOAT amount);
Vector2 myD3DXVec2Lerp(Vector2* pOut, const Vector2* p1, const Vector2* p2, const FLOAT amount);
Vector3 myD3DXVec3Lerp(Vector3* pOut, const Vector3* p1, const Vector3* p2, const FLOAT amount);
FLOAT myD3DXVec2Length(Vector2* pOut);
FLOAT myD3DXVec3Length(Vector3* pOut);
Vector2 myD3DXVec2Normalize(Vector2* pOut, const Vector2* p1);
Vector3 myD3DXVec3Normalize(Vector3* pOut, const Vector3* p1);
FLOAT myD3DXVec2Dot(const Vector2* p1, const Vector2* p2);
FLOAT myD3DXVec3Dot(const Vector3* p1, const Vector3* p2);
Vector3 myD3DXVec3Cross(Vector3* pOut, const Vector3 p1, const Vector3 p2);

VOID myD3DXMatrixShow(const D3DXMATRIX* pOut);
D3DXMATRIX myD3DXMatrixIdentity(D3DXMATRIX* pOut);
BOOL myD3DXMatrixIsIdentity(const D3DXMATRIX* pM);
D3DXMATRIX myD3DXMatrixMultiply(D3DXMATRIX* pOut, const D3DXMATRIX* m1, const D3DXMATRIX* m2);

END