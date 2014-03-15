#include "Material.h"
#include <windows.h>
#include <gl/gl.h>


std::vector<CMaterial> CMaterial::matLib;

CMaterial::CMaterial(void)
{
}


CMaterial::~CMaterial(void)
{
}
    

void CMaterial::ApplyMaterial(void)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->m_fAmbientColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->m_fDiffuseColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->m_fSpecularColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, this->m_fEmissiveColor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->m_fSpecPower); 
    glColor3fv(this->m_fDiffuseColor);
}
