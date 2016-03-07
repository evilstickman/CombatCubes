#include "Mesh.h"
#include <fstream>
#include <windows.h>
#include <GL/glew.h>
#include <gl/gl.h>
#include "Vertex.h"
#include "Face.h"

Mesh::Mesh(void)
{
}


Mesh::~Mesh(void)
{
}

void Mesh::LoadFromFile( std::string filename )
{
  
  std::ifstream fIn(filename);
  LoadAsciiFormat(fIn);
}

void Mesh::LoadAsciiFormat( std::ifstream &fIn)
{
  std::string line;
  //- leading comment
  std::getline(fIn,line);
  //- line break
  std::getline(fIn,line);
  //- Frames: 30 // total frame count
  std::getline(fIn,line);
  //- Frame: 1 // current frame
  std::getline(fIn,line);
  // - Line Break  
  std::getline(fIn,line);
  //- Meshes: 11 // number of meshes in the scene
  int meshCount;
  // skip meshes identifier
  fIn >> line;
  // get mesh count;
  fIn >> meshCount;

  vMin.buf()[0] = vMin.buf()[1] = vMin.buf()[2] = 999999.0;  
  vMax.buf()[0] = vMax.buf()[1] = vMax.buf()[2] = -999999.0;

  for(int i = 0; i < meshCount; ++i)
  {
    GraphicsObject *obj = new GraphicsObject();
    int materialId = 0;
    int vertexCount = 0;
	  // - Mesh name, selected?, materialID
    fIn >> line >> materialId >> materialId;
	  // - vertex count
    fIn >> vertexCount;
    for(int j = 0; j < vertexCount; ++j)
    {
      int currSelection, endNumber;
      float x, y, z, s, t;
      //  - selected?, x, y, z, s, t, some number
      fIn >> currSelection >> x >> y >> z >> s >> t >> endNumber;

      Vertex v(x,y,z,s,t);

      AdjustMinMax(x,y,z);
      
      obj->AddVertex(v);
    }

	  // - normal count
    int normalCount = 0;
    std::vector<Vertex> nArr;
    fIn>> normalCount;
    for(int j = 0; j < normalCount; ++j)
    {
      float x, y, z;
		  //  - x, y, z
      fIn >> x >> y >> z;

      Vertex n(x,y,z);
      nArr.push_back(n);
      
    }
	  // - Face count
    int faceCount = 0;
    fIn >> faceCount;
    for(int j = 0; j < faceCount; ++j)
    {
		  //  - selected?, v1, v2, v3, normal1, normal2, normal3, number
      int selected, v1, v2, v3, n1, n2, n3, other;
      fIn >> selected >> v1 >> v2 >> v3 >> n1 >> n2 >> n3 >> other;

      Face f(v1,v2,v3,nArr[n1],nArr[n2],nArr[n3]);
      obj->AddFace(f);
      obj->AddNormalToVertex(v1, nArr[n1].m_v[0], nArr[n1].m_v[1], nArr[n1].m_v[2]);
      obj->AddNormalToVertex(v2, nArr[n2].m_v[0], nArr[n2].m_v[1], nArr[n2].m_v[2]);
      obj->AddNormalToVertex(v3, nArr[n3].m_v[0], nArr[n3].m_v[1], nArr[n3].m_v[2]);
    }

    obj->SetMaterialID(materialId);
    // store the mesh
    m_objectList.push_back(obj);
  }
  //- Materials: 3 // number of materials in the scene
  int materialCount = 0;
  // skip materials identifier
  fIn >> line >> materialCount;

  for(int i = 0; i < materialCount; ++i)
  {
    CMaterial mat;
	   // - name
    fIn>>mat.m_sName;
	   // - ambient r, ambient g, ambient b, ambient alpha
    fIn >> mat.m_fAmbientColor[0]>> mat.m_fAmbientColor[1]>> mat.m_fAmbientColor[2]>> mat.m_fAmbientColor[3];
	   // - diffuse r, diffuse g, diffuse b, diffuse alpha
    fIn >> mat.m_fDiffuseColor[0]>> mat.m_fDiffuseColor[1]>> mat.m_fDiffuseColor[2]>> mat.m_fDiffuseColor[3];
	   // - specular r, specular g, specular b, specular alpha
    fIn >> mat.m_fSpecularColor[0]>> mat.m_fSpecularColor[1]>> mat.m_fSpecularColor[2]>> mat.m_fSpecularColor[3];
	   // - emissive r, emissive g, emissive b, emissive alpha
    fIn >> mat.m_fEmissiveColor[0]>> mat.m_fEmissiveColor[1]>> mat.m_fEmissiveColor[2]>> mat.m_fEmissiveColor[3];
	   // - specular power/roughness
    fIn >> mat.m_fSpecPower;
	   // - emission factor
    fIn >> mat.m_fEmissionFactor;
	   // - texture 1 name
     fIn >> mat.m_sTexture1;
	   // - texture 2 name
     fIn >> mat.m_sTexture2;
     m_matlib.matLib.push_back(mat);
  }
}

