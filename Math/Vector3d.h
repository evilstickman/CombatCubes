#pragma once

class Vector3d
{
public:
  Vector3d(float x = 0.0, float y = 0.0, float z = 0.0);
  ~Vector3d(void);

  float m_vert[3];
  float m_w;
};
