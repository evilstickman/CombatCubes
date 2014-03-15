#pragma once
#include "Vertex.h"

class Face
{
public:
    Face(unsigned int v1, unsigned int v2, unsigned int v3, Vertex n1, Vertex n2, Vertex n3);
    ~Face(void);

    Vertex m_normals[3];
    unsigned int m_verts[3];
};

