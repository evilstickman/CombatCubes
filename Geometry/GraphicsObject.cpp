#include "GraphicsObject.h"
#include <windows.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include "Material.h"

struct SFlatVert
{
    float m_v[3];
    float m_n[3];
    float m_tex[2];
    float m_fv[3];
    float padding[5];
};


GraphicsObject::GraphicsObject(void)
{
    glewInit();
    if(!GLEW_ARB_vertex_buffer_object)
    {
        _asm int 3;
    }
    m_bBufferCreated = false;
}


GraphicsObject::~GraphicsObject(void)
{
}

void GraphicsObject::SetVertexUV(int id, float u, float v)
{
    m_vertList[id].SetUV(u,v);
}

void GraphicsObject::AddVertex(Vertex vIn)
{
    m_vertList.push_back(vIn);
}

void GraphicsObject::AddFace(Face fIn)
{
    m_faceList.push_back(fIn);
}

void GraphicsObject::Draw()
{
    SFlatVert v;
    if(!m_bBufferCreated)
    {
        CreateVertexBuffer();
    }
    // do some pointer math to find the offset

    
    glBindBuffer(GL_ARRAY_BUFFER, m_nVBID);
    glVertexPointer(3, GL_FLOAT, sizeof(SFlatVert),0);
    glNormalPointer(GL_FLOAT, sizeof(SFlatVert), reinterpret_cast<void*>(12));
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    //glClientActiveTexture(GL_TEXTURE0);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);    //Notice that after we call glClientActiveTexture, we enable the array
    //glTexCoordPointer(2, GL_FLOAT, sizeof(v), reinterpret_cast<void*>(offsetof(Vertex,m_tex)));

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nIBID);
     glPushMatrix();
     glDrawElements(GL_TRIANGLES,m_faceList.size()*3,GL_UNSIGNED_INT,0);
     glPopMatrix();
    /*glPushMatrix();
    glBegin(GL_TRIANGLES);
        CMaterial::matLib[m_nMaterialId].ApplyMaterial();

        for(unsigned int i = 0; i < m_faceList.size(); ++i)
        {
            for(unsigned int j = 0; j < 3; ++j)
            {
                glTexCoord2fv(m_vertList[m_faceList[i].m_verts[j]].tbuf());
                glNormal3fv(m_faceList[i].m_normals[j].buf());
                glVertex3fv(m_vertList[m_faceList[i].m_verts[j]].buf());
            }
        }
    glEnd();
    glPopMatrix();*/
}

void GraphicsObject::SetMaterialID(int id)
{
    m_nMaterialId = id;
}

void GraphicsObject::SetXlate(float x, float y, float z)
{
    m_xlate[0]= x;
    m_xlate[1] = y;
    m_xlate[2] = z;
}


void GraphicsObject::CreateVertexBuffer()
{
    SFlatVert * vertArr = new SFlatVert[m_vertList.size()];
    unsigned int * indexArr = new unsigned int[m_faceList.size()*3];
    for(int i = 0; i < m_vertList.size(); ++i)
    {    
        vertArr[i].m_v[0] = m_vertList[i].m_v[0];
        vertArr[i].m_v[1] = m_vertList[i].m_v[1];
        vertArr[i].m_v[2] = m_vertList[i].m_v[2];
        vertArr[i].m_n[0] = m_vertList[i].m_n[0];
        vertArr[i].m_n[1] = m_vertList[i].m_n[1];
        vertArr[i].m_n[2] = m_vertList[i].m_n[2];
        vertArr[i].m_tex[0] = m_vertList[i].m_tex[0];
        vertArr[i].m_tex[1] = m_vertList[i].m_tex[1];
    }
    for(int i = 0; i < m_faceList.size(); ++i)
    {
        indexArr[i*3] = m_faceList[i].m_verts[0];
        indexArr[i*3+1] = m_faceList[i].m_verts[1];
        indexArr[i*3+2] = m_faceList[i].m_verts[2];
    }
    // generate a new VBO and get the associated ID
    glGenBuffers(1, &m_nVBID);

    // bind VBO in order to use
    glBindBuffer(GL_ARRAY_BUFFER, m_nVBID);

    glBufferData(GL_ARRAY_BUFFER, 64 * m_vertList.size(), vertArr,GL_STATIC_DRAW);

    glGenBuffers(1, &m_nIBID);

    // bind index buffer in order to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nIBID);

    // Fill it with data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_faceList.size() * 3, indexArr, GL_STATIC_DRAW);
    // buffer created
    m_bBufferCreated = true;
}


void GraphicsObject::AddNormalToVertex(int vertId, float x, float y, float z)
{
    m_vertList[vertId].addNormal(x,y,z);
}