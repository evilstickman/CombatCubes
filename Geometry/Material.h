#pragma once
#include <string>
#include <vector>

class CMaterial
{
public:
    CMaterial(void);
    ~CMaterial(void);

    void ApplyMaterial(void);

    std::string m_sName;
    int m_nId;
    
    float m_fAmbientColor[4];
    float m_fDiffuseColor[4];
    float m_fSpecularColor[4];
    float m_fEmissiveColor[4];
    float m_fSpecPower;
    float m_fEmissionFactor;
    std::string m_sTexture1;
    std::string m_sTexture2;

    std::vector<CMaterial> matLib;
};

