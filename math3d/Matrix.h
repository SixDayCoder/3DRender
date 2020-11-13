#pragma once
#include "MathDefine.h"
#include "math3d/Vector.h"


class Matrix
{
public:

	union
	{
		real m[4][4];
		struct
		{
			real _11; real _12; real _13; real _14;
			real _21; real _22; real _23; real _24;
			real _31; real _32; real _33; real _34;
			real _41; real _42; real _43; real _44;
		};
	};

public:
	Matrix();

	Matrix(real a1, real a2, real a3, real a4,
		   real b1, real b2, real b3, real b4,
		   real c1, real c2, real c3, real c4,
		   real d1, real d2, real d3, real d4);

	Matrix(const Matrix& rhs);

	Matrix& operator=(const Matrix& rhs);

	void SetIdentity();

	void SetZero();

	Matrix Transpose()const;

	Matrix Adjugate()const;

	Matrix Inverse()const;

	real Det()const;

	real AdjElem(real a1, real a2, real a3,
	 	         real b1, real b2, real b3,
		         real c1, real c2, real c3)const;


	friend bool    operator==(const Matrix& lhs, const Matrix& rhs);
	friend Matrix  operator+(const Matrix& lhs, const Matrix& rhs);
	friend Matrix  operator-(const Matrix& lhs, const Matrix& rhs);
	friend Matrix  operator*(const Matrix& lhs, const Matrix& rhs);
	friend Vector4 operator*(const Vector4& v, const Matrix& m);
};




