#pragma once
#include "Vertex.h"
#include "Texture2D.h"
#include "Matrix.h"
#include "Shader.h"
#include <vector>
using std::vector;

class Mesh
{
public:

	Mesh();

	Matrix     model;
	Vector3    position;
	Vector3    rotation;
	Vector3    scale;
	Texture2D  texture;
	Shader     shader;

	vector<VertexIn> vertices;
	vector<uint32>  indices;

	void Update();

	void RotateSelfX(real angle);

	void RotateSelfY(real angle);

	void RotateSelfZ(real angle);
};

