#pragma once
#include "Geometry\SceneObject.h"
#include "Geometry\Mesh.h"
#include <vector>
#include <map>
#include <string>

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
private:
    std::map<std::string, Mesh *> m_modelLibrary;
    std::vector<SceneObject *> m_lstModels;
};

