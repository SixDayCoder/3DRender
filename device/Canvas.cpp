#include "device/Canvas.h"
#include "math3d/Utils.h"
#include "math3d/Vertex.h"
#include <algorithm>


Canvas::Canvas() :
	m_RenderMode(RENDER_WIREFRAME),
	m_pFrameBuffer(nullptr),
	m_zBuffer(nullptr)
{
}

Canvas::Canvas(int w, int h)
{
	assert(w > 0 && h > 0);
	m_width = w;
	m_height = h;
	m_zBuffer = new real*[w];
	for (int i = 0; i < w; ++i)
	{
		m_zBuffer[i] = new real[h]{ 0 };
	}
}

Canvas::~Canvas()
{
	if (m_zBuffer)
	{
		for (int i = 0; i < m_width; ++i)
		{
			delete[] m_zBuffer[i];
		}
		delete m_zBuffer;
		m_zBuffer = nullptr;
	}
}

real Canvas::GetZ(int x, int y) const
{
	assert(m_pFrameBuffer != nullptr);
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		return m_zBuffer[x][y];
	}
	else
	{
		return static_cast<real>(1);
	}
}

void Canvas::SetZ(int x, int y, real z)
{
	assert(m_pFrameBuffer != nullptr);
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		m_zBuffer[x][y] = z;
	}
}

void Canvas::SetViewPort(int left, int top, int width, int height)
{
	m_Screen = Utils::Viewport(left, top, width, height);
}


void Canvas::DrawLine(int x1, int y1, int x2, int y2, const Vector3& color)
{
	int dx = abs(x2 - x1);
	int stepx = x1 < x2 ? 1 : -1;

	int dy = abs(y2 - y1);
	int stepy = y1 < y2 ? 1 : -1;

	int err = (dx > dy ? dx : -dy) / 2;

	while (x1 != x2 || y1 != y2)
	{
		if ((0 <= x1 && x1 < m_width) && (0 <= y1 && y1 < m_height))
		{
			DrawPixel(x1, y1, color);			
		}	

		int e2 = err;
		if (e2 > -dx) { err -= dy; x1 += stepx; }
		if (e2 <  dy) { err += dx; y1 += stepy; }
	}
}

void Canvas::DrawTriangle(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3, const Shader& shader)
{
	if (m_RenderMode == RENDER_WIREFRAME)
	{
		int v1x = (int)v1.position.x, v1y = (int)v1.position.y;
		int v2x = (int)v2.position.x, v2y = (int)v2.position.y;
		int v3x = (int)v3.position.x, v3y = (int)v3.position.y;

		DrawLine(v1x, v1y, v2x, v2y, Vector3::Red);
		DrawLine(v1x, v1y, v3x, v3y, Vector3::Red);
		DrawLine(v3x, v3y, v2x, v2y, Vector3::Red);
	}
	else if (m_RenderMode == RENDER_TEXTURE2D)
	{
		TriangleRasterization(v1, v2, v3, shader);
	}
}

void Canvas::DrawMesh(const Mesh & mesh)
{
	const vector<uint32>& indices = mesh.indices;
	const vector<VertexIn>& vertices = mesh.vertices;

	for (uint32 i = 0; i < mesh.indices.size(); i += 3)
	{
		VertexIn p1 = vertices[ indices[i] ];
		VertexIn p2 = vertices[ indices[i + 1] ];
		VertexIn p3 = vertices[ indices[i + 2] ];

		VertexOut v1 = mesh.shader.VS(p1);
		VertexOut v2 = mesh.shader.VS(p2);
		VertexOut v3 = mesh.shader.VS(p3);

		if (Utils::BackFaceCulling(p1, p2, p3) == false)
		{
			continue;
		}

		if (Utils::HomogenClip(v1) == false && 
			Utils::HomogenClip(v2) == false &&
			Utils::HomogenClip(v3) == false)
		{
			continue;
		}

		Utils::HomogenDivide(v1); 
		Utils::HomogenDivide(v2);
		Utils::HomogenDivide(v3);

		Utils::TransformToScreen(m_Screen, v1);
		Utils::TransformToScreen(m_Screen, v2);
		Utils::TransformToScreen(m_Screen, v3);

		DrawTriangle(v1, v2, v3, mesh.shader);
	}
}

