#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	pos.x = 0.0f;
	pos.y = 1.75f;
	pos.z = 0.0;

	dir.x = 0.0f;
	dir.y = -0.5f;
	dir.z =-1.0f;

	speed.x = 0.0f;
	speed.y = 0.0f;
	speed.z = 0.0f;
}

Camera::~Camera()
{
}
