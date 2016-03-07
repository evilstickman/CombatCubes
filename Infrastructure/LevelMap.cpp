#include "LevelMap.h"
#include <fstream>
#include "Geometry\Mesh.h"


LevelMap::LevelMap(void)
{
}


LevelMap::~LevelMap(void)
{
    Mesh *m = NULL;
    SceneObject *s = NULL;
    for(std::vector<SceneObject *>::iterator iter  = m_lstModels.begin(); iter != m_lstModels.end(); ++iter)
    {
        s = (*iter);
        (*iter) = NULL;
        delete s;
    }
    for(std::map<std::string, Mesh *>::iterator iter  = m_modelLibrary.begin(); iter != m_modelLibrary.end(); ++iter)
    {
        m = (*iter).second;
        (*iter).second = NULL;
        delete m;
    }

}

void LevelMap::LoadFromFile( std::string filename )
{
    std::ifstream fIn(filename);
    std::string fname;
    float x, y,z;
    std::string shader_name, vert_shader_name, frag_shader_name;
    while(!fIn.eof())
    {
        // read file name, then x, y, z positions
        fIn>> fname;
        fIn >> x >> y >> z;
        fIn >> shader_name;
        vert_shader_name = "shaders\\"+shader_name+".vert";
        frag_shader_name = "shaders\\" + shader_name + ".frag";
        Mesh *m = NULL;
        SceneObject *s = NULL;
        Shader *shader = m_graphicsApp->GetShaderObject(vert_shader_name, frag_shader_name);
        shader->load_and_compile_shaders();
        // Save load time if we can
        if(m_modelLibrary.find(fname) == m_modelLibrary.end())
        {
            m = new Mesh();
            m->LoadFromFile(fname);
            m->SetShader(shader);
            m_modelLibrary[fname] = m;
        }
        s = new SceneObject(m_modelLibrary[fname]);
        s->SetXlate(x,y,z);
        m_lstModels.push_back(s);
    }
    fIn.close();
}

void LevelMap::Draw()
{

  for(std::vector<SceneObject *>::iterator iter  = m_lstModels.begin(); iter != m_lstModels.end(); ++iter)
  {
      (*iter)->draw();
  }
}

void LevelMap::ReloadShaders()
{
  for (std::vector<SceneObject *>::iterator iter = m_lstModels.begin(); iter != m_lstModels.end(); ++iter)
  {
    (*iter)->ReloadShaders();
  }

}
