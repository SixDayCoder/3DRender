#pragma once
#include "device/Canvas.h"
#include "math3d/Model.h"
#include "math3d/Light.h"
#include "math3d/Camera.h"

#include <windows.h>
#include <memory>
#include <ctime>

class Scene
{
public:

	Scene();
	~Scene();

	bool Init(HINSTANCE hInstance, HWND hWnd);
	void InitCamera();
	void InitCanvas();
	bool IsValid() { return m_bInit; }

	void Update();
	void Render();
	void TickTime();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
	void OnKeyDown(WPARAM btnState);

	void AddMesh(const Mesh& mesh) { m_Meshes.push_back(mesh); }
	void AddModel(const Model& model) { m_Models.push_back(model); }

	uint32*& GetCanvasBuffer() { return m_pCanvas->GetFrameBuffer(); }

private:

	HINSTANCE	m_hInstance;
	HWND  m_hWnd;
	POINT m_lastMousePos;

	int	   m_width;
	int    m_height;
	bool   m_bInit;

	clock_t  m_lasttime;
	double   m_deltatime;
		
	Camera             m_Camera;
	Canvas*            m_pCanvas;
	
	vector<Mesh> m_Meshes;
	vector<Model> m_Models;
};

