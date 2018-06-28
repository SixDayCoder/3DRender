#pragma once
#include "Mesh.h"
#include "Model.h"
#include <memory>


enum RenderMode
{
	RENDER_WIREFRAME,//线框模式
	RENDER_TEXTURE2D //纹理模式
};

class Canvas
{
public:

	Canvas();
	Canvas(int w, int h);
	~Canvas();

	void SetRenderMode(RenderMode mode)
	{
		m_RenderMode = mode;
	}

	RenderMode GetRenderMode()const { return m_RenderMode; }

	void ClearBuffer(Vector3 color);

	void SetViewPort(int left, int top, int width, int height);

	void  DrawMesh(const Mesh& mesh);

	void  DrawModel(const Model& model);


	int Width()const { return m_width; }
	int Height() const { return m_height; }

	uint32*& GetFrameBuffer() { return m_pFrameBuffer; }
	Matrix m_Screen;

private:

	void TriangleRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3, const Shader& shader);
	void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3, const Shader& shader);
	void DrawTriangleTop(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3, const Shader& shader);
	void DrawTriangleBottom(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3, const Shader& shader);
	void ScanlineFill(const VertexOut& va, const VertexOut& vb, int yIndex, const Shader& shader);
	void DrawLine(int x1, int y1, int x2, int y2, const Vector3& color);
	void DrawPixel(int x, int y, Vector4 color);
	real GetZ(int x, int y) const;
	void SetZ(int x, int y, real z);

private:

	RenderMode m_RenderMode;
	uint32* m_pFrameBuffer;
	real **m_zBuffer;

	int m_width;
	int m_height;	
};

