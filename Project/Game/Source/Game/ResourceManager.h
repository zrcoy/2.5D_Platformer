#pragma once
#include <map>

class Mesh;
class Texture;
class ShaderProgram;

#include "Mesh/Material.h"

class ResourceManager
{
protected:
    std::map<std::string, Mesh*> m_pMeshes;
    std::map<std::string, Texture*> m_pTextures;
    std::map<std::string, ShaderProgram*> m_pShader;
    std::map<std::string, Material*> m_pMaterials;
public:
    ResourceManager();
    ~ResourceManager();

    Mesh* AddMesh(std::string name, Mesh* mesh);
    Mesh* GetMesh(std::string name);

    void AddTexture(std::string name, Texture* texture);
    Texture* GetTexture(std::string name);

    void AddShader(std::string name, ShaderProgram* shader);
    ShaderProgram* GetShader(std::string name);

    void AddMaterial(std::string name, Material* pMaterial);
    Material*      GetMaterial(const std::string name);
};