#include "Mesh.h"
#include "Utils.h"

Mesh::Mesh()
{
	position = Vector3::Zero;
	scale = Vector3(1, 1, 1);
	rotation = Vector3::Zero;
	model.SetIdentity();
}

void Mesh::Update()
{
	float xradians = Radians(rotation.x);
	float yradians = Radians(rotation.y);
	float zradians = Radians(rotation.z);

	Matrix t = Utils::Translate(position);
	Matrix s = Utils::Scale(scale);
	Matrix r = Utils::RotateZ(zradians) * Utils::RotateX(xradians) * Utils::RotateY(yradians);
	model = s * r * t;
}

void Mesh::RotateSelfX(real angle)
{
	rotation.x += angle;
}

void Mesh::RotateSelfY(real angle)
{
	rotation.y += angle;
}

void Mesh::RotateSelfZ(real angle)
{
	rotation.z += angle;
}
