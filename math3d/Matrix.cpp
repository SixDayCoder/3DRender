#include "Matrix.h"


Matrix::Matrix()
{
	_11 = 1; _12 = 0; _13 = 0; _14 = 0;
	_21 = 0; _22 = 1; _23 = 0; _24 = 0;
	_31 = 0; _32 = 0; _33 = 1; _34 = 0;
	_41 = 0; _42 = 0; _43 = 0; _44 = 1;
}

Matrix::Matrix(real a1, real a2, real a3, real a4, real b1, real b2, real b3, real b4, real c1, real c2, real c3, real c4, real d1, real d2, real d3, real d4)
{
	_11 = a1; _12 = a2; _13 = a3; _14 = a4;
	_21 = b1; _22 = b2; _23 = b3; _24 = b4;
	_31 = c1; _32 = c2; _33 = c3; _34 = c4;
	_41 = d1; _42 = d2; _43 = d3; _44 = d4;
}

Matrix::Matrix(const Matrix & rhs)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = rhs.m[i][j];
		}			
	}		
}

Matrix & Matrix::operator=(const Matrix & rhs)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = rhs.m[i][j];
		}			
	}
		
	return *this;
}

void Matrix::SetIdentity()
{
	SetZero();
	_11 = 1;
	_22 = 1;
	_33 = 1;
	_44 = 1;
}

void Matrix::SetZero()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = 0;
		}
	}		
}

bool operator==(const Matrix & lhs, const Matrix & rhs)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (!Equal(lhs.m[i][j], rhs.m[i][j]))
			{
				return false;
			}
		}
	}
		
	return true;
}

Matrix operator+(const Matrix & lhs, const Matrix & rhs)
{
	Matrix mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat.m[i][j] = lhs.m[i][j] + rhs.m[i][j];
		}			
	}		
	return mat;
}

Matrix operator-(const Matrix & lhs, const Matrix & rhs)
{
	Matrix mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat.m[i][j] = lhs.m[i][j] - rhs.m[i][j];
		}
	}
	return mat;
}

Matrix operator*(const Matrix & lhs, const Matrix & rhs)
{
	Matrix mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat.m[j][i] = (lhs.m[j][0] * rhs.m[0][i]) +
						  (lhs.m[j][1] * rhs.m[1][i]) +
						  (lhs.m[j][2] * rhs.m[2][i]) +
						  (lhs.m[j][3] * rhs.m[3][i]);
		}
	}
	return mat;
}

Vector4 operator*(const Vector4& v, const Matrix& m)
{
	Vector4 vec;

	vec.x = v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41;
	vec.y = v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42;
	vec.z = v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43;
	vec.w = v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44;

	return vec;
}

Matrix Matrix::Transpose()const
{
	return Matrix(
		 _11, _21, _31, _41,
		 _12, _22, _32, _42,
		 _13, _23, _33, _43,
		 _14, _24, _34, _44);
}

real Matrix::Det()const
{
	real result =
		_11*_22*_33*_44 - _11*_22*_34*_43 -
		_11*_23*_32*_44 + _11*_23*_34*_42 +

		_11*_24*_32*_43 - _11*_24*_33*_42 -
		_12*_21*_33*_44 + _12*_21*_34*_43 +

		_12*_23*_31*_44 - _12*_23*_34*_41 -
		_12*_24*_31*_43 + _12*_24*_33*_41 +

		_13*_21*_32*_44 - _13*_21*_34*_42 -
		_13*_22*_31*_44 + _13*_22*_34*_41 +

		_13*_24*_31*_42 - _13*_24*_32*_41 -
		_14*_21*_32*_43 + _14*_21*_33*_42 +

		_14*_22*_31*_43 - _14*_22*_33*_41 -
		_14*_23*_31*_42 + _14*_23*_32*_41;

	return result;
}

real Matrix::AdjElem(
	real a1, real a2, real a3,
	real b1, real b2, real b3,
	real c1, real c2, real c3)const
{
	return a1*(b2*c3 - c2*b3) - a2*(b1*c3 - c1*b3) + a3*(b1*c2 - c1*b2);
}

Matrix Matrix::Adjugate()const
{
	real a1 = AdjElem(_22, _23, _24, _32, _33, _34, _42, _43, _44);
	real a2 = AdjElem(_21, _23, _24, _31, _33, _34, _41, _43, _44);
	real a3 = AdjElem(_21, _22, _24, _31, _32, _34, _41, _42, _44);
	real a4 = AdjElem(_21, _22, _23, _31, _32, _33, _41, _42, _43);
	real b1 = AdjElem(_12, _13, _14, _32, _33, _34, _42, _43, _44);
	real b2 = AdjElem(_11, _13, _14, _31, _33, _34, _41, _43, _44);
	real b3 = AdjElem(_11, _12, _14, _31, _32, _34, _41, _42, _44);
	real b4 = AdjElem(_11, _12, _13, _31, _32, _33, _41, _42, _43);
	real c1 = AdjElem(_12, _13, _14, _22, _23, _24, _42, _43, _44);
	real c2 = AdjElem(_11, _13, _14, _21, _23, _24, _41, _43, _44);
	real c3 = AdjElem(_11, _12, _14, _21, _22, _24, _41, _42, _44);
	real c4 = AdjElem(_11, _12, _13, _21, _22, _23, _41, _42, _43);
	real d1 = AdjElem(_12, _13, _14, _22, _23, _24, _32, _33, _34);
	real d2 = AdjElem(_11, _13, _14, _21, _23, _24, _31, _33, _34);
	real d3 = AdjElem(_11, _12, _14, _21, _22, _24, _31, _32, _34);
	real d4 = AdjElem(_11, _12, _13, _21, _22, _23, _31, _32, _33);

	Matrix result(
		a1, -a2, a3, -a4,
		-b1, b2, -b3, b4,
		c1, -c2, c3, -c4,
		-d1, d2, -d3, d4
	);
	return result.Transpose();
}

Matrix Matrix::Inverse()const
{
	real d = abs(Det());
	Matrix adj = Adjugate();
	Matrix Inverse;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Inverse.m[i][j] = adj.m[i][j] / d;
		}
	}
		
	return Inverse;
}
