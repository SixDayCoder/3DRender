#pragma once
#include "MathDefine.h"
#include "Vector.h"


class Texture2D
{
public:

	Texture2D() :m_width(0), m_height(0), m_pixelBuffer(nullptr) {}

	Texture2D(uint32 width, uint32 height);

	Texture2D(uint32 width, uint32 height, void* data);

	~Texture2D();

	Texture2D(Texture2D&& rhs);

	Texture2D(const Texture2D& rhs);

	Texture2D& operator=(const Texture2D& rhs)
	{
		if (this == &rhs) return *this;
		Texture2D clone(rhs);
		delete[] m_pixelBuffer;
		m_width = clone.m_width;
		m_height = clone.m_height;
		m_pixelBuffer = clone.m_pixelBuffer;
		clone.m_pixelBuffer = nullptr;
		return *this;
	}

	bool Invalid() const { return m_pixelBuffer != nullptr; }

	Vector4 Sample(const Vector2& tex)const;

	uint32   m_width;
	uint32   m_height;
	Vector4* m_pixelBuffer;

	static Texture2D LoadTexture2D(const wchar_t* filePath);
};



