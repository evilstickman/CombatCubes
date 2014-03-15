#pragma once
class Vertex
{
public:
    Vertex(float x = 0.0, float y = 0.0, float z = 0.0, float u = 0.0, float v = 0.0);
    ~Vertex(void);

    void SetUV(float u, float v){ m_tex[0] = u; m_tex[1] = v;}

    float * buf() { return m_v;} 
    float * tbuf() { return m_tex;}
    float * fbuf() { return m_fv; }
    void addNormal(float x, float y, float z);

    float m_v[3];
    float m_n[3];
    float m_tex[2];
    float m_fv[3];
    float padding[5];
};

