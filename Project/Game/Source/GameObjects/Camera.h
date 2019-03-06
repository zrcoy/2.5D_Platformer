#pragma once

#include "GameObject.h"
class Mesh;
class Material;
class Scene;


class Camera : public GameObject
{


protected:
    MyMatrix m_ViewMat;
    MyMatrix m_ProjMat;
    //GameObject* m_pObjToLook;
    vec3 m_LookAtPosition;
    vec3 m_PosOffset;
    GameObject* m_pObj;
public:
    Camera(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale/*, Mesh* pMesh, Material* pMaterial,GameObject* pObj*/);
    virtual ~Camera();

    virtual void Update(float deltatime) override;
    //virtual void Draw();

    MyMatrix GetViewMat() { return m_ViewMat; }
    MyMatrix GetProjMat() { return m_ProjMat; }

    //void SetObjToLook(GameObject* pObj) { m_pObjToLook = pObj; }

    void SetLookAtPosition(vec3 pos) { m_LookAtPosition = pos; }

    //void SetCameraAttri(vec3 eye, vec3 at);

    void SetObjectToFollow(GameObject* obj, vec3 posOffset);
};

