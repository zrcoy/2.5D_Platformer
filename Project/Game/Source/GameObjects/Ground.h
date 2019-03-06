#pragma once

class GameObject;
class Mesh;


class Ground : public GameObject
{
 

protected:



public:
    Ground(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~Ground();

    virtual void Update(float deltatime) override;
    virtual void Draw(Camera* pCamera);




};

