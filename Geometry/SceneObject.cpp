#include "SceneObject.h"
#include <windows.h>
#include <gl/gl.h>


SceneObject::SceneObject(Mesh *mesh) : m_baseMesh(mesh)
{
}


SceneObject::~SceneObject(void)
{
}


void SceneObject::SetXlate(float x, float y, float z)
{
    m_xlate[0]= x;
    m_xlate[1] = y;
    m_xlate[2] = z;
}

void SceneObject::draw()
{    
    glPushMatrix();
        glTranslated(m_xlate[0]*m_baseMesh->xDist, m_xlate[1]*m_baseMesh->yDist, m_xlate[2]*m_baseMesh->zDist);
        m_baseMesh->Draw();
    glPopMatrix();
}