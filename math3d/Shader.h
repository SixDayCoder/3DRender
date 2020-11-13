#pragma once

#include "math3d/Texture2D.h"
#include "math3d/Matrix.h"
#include "math3d/Vertex.h"

class Shader
{
public:

	Shader();
	Shader(const Shader& other);
	Shader& operator=(const Shader& other);
	~Shader();

	const Matrix& World()const { return m_World; }
	void  SetWorld(const Matrix& mat) { m_World = mat; }

	const Texture2D& Texture()const { return m_Texture; }
	void  SetTexture2D(const Texture2D& tex) { m_Texture = tex; }

	const Matrix& View()const { return m_View; }
	void  SetView(const Matrix& mat){ m_View = mat; }

	const Matrix& Projection()const { return m_Projection; }
	void SetProjection(const Matrix& mat) { m_Projection = mat; }

	VertexOut VS(const VertexIn& v) const;

	Vector4   PS(const VertexOut& v) const;

private:

	Texture2D  m_Texture;
	Matrix     m_World;
	Matrix     m_View;
	Matrix     m_Projection;
};