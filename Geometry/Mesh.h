#pragma once

#include <vector>
#include <string>
#include "GraphicsObject.h"
#include "Material.h"
// store mesh as list of vertices with normals and uvs, and list of face indices - triangles. Problem is need to calculate vertex normals,

class Mesh
{
public:
    Mesh(void);
    ~Mesh(void);

    void LoadFromFile( std::string filename );
    void LoadTxtFormat( std::ifstream &fIn);
    void LoadAsciiFormat( std::ifstream &fIn);
    void SetShader(Shader *shader);
    void Draw();

    void ReloadShaders();


    void AdjustMinMax(float x, float y, float z);

    std::vector<GraphicsObject *> m_objectList;

    Vertex vMin, vMax;
    float xDist, yDist, zDist;

    CMaterial m_matlib;

    Shader *m_shader;
};

