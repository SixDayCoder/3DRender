#include "Model.h"
#include "Utils.h"
#include <cassert>

#include <assimp\postprocess.h>
#include <assimp\Importer.hpp>

Model::Model()
{
	position = Vector3::Zero;
	scale = Vector3(1, 1, 1);
	rotation = Vector3::Zero;
	world.SetIdentity();
	texture = Texture2D::LoadTexture2D(L"resources/texture/dark_red.jpg");
}

void Model::Update()
{
	float xradians = Radians(rotation.x);
	float yradians = Radians(rotation.y);
	float zradians = Radians(rotation.z);

	Matrix t = Utils::Translate(position);
	Matrix s = Utils::Scale(scale);
	Matrix r = Utils::RotateZ(zradians) * Utils::RotateX(xradians) * Utils::RotateY(yradians);
	world = s * r * t;
}

void Model::LoadFromFile(const std::string & filePath)
{
	assert(!filePath.empty());
	m_Meshes.clear();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile
	(
		filePath.c_str(),
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FixInfacingNormals | aiProcess_JoinIdenticalVertices
	);
	assert(scene);
	if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	ProcessNode(scene->mRootNode, scene);
}

void Model::RotateSelfX(real angle)
{
	rotation.x += angle;
}

void Model::RotateSelfY(real angle)
{
	rotation.y += angle;
}

void Model::RotateSelfZ(real angle)
{
	rotation.z += angle;
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (uint32 i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (uint32 i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<VertexIn> vertices;
	vector<uint32> indices;
	vector<Texture2D> textures;

	//vertices
	for (uint32 i = 0; i < mesh->mNumVertices; ++i)
	{
		VertexIn v;

		Vector3 pos;
		if (mesh->HasPositions())
		{
			pos.x = mesh->mVertices[i].x;
			pos.y = mesh->mVertices[i].y;
			pos.z = mesh->mVertices[i].z;
		}
		v.pos = pos;


		Vector3 normal(0, 0, 0);
		if (mesh->HasNormals())
		{
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
		}
		v.normal = normal;

		real tu = 0;
		real tv = 0;
		if (mesh->HasTextureCoords(0))
		{
			tu = mesh->mTextureCoords[0][i].x;
			tv = mesh->mTextureCoords[0][i].y;
		}
		v.tex.u = tu;
		v.tex.v = tv;

		v.color = Vector3::White;
		vertices.push_back(v);

	}

	//indices
	for (uint32 i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (uint32 j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}

	}

	//textures

	Mesh m;
	m.vertices = vertices;
	m.indices = indices;

	m_Meshes.push_back(m);
}