void Mesh::LoadTxtFormat( std::ifstream &fIn)
{
  std::string line;
  //mesh format line: string, int
  std::getline(fIn,line);
  //object count: int
  //std::getline(fIn,line);
  int objcount = 0;
  fIn >> objcount;
  //objects:
  for(int i = 0; i < objcount; ++i)
  {
    GraphicsObject *obj = new GraphicsObject();
    // object name: string
    fIn >> line;
    // vertex count: int
    int vertcount = 0;
    fIn >> vertcount;
    // vertices:
    for(int j = 0; j < vertcount; ++j)
    {
      float x, y, z;
      x = y = z = 0.0;
      
      // vertex: x, y, z
      fIn >> x >> y >> z;

      Vertex v(x,y,z);
      
      obj->AddVertex(v);
    }
    
    // face count: int
    int facecount = 0;
    fIn >> facecount;
    // faces:
    for(int j = 0; j < facecount; ++j)
    {
      int sgroup, v1, v2, v3;
      sgroup = v1 = v2 = v3 = 0;
      
      float x1, y1, z1, s1, t1;
      float x2, y2, z2, s2, t2;
      float x3, y3, z3, s3, t3;
      x1 = y1 = z1 = s1 = t1 = 0.0;
      x2 = y2 = z2 = s2 = t2 = 0.0;
      x3 = y3 = z3 = s3 = t3 = 0.0;
      Vertex n1,n2, n3;

      
      // face: smoothing group<int>, v1<int>, v2<int>, v3<int>, n-v1<x,y,z>, n-v2<x,y,z>, n-v3<x,y,z>, v1 tex<u,v>, v2 tex<u,v>, v3 tex<u,v>
      fIn >> sgroup >> v1 >> v2 >> v3;
      fIn >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> s1 >> t1 >> s2 >> t2 >> s3 >> t3;
      n1 = Vertex(x1, y1, z1, s1, t1);
      n2 = Vertex(x2, y2, z2, s2, t2);
      n3 = Vertex(x3, y3, z3, s3, t3);      

      Face f(v1, v2, v3, n1, n2, n3);
      obj->SetVertexUV(v1, s1, t1);
      obj->SetVertexUV(v2, s2, t2);
      obj->SetVertexUV(v3, s3, t3);
      obj->AddFace(f);
    }
    m_objectList.push_back(obj);
  }
}


void Mesh::SetShader(Shader *shader)
{
  m_shader = shader;
}

void Mesh::Draw()
{

  glEnable(GL_LIGHTING);
  GLfloat lightpos[] = { -10, 5, -10., 0. };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  for(std::vector<GraphicsObject *>::iterator iter = m_objectList.begin(); iter != m_objectList.end(); ++iter)
  {
    this->m_matlib.matLib[(*iter)->m_nMaterialId].ApplyMaterial();
    glUseProgram(m_shader->get_program_object_handle());
    (*iter)->Draw();
    glUseProgram(0);
  }
  glDisable(GL_LIGHTING);
  glPopMatrix();
}


void Mesh::AdjustMinMax(float x, float y, float z)
{
  if(x > vMax.buf()[0])
  {
    vMax.buf()[0] = x;
  }
  if(x < vMin.buf()[0])
  {
    vMin.buf()[0] = x;
  }
  if(y > vMax.buf()[1])
  {
    vMax.buf()[1] = y;
  }
  if(y < vMin.buf()[1])
  {
    vMin.buf()[1] = y;
  }
  if(z > vMax.buf()[2])
  {
    vMax.buf()[2] = z;
  }
  if(z < vMin.buf()[2])
  {
    vMin.buf()[2] = z;
  }
  xDist = vMax.buf()[0] - vMin.buf()[0];
  yDist = vMax.buf()[1] - vMin.buf()[1];
  zDist = vMax.buf()[2] - vMin.buf()[2];
}

void Mesh::ReloadShaders()
{
  m_shader->load_and_compile_shaders();
}