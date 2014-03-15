#pragma once
#include "Math\Point.h"

// Due to the structure, this class will necessarily serve as a parent to more
// engine-specific classes under the covers. Think "OpenGLCameraImpl," 
// "DirectXCameraImpl," etc. For now, though, just focus on making the OpenGL 
// stuff work. We'll abstract away what we can later.
class Camera
{
public:
    Camera(Point eye, Point lookAt, Point up);
    virtual ~Camera(void);

    virtual void SetCameraMatrix();

    Point m_eye;
    Point m_lookAt;
    Point m_upAxis;
};
