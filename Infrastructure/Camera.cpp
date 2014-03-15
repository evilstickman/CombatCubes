#include "Camera.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

Camera::Camera(Point eye, Point lookAt, Point up) : m_eye(eye), m_lookAt(lookAt), m_upAxis(up)
{
}

Camera::~Camera(void)
{
}

void Camera::SetCameraMatrix()
{

  // Just put the OpenGL code here for now. We'll shuffle it later if the need
  // for multiplatform support actually becomes pressing
  
  gluLookAt(  m_eye.m_vert[0], m_eye.m_vert[1], m_eye.m_vert[2], //0, 0, 10,
              m_lookAt.m_vert[0], m_lookAt.m_vert[1], m_lookAt.m_vert[2],
              m_upAxis.m_vert[0], m_upAxis.m_vert[1], m_upAxis.m_vert[2]);
}
