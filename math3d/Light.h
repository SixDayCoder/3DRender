#pragma once
#include "Vector.h"
#include <algorithm>


struct Material
{
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	Vector3 reflect;
	real shininess;
};


class Light
{
public:
	virtual 
	void CalcLight(
		Material mat,
		const Vector3& pos,
		const Vector3& normal,
		const Vector3& toEye,
		Vector3& ambient,
		Vector3& diffuse,
		Vector3& spec) const = 0;
};

class DirectionalLight : public Light
{
public:
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	Vector3 direction;
	virtual 
	void CalcLight( 
		Material mat, 
		const Vector3& pos, 
		const Vector3& normal,
		const Vector3& toEye,
		Vector3& ambient,
		Vector3& diffuse,
		Vector3& spec) const
	{
		ambient = mat.ambient * this->ambient;
		Vector3 lightVec = -this->direction;
		lightVec.Normalize();

		real diff = std::max(Vector3::Dot(lightVec, normal), (real)0);
		real spe = std::pow(std::max(Vector3::Dot(Vector3::Reflect(-lightVec, normal), toEye), (real)0), mat.shininess);

		diffuse = mat.diffuse *  this->diffuse * diff;
		spec = mat.specular *  this->specular * spec;
	}
};


