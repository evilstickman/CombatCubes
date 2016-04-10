#pragma once
#include <vector>
#include "Vertex.h"
#include "Face.h"
#include "Shader.h"


class GraphicsObject
{
public:
    GraphicsObject(void);
    virtual ~GraphicsObject(void);

    void AddVertex(Vertex vIn);
    void AddFace(Face fIn);

    void SetVertexUV(int id, float u, float v);

    void SetMaterialID(int id);
    
    void Draw();
    void DrawNormals();
    void SetXlate(float x  = 0.0, float y = 0.0, float z = 0.0);

    void CreateVertexBuffer();

    void AddNormalToVertex(int vertId, float x, float y, float z);

    std::vector<Vertex> m_vertList;
    std::vector<Face> m_faceList;
    float m_xlate[3];

    bool m_bBufferCreated;

    int m_nMaterialId;
    unsigned int m_nVBID;
    unsigned int m_nIBID;
};

