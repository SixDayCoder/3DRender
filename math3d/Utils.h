#pragma once
#include "math3d/MathDefine.h"
#include "math3d/Matrix.h"
#include "math3d/Mesh.h"

class Utils
{

public:

	static real Clamp(real x, real mi, real mx);

	static Matrix Scale(const Vector3& s);

	static Matrix Translate(const Vector3& v);

	static Matrix RotateX(real radians);

	static Matrix RotateY(real radians);

	static Matrix RotateZ(real radians);

	static Matrix Rotate(const Vector3& axis, real radians);

	static Matrix LookAt(Vector3 eyePos, Vector3 lookAt, Vector3 up);

	static Matrix Perspectivce(real fovy, real aspect, real zNear, real zFar);

	static Matrix Viewport(int left, int top, int width, int heigt);

	static uint32 UnitColor(const Vector3& color);
	
	static VertexOut TransofrmToProjection(const VertexIn& v, const Matrix& world, const Matrix& view, const Matrix& projection);

	static void HomogenDivide(VertexOut& v);

	static bool HomogenClip(const VertexOut& v);

	static void TransformToScreen(const Matrix& m, VertexOut& v);

	static bool BackFaceCulling(const VertexIn& v1, const VertexIn& v2, const VertexIn& v3);
	
	static real Lerp(real mi, real mx, real t);

	static Vector2 Lerp(const Vector2&, const Vector2&, real t);

	static Vector3 Lerp(const Vector3&, const Vector3&, real t);
	
	static Vector4 Lerp(const Vector4&, const Vector4&, real t);

	static VertexOut Lerp(const VertexOut & a, const VertexOut & b, real t);

};


