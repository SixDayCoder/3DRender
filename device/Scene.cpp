#include "Scene.h"
#include "BoxDemo.h"
#include "Light.h"
#include "Utils.h"

Scene::Scene()
{

	m_lastMousePos.x = 0;
	m_lastMousePos.y = 0;

	m_deltatime = 0;
	m_bInit = false;
}


Scene::~Scene()
{
	if (m_pCanvas)
	{
		delete m_pCanvas;
		m_pCanvas = nullptr;
	}
}

bool Scene::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hInstance = hInstance;
	m_lasttime = clock();

	RECT rc;
	GetClientRect(m_hWnd, &rc);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	InitCanvas();
	InitCamera();
	
	m_deltatime = 0.0f;
	m_bInit = true;
	return true;
}

void Scene::Update()
{
	TickTime();
	m_Camera.Update();

	for (auto& mesh : m_Meshes)
	{
		mesh.Update();
	}

	for (auto& model : m_Models)
	{
		model.Update();
	}
}

void Scene::Render()
{
	m_pCanvas->ClearBuffer(Vector3::Grey);
	const Matrix& view = m_Camera.View();
	const Matrix& projection = m_Camera.Projection();

	for (Mesh& mesh : m_Meshes)
	{
		mesh.shader.SetWorld(mesh.model);
		mesh.shader.SetView(view);
		mesh.shader.SetProjection(projection);
		m_pCanvas->DrawMesh(mesh);
	}

	for (Model& model : m_Models)
	{
		model.shader.SetWorld(model.world);
		model.shader.SetView(view);
		model.shader.SetProjection(projection);
		m_pCanvas->DrawModel(model);
	}
	
}

void Scene::TickTime()
{
	clock_t now = clock();
	clock_t delta = clock() - m_lasttime;
	m_lasttime = now;
	m_deltatime = delta / 1000.0f;
	std::cout << "FPS : " << 1.0f / m_deltatime << std::endl;
}

void Scene::InitCamera()
{
	m_Camera.position = Vector4(0, 0, -10, 1.0f);
	m_Camera.view = Vector4(0.f, 0.f, 1.0f, 0.0f);
	m_Camera.up = Vector4(0.f, 1.f, 0.f, 0.f);
	m_Camera.aspect = (real)(m_width) / (real)(m_height);
	m_Camera.fovy = PI / 4;
	m_Camera.znear = 1.0f;
	m_Camera.zfar = 1000.0f;
}

void Scene::InitCanvas()
{
	if (m_pCanvas)
	{
		delete m_pCanvas;
		m_pCanvas = nullptr;
	}
	m_pCanvas = new Canvas(m_width, m_height);
	m_pCanvas->SetViewPort(0, 0, m_width, m_height);
}

void Scene::OnMouseDown(WPARAM btnState, int x, int y)
{
	m_lastMousePos.x = x;
	m_lastMousePos.y = y;
	SetCapture(m_hWnd);
}

void Scene::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void Scene::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		float dx = 0.25 * (float)(x - m_lastMousePos.x);
		float dy = 0.25 * (float)(y - m_lastMousePos.y);

		m_Camera.RotateView(dx, dy);
	}

	m_lastMousePos.x = x;
	m_lastMousePos.y = y;
}

void Scene::OnKeyDown(WPARAM btnState)
{
	switch (btnState)
	{
		case VK_SPACE:
		{
			RenderMode mode = m_pCanvas->GetRenderMode();
			if (RenderMode::RENDER_WIREFRAME == mode)
			{
				m_pCanvas->SetRenderMode(RenderMode::RENDER_TEXTURE2D);
			}
			else if (RenderMode::RENDER_TEXTURE2D == mode)
			{
				m_pCanvas->SetRenderMode(RenderMode::RENDER_WIREFRAME);
			}
			break;
		}

		case VK_UP:
		{
			for (Mesh& m : m_Meshes)
			{
				m.RotateSelfX(-3);
			}

			for (Model& m : m_Models)
			{
				m.RotateSelfX(-3);
			}
			break;
		}

		case VK_DOWN:
		{
			for (Mesh& m : m_Meshes)
			{
				m.RotateSelfX(3);
			}

			for (Model& m : m_Models)
			{
				m.RotateSelfX(3);
			}
			break;
		}

		case VK_LEFT:
		{
			for (Mesh& m : m_Meshes)
			{
				m.RotateSelfY(3);
			}

			for (Model& m : m_Models)
			{
				m.RotateSelfY(3);
			}
			break;
		}

		case VK_RIGHT:
		{
			for (Mesh& m : m_Meshes)
			{
				m.RotateSelfY(-3);
			}

			for (Model& m : m_Models)
			{
				m.RotateSelfY(-3);
			}
			break;
		}

		case 'W': 
		{
			m_Camera.Move(CameraMove::CAMERA_MOVE_FRONT, m_deltatime);
			break;
		}

		case 'A':
		{
			m_Camera.Move(CameraMove::CAMERA_MOVE_LEFT, m_deltatime);
			break;		
		}

		case 'S':
		{
			m_Camera.Move(CameraMove::CAMERA_MOVE_BACK, m_deltatime);
			break;
		}

		case 'D':
		{
			m_Camera.Move(CameraMove::CAMERA_MOVE_RIGHT, m_deltatime);
			break;
		}
	}
}
