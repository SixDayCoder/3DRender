#pragma once

#include "math3d/Vector.h"
#include "math3d/MathDefine.h"

class VertexIn
{
public:

	Vector4 pos;    
	Vector4 color;  
	Vector2 tex;    
	Vector3 normal; 

	VertexIn() = default;
	VertexIn(Vector4 _pos, Vector4 _color, Vector2 _tex, Vector3 _normal)
		:pos(_pos), color(_color), tex(_tex), normal(_normal)
	{
	}
};


class VertexOut
{
public:

	Vector4 worldPos;  
	Vector4 position;   	
	Vector2 tex;       
	Vector3 normal;	   
	Vector4 color;	   
	real rhw;          

	VertexOut() = default;
	VertexOut(Vector4 _world, Vector4 _proj, Vector2 _tex, Vector3 _normal, Vector4 _color, real _rhw)
		:worldPos(_world), position(_proj), tex(_tex), normal(_normal), color(_color), rhw(_rhw)
	{
	}
};