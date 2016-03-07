#pragma once
#include "Mesh.h"
class SceneObject
{
public:
    SceneObject(Mesh *mesh);
    ~SceneObject(void);

    void SetXlate(float x  = 0.0, float y = 0.0, float z = 0.0);

    void draw();

    void ReloadShaders();
    
    float m_transformation[16];

    float m_xlate[3];

private:
    Mesh * m_baseMesh;
};

