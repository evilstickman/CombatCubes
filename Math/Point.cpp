#include "Point.h"

Point::Point(float x, float y, float z)
{
  m_vert[0] = x;
  m_vert[1] = y;
  m_vert[2] = z;
}

Point::~Point(void)
{
}
