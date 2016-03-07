#pragma once
#include "Geometry\SceneObject.h"
#include "GraphicsApplication.h"
#include "Geometry\Shader.h"
#include "Geometry\Mesh.h"
#include <vector>
#include <map>
#include <string>
#include <set>

struct SMapCell
{
   
};

class LevelMap
{
public:
    LevelMap(void);
    ~LevelMap(void);

    void LoadFromFile( std::string filename );

    void Draw();

    inline void SetGraphicsApp(GraphicsApplication * graphics_app) { m_graphicsApp = graphics_app; }
    inline GraphicsApplication* GetGraphicsApp() { return m_graphicsApp; }

    void ReloadShaders();
private:
    std::map<std::string, Mesh *> m_modelLibrary;
    std::vector<SceneObject *> m_lstModels;
    GraphicsApplication *m_graphicsApp;
};

