#include "Utils.h"
#include "Vertex.h"
#include <cmath>
#include <algorithm>




real Utils::Clamp(real x, real mi, real mx)
{
	return std::max(mi, std::min(x, mx));
}

Matrix Utils::Scale(const Vector3& s)
{
	return Matrix(
		s.x, 0, 0, 0,
		0, s.y, 0, 0,
		0, 0, s.z, 0,
		0, 0, 0, 1
	);
}

Matrix Utils::Translate(const Vector3& v)
{
	return Matrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		v.x, v.y, v.z, 1
	);
}

Matrix Utils::RotateX(real radians)
{
	return Matrix(
		1, 0, 0, 0,
		0, cos(radians), sin(radians), 0,
		0, -sin(radians), cos(radians), 0,
		0, 0, 0, 1
	);
}

Matrix Utils::RotateY(real radians)
{
	return Matrix(
		cos(radians), 0, -sin(radians), 0,
		0, 1, 0, 0,
		sin(radians), 0, cos(radians), 0,
		0, 0, 0, 1
	);
}

Matrix Utils::RotateZ(real radians)
{
	return Matrix(
		cos(radians), sin(radians), 0, 0,
		-sin(radians), cos(radians), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

Matrix Utils::Rotate(const Vector3& axis, real radians)
{
	real oneMinusCos = 1 - cos(radians);


	axis.Normalize();
	Matrix mat;
	mat.SetZero();

	mat._11 = axis.x * axis.x * oneMinusCos + cos(radians);
	mat._12 = axis.x * axis.y * oneMinusCos + axis.z * sin(radians);
	mat._13 = axis.x * axis.z * oneMinusCos - axis.y * sin(radians);

	mat._21 = axis.x * axis.y * oneMinusCos - axis.z * sin(radians);
	mat._22 = axis.y * axis.y * oneMinusCos + cos(radians);
	mat._23 = axis.y * axis.z * oneMinusCos + axis.z * sin(radians);

	mat._31 = axis.x * axis.z * oneMinusCos + axis.y * sin(radians);
	mat._32 = axis.y * axis.z * oneMinusCos - axis.x * sin(radians);
	mat._33 = axis.z * axis.z * oneMinusCos + cos(radians);

	mat._44 = 1;

	return mat;
}

Matrix Utils::LookAt(Vector3 eyePos, Vector3 lookAt, Vector3 up)
{
	Vector3 zaxis = lookAt - eyePos;
	zaxis.Normalize();
	Vector3 xaxis = Vector3::Cross(up, zaxis);
	xaxis.Normalize();
	Vector3 yaxis = Vector3::Cross(zaxis, xaxis);
	yaxis.Normalize();

	real tx = -Vector3::Dot(xaxis, eyePos);
	real ty = -Vector3::Dot(yaxis, eyePos);
	real tz = -Vector3::Dot(zaxis, eyePos);

	return Matrix(
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		tx,      ty,      tz,      1
	);
}

Matrix Utils::Perspectivce(real fovy, real aspect, real zNear, real zFar)
{
	assert(abs(aspect - std::numeric_limits<real>::epsilon()) > static_cast<real>(0));

	Matrix mat;
	mat.SetZero();
	real height = cos(fovy * static_cast<real>(0.5)) / sin(fovy * static_cast<real>(0.5));
	mat._11 = height / aspect;
	mat._22 = height;
	mat._33 = zFar / (zFar - zNear);
	mat._34 = static_cast<real>(1);
	mat._43 = (zNear * zFar) / (zNear - zFar);
	return mat;
}


Matrix Utils::Viewport(int left, int top, int width, int height)
{
	real _11 = (real)width *  (real)0.5;
	real _22 = (real)(-height) * (real)0.5;
	real _41 = (real)width *  (real)0.5 + (real)left;
	real _42 = (real)height * (real)0.5 + (real)top;

	return Matrix(
		_11,  0,   0, 0,
		 0,  _22,  0, 0,
		 0,   0,   1, 0,
		_41, _42,  0, 1
	);
}


uint32 Utils::UnitColor(const Vector3& color)
{
	byte red = static_cast<byte>(255 * color.x);
	byte green = static_cast<byte>(255 * color.y);
	byte blue = static_cast<byte>(255 * color.z);
	return (unsigned int)((byte)blue | (unsigned short)((byte)green << 8) | (unsigned long)((byte)red << 16));
}

VertexOut Utils::TransofrmToProjection(const VertexIn & v, const Matrix & world, const Matrix & view, const Matrix & projection)
{
	VertexOut out;
	out.worldPos = v.pos * world;
	out.position = out.worldPos * view * projection;
	out.normal = v.normal * world.Inverse().Transpose();
	out.color = v.color;
	out.tex = v.tex;

	//Í¸ÊÓ½ÃÕý
	assert(!Equal(out.position.w, (real)0));
	out.rhw = 1 / out.position.w;
	out.worldPos *= out.rhw;
	out.color *= out.rhw;
	out.tex *= out.rhw;

	return out;
}

void Utils::HomogenDivide(VertexOut & v)
{
	assert(!Equal(v.position.w, (real)0));
	v.position.x /= v.position.w;
	v.position.y /= v.position.w;
	v.position.z /= v.position.w;
	v.position.w = (real)1;
}

bool Utils::HomogenClip(const VertexOut & v)
{
	if (v.position.x >= -v.position.w && v.position.x <= v.position.w &&
		v.position.y >= -v.position.w && v.position.y <= v.position.w &&
		v.position.z >= 0.f && v.position.z <= v.position.w)
	{
		return true;
	}
	return false;
}

void Utils::TransformToScreen(const Matrix & m, VertexOut & v)
{
	v.position = v.position * m;
}

bool Utils::BackFaceCulling(const VertexIn & v1, const VertexIn & v2, const VertexIn & v3)
{
	Vector3 vector1 = v2.pos - v1.pos;
	Vector3 vector2 = v3.pos - v2.pos;
	Vector3 normal = Vector3::Cross(vector1, vector2);
	Vector3 viewDir = v1.pos;
	if (Vector3::Dot(normal, viewDir) > 0)
	{
		return true;
	}
	return false;
}

real Utils::Lerp(real mi, real mx, real t)
{
	return mi + (mx - mi) * t;
}

Vector2 Utils::Lerp(const Vector2 &lhs, const Vector2 &rhs, real t)
{
	return Vector2(lhs.x + (rhs.x - lhs.x) * t, lhs.y + (rhs.y - lhs.y) * t);
}

Vector3 Utils::Lerp(const Vector3 &lhs, const Vector3 &rhs, real t)
{
	return Vector3(lhs.x + (rhs.x - lhs.x) * t,
				   lhs.y + (rhs.y - lhs.y) * t,
				   lhs.z + (rhs.z - lhs.z) * t);
}

Vector4 Utils::Lerp(const Vector4 &lhs, const Vector4 &rhs, real t)
{
	return Vector4(lhs.x + (rhs.x - lhs.x) * t,
				   lhs.y + (rhs.y - lhs.y) * t,
				   lhs.z + (rhs.z - lhs.z) * t,
				   lhs.w);
}

VertexOut Utils::Lerp(const VertexOut & a, const VertexOut & b, real t)
{

	return VertexOut(
		Lerp(a.worldPos, b.worldPos, t),
		Lerp(a.position, b.position, t),
		Lerp(a.tex, b.tex, t),
		Lerp(a.normal, b.normal, t),
		Lerp(a.color, b.color, t),
		Lerp(a.rhw, b.rhw, t)
	);
}




