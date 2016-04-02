#include "Unit.h"



Unit::Unit() : m_unitModel(NULL)
{
}


Unit::~Unit()
{
}

void Unit::addModel(SceneObject *unitModel)
{
  m_unitModel = unitModel;
}