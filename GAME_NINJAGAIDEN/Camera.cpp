#include "Camera.h"





Camera::Camera(int w, int h)
{
	_width = w;
	_height = h;

	isAllowFollowAladdin = true;

	// Biên mặc định ban đầu là kích thước MAP
	_boundaryLeft = 0;
	_boundaryRight = 0;// (float)(MapWidth - SCREEN_WIDTH);
	_boundaryTop = 0;
	_boundaryBottom = 0;
	_xCamBackup = _yCamBackup = 0;
	vx = 0;
}

Camera::~Camera()
{
}

void Camera::Update(DWORD dt)
{
	this->dt = dt;

	if (_xCam < _boundaryLeft)
		_xCam = _boundaryLeft;

	if (_xCam > _boundaryRight)
		_xCam = _boundaryRight;

	if (_yCam < _boundaryTop)
		_yCam = _boundaryTop;

	if (_yCam > _boundaryBottom)
		_yCam = _boundaryBottom;

}
D3DXVECTOR2 Camera::Transform(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - _xCam, yWorld - _yCam);
}

void Camera::SetPosition(float x, float y)
{
	_xCam = x;
	_yCam = y;
}

float Camera::GetXCam()
{
	return _xCam;
}

float Camera::GetYCam()
{
	return _yCam;
}


int Camera::GetWidth()
{
	return _width;
}

int Camera::GetHeight()
{
	return _height;
}

bool Camera::checkObjectInCamera(float x, float y, float w, float h)
{
	if (x + w < _xCam || _xCam + _width < x)
		return false;
	if (y + h < _yCam || _yCam + _height < y)
		return false;
	return true;
}


bool Camera::AllowFollowAladdin()
{
	return isAllowFollowAladdin;
}



void Camera::SetAllowFollowAladdin(bool b)
{
	isAllowFollowAladdin = b;
}


void Camera::SetBoundary(float left, float right,float top, float bottom)
{
	_boundaryLeft = left;
	_boundaryRight = right;
	_boundaryTop = top;
	_boundaryBottom = bottom;
}

float Camera::GetBoundaryRight()
{
	return _boundaryRight;
}

float Camera::GetBoundaryLeft()
{
	return _boundaryLeft;
}

float Camera::GetBoundaryTop()
{
	return _boundaryTop;
}

float Camera::GetBoundaryBottom()
{
	return _boundaryBottom;
}

void Camera::SetPositionBackup(float X, float Y)
{
	_xCamBackup = X;
	_yCamBackup = Y;

}





void Camera::RestorePosition()
{
	_xCam = _xCamBackup;
	_yCam = _yCamBackup;
}
