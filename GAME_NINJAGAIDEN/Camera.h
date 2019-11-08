#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h" 

class Camera
{
protected:
	float _xCam; //toa độ x cam
	float _yCam; //tọa đô y cam

	float _xCamBackup;
	float _yCamBackup;


	int _width; //chiều rộng 
	int _height; //chiều cao

	float _boundaryLeft; // biên giới hạn bên trái 
	float _boundaryRight; // biên giới hạn bên phải
	float _boundaryTop; //biên gới hạn trên
	float _boundaryBottom; //biên giới hạn dưới
	

	float vx; 
	DWORD dt;


	bool isAllowFollowAladdin; //theo aladdin

public:
	Camera(int w, int h);
	~Camera();

	void Update(DWORD dt);

	D3DXVECTOR2 Transform(float, float);

	void SetPosition(float x, float y);

	float GetXCam();
	float GetYCam();
	int GetWidth();
	int GetHeight();

	bool checkObjectInCamera(float x, float y, float w, float h);

	
	bool AllowFollowAladdin();
	void SetAllowFollowAladdin(bool b);

	void SetBoundary(float left, float right, float top, float bottom); // set biên giới hạn cho camera
	float GetBoundaryRight();
	float GetBoundaryLeft();
	float GetBoundaryTop();
	float GetBoundaryBottom();

	void SetPositionBackup(float X, float Y);
	void RestorePosition();


	
};

#endif



