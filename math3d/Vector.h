#pragma once
#include "math3d/MathDefine.h"

class Vector2
{
public:

	
	Vector2() :x(0), y(0) {}
	Vector2(real _x, real _y) :x(_x), y(_y) {}

	bool operator==(const Vector2& other)
	{
		return Equal(x, other.x) && Equal(y, other.y);
	}

	bool operator!=(const Vector2& other)
	{
		return !(*this == other);
	}

	Vector2 operator*(const Vector2& other);

	Vector2 operator-()const
	{
		return Vector2(-x, -y);
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator*=(real factor)
	{
		x *= factor;
		y *= factor;
		return *this;
	}

	Vector2& operator/=(real factor)
	{
		assert(factor != (real)0);
		real rhf = (real)1 / factor;
		x *= rhf;
		y *= rhf;
		return *this;
	}

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator*(const Vector2& lhs, real factor);
	friend Vector2 operator*(real factor, const Vector2& rhs);
	friend Vector2 operator/(const Vector2& lhs, real factor);

	real Magnitude()const
	{
		return sqrt(x * x + y * y);
	}

	real SqrMagnitude()const
	{
		return x * x + y * y;
	}

	Vector2 Normalize()const
	{
		real len = Magnitude();
		if (len > 0.0f)
		{
			real rhl = real(1) / rhl;
			return Vector2(x * rhl, y * rhl);
		}
		return Zero;
	}

	void Normalize()
	{
		real len = Magnitude();
		if (len > 0.0f)
		{
			real rhl = (real)1 / len;
			x *= rhl;
			y *= rhl;
		}
	}

	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 Zero;
	static const Vector2 One;

	static real    Dot(const Vector2&, const Vector2&);

	static real    Angle(const Vector2&, const Vector2&);

	static real    Distance(const Vector2&, const Vector2&);

	static Vector2 Reflect(const Vector2&, const Vector2&);

	union
	{
		struct
		{
			real x, y;
		};
		struct
		{
			real u, v;
		};
	};
};


class Vector3
{
public:

	Vector3() :x(0), y(0), z(0) {}
	Vector3(real _x, real _y, real _z) :x(_x), y(_y), z(_z) {}
	Vector3(const Vector2 v2) : x(v2.x), y(v2.y), z(0) {}

	bool operator==(const Vector3& other)
	{
		return Equal(x, other.x) && Equal(y, other.y) && Equal(z, other.z);
	}

	bool operator!=(const Vector3& other)
	{
		return !(*this == other);
	}

	Vector3 operator*(Vector3 other)const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	Vector3 operator-()const
	{
		return Vector3(-x, -y, -z);
	}

	operator Vector2()const
	{
		return Vector2(x, y);
	}

	Vector3& operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z += other.z;
		return *this;
	}

	Vector3& operator*=(real factor)
	{
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	Vector3& operator/=(real factor)
	{
		assert(factor != (real)0);
		real rhf = (real)1 / factor;
		x *= rhf;
		y *= rhf;
		z *= rhf;
		return *this;
	}

	friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator*(const Vector3& lhs, real factor);
	friend Vector3 operator*(real factor, const Vector3& rhs);
	friend Vector3 operator/(const Vector3& lhs, real factor);

	real Magnitude()const
	{
		return sqrt(x * x + y * y + z * z);
	}

	real SqrMagnitude()const
	{
		return x * x + y * y + z * z;;
	}

	Vector3 Normalize()const
	{
		real len = Magnitude();
		if (len > 0.0f)
		{
			real rhl = 1.0f / len;
			return Vector3(x * rhl, y * rhl, z * rhl);
		}
		return Zero;
	}

	void Normalize()
	{
		real len = Magnitude();
		if (len > 0.0f && !Equal(len, 1.0f))
		{
			real rhl = 1.0f / len;
			x *= rhl;
			y *= rhl;
			z *= rhl;
		}
	}

	static real    Dot(const Vector3&, const Vector3&);

	static real    Angle(const Vector3&, const Vector3&);

	static real    Distance(const Vector3&, const Vector3&);

	static Vector3 Cross(const Vector3&, const Vector3&);

	static Vector3 Reflect(const Vector3&, const Vector3&);

	static const Vector3 Left;
	static const Vector3 Right;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Forward;
	static const Vector3 Back;
	static const Vector3 Zero;
	static const Vector3 One;

	static const Vector3 Red;
	static const Vector3 Green;
	static const Vector3 Blue;
	static const Vector3 White;
	static const Vector3 Yellow;
	static const Vector3 Grey;

	real x, y, z;
};

class Vector4
{
public:

	Vector4() :x(0), y(0), z(0), w(0) {}
	Vector4(real _x, real _y, real _z, real _w) :x(_x), y(_y), z(_z), w(_w) {}
	Vector4(const Vector2 v2) : x(v2.x), y(v2.y), z(0), w(0) {}
	Vector4(const Vector3 v3) : x(v3.x), y(v3.y), z(v3.z), w(1) {}

	bool operator==(const Vector4& other)
	{
		return Equal(x, other.x) && Equal(y, other.y) && Equal(z, other.z) && Equal(w, other.w);
	}

	bool operator!=(const Vector4& other)
	{
		return !(*this == other);
	}

	Vector4 operator*(const Vector4& other)const
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	Vector4 operator-()const
	{
		return Vector4(-x, -y, -z, -w);
	}

	operator Vector3()const
	{
		return Vector3(x, y, z);
	}

	Vector4& operator+=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vector4& operator-=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vector4& operator*=(real factor)
	{
		x *= factor;
		y *= factor;
		z *= factor;
		w *= factor;
		return *this;
	}

	Vector4& operator/=(real factor)
	{
		assert(factor != (real)0);
		real rhf = (real)1 / factor;
		x *= rhf;
		y *= rhf;
		z *= rhf;
		w *= rhf;
		return *this;
	}

	friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
	friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
	friend Vector4 operator*(const Vector4& lhs, real factor);
	friend Vector4 operator*(real factor, const Vector4& rhs);
	friend Vector4 operator/(const Vector4& lhs, real factor);

	union
	{
		struct
		{
			real x, y, z, w;
		};
		struct
		{
			real u, v, s, t;
		};
	};

};





