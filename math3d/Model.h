#pragma once

#include "Mesh.h"
#include <vector>
#include <string>

#include <assimp\scene.h>



using std::vector;
using std::string;

class Model
{
public:

	Model();

	const vector<Mesh>& Meshes()const { return m_Meshes; }
	vector<Mesh>& Meshes() { return m_Meshes; }

	void Update();

	void LoadFromFile(const string& filePath);

	void RotateSelfX(real angle);

	void RotateSelfY(real angle);

	void RotateSelfZ(real angle);

	Matrix    world;
	Shader    shader;
	Texture2D texture;

	Vector3   position;
	Vector3   rotation;
	Vector3   scale;

private:

	vector<Mesh> m_Meshes;

	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};