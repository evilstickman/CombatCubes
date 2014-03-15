#include "Vertex.h"
#include <math.h>


Vertex::Vertex(float x, float y, float z, float u, float v)
{
    m_v[0] = x;
    m_v[1] = y;
    m_v[2] = z;
    m_n[0] = 0;
    m_n[1] = 0;
    m_n[2] = 0;
    m_tex[0] = u;
    m_tex[1] = v;
    m_fv[0] = x;
    m_fv[1] = y;
    m_fv[2] = z;
}


Vertex::~Vertex(void)
{
}

void Vertex::addNormal(float x, float y, float z)
{ 
    float mag = 0.0;
    m_n[0] +=x;  
    m_n[1] +=y;  
    m_n[2] +=z; 

    mag = m_n[0] * m_n[0] + m_n[1] * m_n[1] + m_n[2] * m_n[2];
    mag = sqrt(mag);
    
    m_n[0] /= mag;
    m_n[1] /= mag;
    m_n[2] /= mag;
}