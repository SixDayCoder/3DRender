#pragma once

#include "math3d/Vertex.h"
#include "math3d/Texture2D.h"
#include "math3d/Matrix.h"
#include "math3d/Shader.h"

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
	Shader     shader;

	vector<VertexIn> vertices;
	vector<uint32>  indices;

	void Update();

	void RotateSelfX(real angle);

	void RotateSelfY(real angle);

	void RotateSelfZ(real angle);
};

