#pragma once

class Point
{
public:
  Point(float x = 0.0, float y = 0.0, float z = 0.0);
  
  ~Point(void);

  float m_vert[3];
  float m_w;
};
