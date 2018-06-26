#pragma once
#include <cmath>
#include <cassert>
#include <iostream>

#ifdef _DOUBLE
typedef double real;
#else
typedef float real;
#endif // _DOUBLE

using byte = unsigned char;
using uint32 = unsigned int;

static const  real Esplion = static_cast<real>(1e-5);
static const  real PI = static_cast<real>(3.1415926);

inline bool Equal(real a, real b)
{
	return fabs(a - b) < Esplion;
}

inline real Radians(real angle)
{
	return angle * PI / 180.0f;
}

inline real Angles(real radians)
{
	return radians * 180.0f / PI;
}


