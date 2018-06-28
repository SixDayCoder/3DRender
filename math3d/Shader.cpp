#include "Shader.h"
#include "Vertex.h"
#include <cassert>

Shader::Shader()
{
	m_World.SetIdentity();
	m_View.SetIdentity();
	m_Projection.SetIdentity();	
}

Shader::Shader(const Shader & other)
{
	m_World = other.m_World;
	m_View = other.m_View;
	m_Projection = other.m_Projection;
	m_Texture = other.m_Texture;
}

Shader & Shader::operator=(const Shader & other)
{
	m_World = other.m_World;
	m_View = other.m_View;
	m_Projection = other.m_Projection;
	m_Texture = other.m_Texture;

	return *this;
}

Shader::~Shader()
{
}

VertexOut Shader::VS(const VertexIn& v) const
{
	VertexOut out;
	out.worldPos = v.pos * m_World;
	out.position = out.worldPos * m_View * m_Projection;
	out.normal = v.normal * m_World.Inverse().Transpose();
	out.color = v.color;
	out.tex = v.tex;

	assert(!Equal(out.position.w, (real)0));
	out.rhw = 1 / out.position.w;
	out.worldPos *= out.rhw;
	out.color *= out.rhw;
	out.tex *= out.rhw;

	return out;
}

Vector4 Shader::PS(const VertexOut & v) const
{
	return m_Texture.Sample(v.tex);
}

