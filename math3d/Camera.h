#pragma once

#include "math3d/Matrix.h"

enum CameraMove
{
	CAMERA_MOVE_FRONT = 0,
	CAMERA_MOVE_BACK = 1,
	CAMERA_MOVE_LEFT = 2,
	CAMERA_MOVE_RIGHT = 3,
};

class Camera
{
public:
	
	Camera(uint32 nWidth = 800, uint32 nHeight = 600);

	void  Update();	

	const Matrix& View()const { return m_View; }
	const Matrix& Projection() const { return m_Projection; }

	void  RotateView(float dx, float dy);
	void  Move(CameraMove dir, float deltatime);
	void  CalcDirections();

	float znear;
	float zfar;
	float fovy;
	float aspect;
	float yaw;
	float pitch;

	Vector4 position;
	Vector4 up;
	Vector4 view;
	Vector4 right;

private:

	Matrix m_View;
	Matrix m_Projection;

};