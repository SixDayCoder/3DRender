
#include "math3d/Camera.h"
#include "math3d/Utils.h"

Camera::Camera(uint32 nWidth, uint32 nHeight)
{	
	fovy   = PI / 4;
	znear  = 1.0f;
	zfar   = 1000.0f;
	aspect = (real)nWidth / (real)nHeight;
	yaw    = 90.0f;
	pitch  = 0.0f;

	position    = Vector4(0, 0, 0, 1);
	view        = Vector4(0, 0, 1, 0);
	up          = Vector4(0, 1, 0, 0);
	right       = Vector4(1, 0, 0, 0);
}

void Camera::Update()
{
	
	m_View = Utils::LookAt(position, position + view, up);
	m_Projection = Utils::Perspectivce(fovy, aspect, znear, zfar);
}

void Camera::RotateView(float dx, float dy)
{
	dx *= 0.1f;
	dy *= 0.1f;

	yaw += dx;
	pitch += dy;

	pitch = Utils::Clamp(pitch, -89.0f, 89.0f);

	CalcDirections();
}

void Camera::Move(CameraMove dir, float deltatime)
{
	real distance = deltatime * 15.0f;

	switch (dir)
	{
	case CameraMove::CAMERA_MOVE_FRONT:
		position += distance * view;
		break;
	case CameraMove::CAMERA_MOVE_BACK:
		position -= distance * view;
		break;
	case CameraMove::CAMERA_MOVE_LEFT:
		position -= distance * right;
		break;
	case CameraMove::CAMERA_MOVE_RIGHT:
		position += distance * right;
		break;
	default:
		break;
	}
}

void Camera::CalcDirections()
{
	Vector3 Front;
	Vector3 Right;
	Vector3 Up;

	float   radiansYaw = Radians(yaw);
	float   radiansPitch = Radians(pitch);

	Front.x = cos(radiansYaw) * cos(radiansPitch);
	Front.y = sin(radiansPitch);
	Front.z = sin(radiansYaw) * cos(radiansPitch);
	Front.Normalize();
	this->view = Front;

	Right = Vector3::Cross(Vector3::Up, view);
	Right.Normalize();
	this->right = Right;

	Up = Vector3::Cross(view, right);
	Up.Normalize();
	this->up = Up;
}