void Canvas::DrawModel(const Model & model)
{
	const vector<Mesh>& meshes = model.Meshes();
	const Shader& shader = model.shader;

	for (uint32 i = 0; i < meshes.size(); ++i)
	{
		const Mesh& mesh = meshes[i];
		const vector<uint32>& indices = mesh.indices;
		const vector<VertexIn>& vertices = mesh.vertices;

		for (uint32 j = 0; j < mesh.indices.size(); j += 3)
		{
			VertexIn p1 = vertices[indices[j]];
			VertexIn p2 = vertices[indices[j + 1]];
			VertexIn p3 = vertices[indices[j + 2]];

			VertexOut v1 = shader.VS(p1);
			VertexOut v2 = shader.VS(p2);
			VertexOut v3 = shader.VS(p3);

			if (Utils::BackFaceCulling(p1, p2, p3) == false)
			{
				continue;
			}

			if (Utils::HomogenClip(v1) == false &&
				Utils::HomogenClip(v2) == false &&
				Utils::HomogenClip(v3) == false)
			{
				continue;
			}

			Utils::HomogenDivide(v1);
			Utils::HomogenDivide(v2);
			Utils::HomogenDivide(v3);

			Utils::TransformToScreen(m_Screen, v1);
			Utils::TransformToScreen(m_Screen, v2);
			Utils::TransformToScreen(m_Screen, v3);

			DrawTriangle(v1, v2, v3, shader);
		}
	}
}

void Canvas::TriangleRasterization(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3, const Shader& shader)
{
	std::vector<VertexOut> vertices{ v1,v2,v3 };
	std::sort(vertices.begin(), vertices.end(), [](VertexOut v1, VertexOut v2)
	{
		return v1.position.y < v2.position.y;
	});

	VertexOut top = vertices[0];
	VertexOut middle = vertices[1];
	VertexOut bottom = vertices[2];

	real t = (middle.position.y - top.position.y) / (bottom.position.y - top.position.y);

	VertexOut newMiddle = Utils::Lerp(top, bottom, t);

	DrawTriangleTop(middle, newMiddle, bottom, shader);
	DrawTriangleBottom(top, middle, newMiddle, shader);
}

void Canvas::DrawTriangleTop(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3, const Shader& shader)
{
	real dy = 0;
	for (real y = v1.position.y; y <= v3.position.y; y += 1)
	{
		int yIndex = static_cast<int>(y + static_cast<real>(0.5));
		if (yIndex >= 0 && yIndex < m_height)
		{
			real t = 0;
			if (!Equal(v3.position.y, v1.position.y))
			{
				t = dy / (v3.position.y - v1.position.y);
			}

			VertexOut va = Utils::Lerp(v1, v3, t);
			VertexOut vb = Utils::Lerp(v2, v3, t);
			dy += static_cast<real>(1);
			ScanlineFill(va, vb, yIndex, shader);
		}
	}

}

void Canvas::DrawTriangleBottom(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3, const Shader& shader)
{
	real dy = 0;
	for (real y = v1.position.y; y <= v2.position.y; y += 1)
	{
		int yIndex = (int)(y + (real)(0.5));
		if (yIndex >= 0 && yIndex < m_height)
		{
			real t = 0;
			if (!Equal(v2.position.y, v1.position.y))
			{
				t = dy / (v2.position.y - v1.position.y);
			}

			VertexOut va = Utils::Lerp(v1, v2, t);
			VertexOut vb = Utils::Lerp(v1, v3, t);
			dy += static_cast<real>(1);
			ScanlineFill(va, vb, yIndex, shader);
		}
	}
}

void Canvas::ScanlineFill(const VertexOut & va, const VertexOut & vb, int yIndex, const Shader& shader)
{

	VertexOut left = va;
	VertexOut right = vb;

	if (va.position.x >= vb.position.x) { left = vb; right = va;}
	real dx = right.position.x - left.position.x;
	for (real x = left.position.x; x <= right.position.x; x += 1)
	{
		int xIndex = static_cast<int>(x + static_cast<real>(0.5));
		if (xIndex >= 0 && xIndex < m_width)
		{
			real t = 0;
			if (!Equal(dx, 0)) { t = (x - left.position.x) / dx; }
			real rhw = Utils::Lerp(left.rhw, right.rhw, t);
			if (rhw >= GetZ(xIndex, yIndex))
			{
				SetZ(xIndex, yIndex, rhw);
				real w = 1 / rhw;
				VertexOut out = Utils::Lerp(left, right, t);
				out.position.x = xIndex;
				out.position.y = yIndex;
				out.worldPos *= w;
				out.tex *= w;
				out.color *= w;
				DrawPixel(xIndex, yIndex, shader.PS(out));
			}
		}

	}
}

void Canvas::DrawPixel(int x, int y, Vector4 color)
{
	assert(m_pFrameBuffer != nullptr);
	m_pFrameBuffer[y * m_width + x] = Utils::UnitColor(color);
}

void Canvas::ClearBuffer(Vector3 color)
{
	assert(m_pFrameBuffer != nullptr && m_zBuffer != nullptr);
	for (int x = 0; x < m_width; ++x)
	{
		for (int y = 0; y < m_height; ++y)
		{
			m_pFrameBuffer[m_width * y + x] = Utils::UnitColor(color);
			m_zBuffer[x][y] = 0;
		}
	}
}