#include "Face.h"


Face::Face(unsigned int v1, unsigned int v2, unsigned int v3, Vertex n1, Vertex n2, Vertex n3)
{
    m_verts[0] = v1;
    m_verts[1] = v2;
    m_verts[2] = v3;
    m_normals[0] = n1;
    m_normals[1] = n2;
    m_normals[2] = n3;
}


Face::~Face(void)
{
}
