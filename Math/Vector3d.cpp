#include "Vector3d.h"

Vector3d::Vector3d(float x, float y, float z)
{
  m_vert[0] = x;
  m_vert[1] = y;
  m_vert[2] = z;
}

Vector3d::~Vector3d(void)
{
}
