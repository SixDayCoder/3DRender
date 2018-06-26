#include "Shader.h"
#include <cassert>

Shader::Shader()
{
}

Shader::Shader(const Shader & other)
{
	m_View = other.m_View;
	m_Projection = other.m_Projection;
	m_Texture = other.m_Texture;
}

Shader & Shader::operator=(const Shader & other)
{

	m_View = other.m_View;
	m_Projection = other.m_Projection;
	m_Texture = other.m_Texture;

	return *this;
}

Shader::~Shader()
{
}

const Texture2D & Shader::Texture() const
{
	return m_Texture;
}

void Shader::SetTexture2D(const Texture2D & tex)
{
	m_Texture = tex;
}
