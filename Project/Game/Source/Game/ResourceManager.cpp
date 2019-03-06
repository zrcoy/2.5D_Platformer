#include "GamePCH.h"
#include <string>
#include "ResourceManager.h"
#include "Mesh/Mesh.h"
#include "assert.h"
#include "Mesh/Texture.h"

using namespace std;

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
  /*  for (map<string, Mesh*>::iterator it = m_pMeshes.begin; it != m_pMeshes.end; it++)
    {
        delete it->second;
        
    }
*/
    for (auto object : m_pMeshes)
        delete object.second;


    for (auto object : m_pMaterials)
        delete object.second;

    for (auto object : m_pTextures)
        delete object.second;

    for (auto object : m_pShader)
        delete object.second;
}

Mesh* ResourceManager::AddMesh(string name, Mesh* mesh)
{
    // make sure this mesh not exist,so that we can add it
    assert(m_pMeshes.find(name) == m_pMeshes.end());
    //m_pMeshes.insert(pair<string, Mesh*>(name, mesh));
    m_pMeshes[name] = mesh;
    return mesh;
}

Mesh* ResourceManager::GetMesh(string name)
{
    // make sure this mesh exist
    if (m_pMeshes.find(name) != m_pMeshes.end())
    {
        return m_pMeshes[name];
    }
    else
    {
        assert(false); // REsource wasn't found
        return nullptr;
    }
}

void ResourceManager::AddTexture(string name, Texture* texture)
{
    // make sure this mesh not exist,so that we can add it
    assert(m_pTextures.find(name) == m_pTextures.end());
    m_pTextures.insert(pair<string, Texture*>(name, texture));
}

Texture* ResourceManager::GetTexture(string name)
{
    // make sure this mesh exist
    if (m_pTextures.find(name) != m_pTextures.end())
    {
        return m_pTextures[name];
    }
    else
    {
        assert(false); // REsource wasn't found
        return nullptr;
    }
}

void ResourceManager::AddShader(string name, ShaderProgram* shader)
{
    // make sure this mesh not exist,so that we can add it
    assert(m_pShader.find(name) == m_pShader.end());
    m_pShader.insert(pair<string, ShaderProgram*>(name, shader));
}

ShaderProgram* ResourceManager::GetShader(string name)
{
    // make sure this mesh exist
    if (m_pShader.find(name) != m_pShader.end())
    {
        return m_pShader[name];
    }
    else
    {
        assert(false); // REsource wasn't found
        return nullptr;
    }
}

void ResourceManager::AddMaterial(std::string name, Material* pMaterial)
{
    assert(m_pMaterials.find(name) == m_pMaterials.end());

    m_pMaterials[name] = pMaterial;
}

Material* ResourceManager::GetMaterial(std::string name)
{
    auto it = m_pMaterials.find(name);
    if (it == m_pMaterials.end())
        return nullptr;

    return it->second;
}

