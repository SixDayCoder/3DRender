#pragma once

#include "Texture2D.h"
#include "Matrix.h"

class Shader
{
public:

	Shader();
	Shader(const Shader& other);
	Shader& operator=(const Shader& other);
	~Shader();


	const Texture2D& Texture()const;
	void  SetTexture2D(const Texture2D& tex);

	const Matrix& View()const { return m_View; }
	void  SetView(const Matrix& mat){ m_View = mat; }

	const Matrix& Projection()const { return m_Projection; }
	void SetProjection(const Matrix& mat) { m_Projection = mat; }

private:

	Texture2D  m_Texture;
	Matrix     m_View;
	Matrix     m_Projection;
};