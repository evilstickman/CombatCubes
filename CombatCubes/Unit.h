#pragma once
#include "Geometry\SceneObject.h"
class Unit
{
public:
  Unit();
  ~Unit();

  void addModel(SceneObject *unitModel);
  void draw() { m_unitModel->draw(); }

  SceneObject * m_unitModel;
};

