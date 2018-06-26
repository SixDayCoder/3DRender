#include "Vector.h"

const Vector2 Vector2::Zero(0, 0);
const Vector2 Vector2::One(1, 1);
const Vector2 Vector2::Left(-1, 0);
const Vector2 Vector2::Right(1, 0);
const Vector2 Vector2::Up(0, 1);
const Vector2 Vector2::Down(0, -1);


const Vector3 Vector3::Left(-1, 0, 0);
const Vector3 Vector3::Right(1, 0, 0);
const Vector3 Vector3::Up(0, 1, 0);
const Vector3 Vector3::Down(0, -1, 0);
const Vector3 Vector3::Forward(0, 0, 1);
const Vector3 Vector3::Back(0, 0, -1);
const Vector3 Vector3::One(1, 1, 1);
const Vector3 Vector3::Zero(0, 0, 0);

const Vector3 Vector3::Red(1, 0, 0);
const Vector3 Vector3::Green(0, 1, 0);
const Vector3 Vector3::Blue(0, 0, 1);
const Vector3 Vector3::White(1, 1, 1);
const Vector3 Vector3::Yellow(1, 1, 0);
const Vector3 Vector3::Grey(0.5, 0.5, 0.5f);

//************************************************************Vector2**********************************************************//

Vector2 operator+(const Vector2 & lhs, const Vector2 & rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator-(const Vector2 & lhs, const Vector2 & rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 operator*(const Vector2 & lhs, real factor)
{
	return Vector2(lhs.x * factor, lhs.y * factor);
}

Vector2 operator*(real factor, const Vector2 & rhs)
{
	return rhs * factor;
}

Vector2 operator/(const Vector2 & lhs, real factor)
{
	assert(factor != (real)0);
	real rhf = (real)1 / factor;
	return lhs * rhf;
}

Vector2 Vector2::operator*(const Vector2 & other)
{
	return Vector2(x * other.x, y * other.y);
}

real Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

real Vector2::Angle(const Vector2& a, const Vector2& b)
{
	real dot = Dot(a, b);
	return acos(dot / a.Magnitude() / b.Magnitude());
}

real Vector2::Distance(const Vector2& a, const Vector2& b)
{
	return (a - b).Magnitude();
}

Vector2 Vector2::Reflect(const Vector2& I, const Vector2& N)
{
	real tmp = 2.f * Dot(N, I);
	return I - (N * tmp);
}

//************************************************************Vector2**********************************************************//


//************************************************************Vector3**********************************************************//
Vector3 operator+(const Vector3 & lhs, const Vector3 & rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 operator-(const Vector3 & lhs, const Vector3 & rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3 operator*(const Vector3 & lhs, real factor)
{
	return Vector3(lhs.x * factor, lhs.y * factor, lhs.z * factor);
}

Vector3 operator*(real factor, const Vector3 & rhs)
{
	return rhs * factor;
}

Vector3 operator/(const Vector3 & lhs, real factor)
{
	assert(factor != (real)0);
	real rhf = (real)1 / factor;
	return lhs * rhf;
}

real Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(a.y * b.z - a.z * b.y,
				   a.z * b.x - a.x * b.z,
				   a.x * b.y - a.y * b.x);
}

real Vector3::Angle(const Vector3& a, const Vector3& b)
{
	real dot = Dot(a, b);
	return acos(dot / a.Magnitude() / b.Magnitude());
}

real Vector3::Distance(const Vector3& a, const Vector3& b)
{
	return (a - b).Magnitude();
}

Vector3 Vector3::Reflect(const Vector3& I, const Vector3& N)
{
	real tmp = 2.f * Dot(N, I);
	return I - (N * tmp);
}

//************************************************************Vector3**********************************************************//


//************************************************************Vector4**********************************************************//

Vector4 operator+(const Vector4 & lhs, const Vector4 & rhs)
{
	return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Vector4 operator-(const Vector4 & lhs, const Vector4 & rhs)
{
	return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Vector4 operator*(const Vector4 & lhs, real factor)
{
	return Vector4(lhs.x * factor, lhs.y * factor, lhs.z * factor, lhs.z * factor);
}

Vector4 operator*(real factor, const Vector4 & rhs)
{
	return rhs * factor;
}

Vector4 operator/(const Vector4 & lhs, real factor)
{
	assert(factor != (real)0);
	real rhf = (real)1 / factor;
	return lhs * rhf;
}

//************************************************************Vector4**********************************************************//







