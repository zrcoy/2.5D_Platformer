#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"

#include "Mesh/Material.h"
#include "Camera.h"
#include "Game/Scene.h"


Camera::Camera(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale/*, Mesh* pMesh, Material* pMaterial, GameObject* pObj*/)
    : GameObject(pScene, name, pos, rot, scale, 0, 0)
    /*, m_pObjToLook(pObj)*/
{
    //m_ViewMat.SetIdentity();
    //m_ProjMat.SetIdentity();

    ////m_ProjMat.CreateOrtho(-10, 10, -10, 10, 0, 100);
    //m_ProjMat.CreatePerspectiveVFoV(60, 600.0f / 600.0f, 0.01f, 200.0f);


    ////m_ViewMat.CreateLookAtView(vec3(0, 0, -50), vec3(0, 1, 0), vec3(0, 0, 0));
    //m_ViewMat.CreateLookAtView(pos, vec3(0, 1, 0), pObj->GetPosition());

    m_LookAtPosition.Set(0, 0, 0);
    m_PosOffset = 0;
    m_pObj = nullptr;
}

Camera::~Camera()
{
    
}

void Camera::Update(float deltatime)
{
    //// camera offset to the object that is watching
    //vec3 cameraOffset = vec3(0, 20.0f, -20.0f);

    //m_ViewMat.CreateLookAtView(/*m_pObjToLook->GetPosition() +cameraOffset*/m_Position, vec3(0, 1, 0), m_pObjToLook->GetPosition());
    // Setup camera/view matrix.
    m_ViewMat.CreateLookAtView(m_Position, vec3(0, 1, 0), m_LookAtPosition);

    float windowWidth = (float)m_pScene->GetGame()->GetFramework()->GetWindowWidth();
    float windowHeight = (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight();
    m_ProjMat.CreatePerspectiveVFoV(45, windowWidth / windowHeight, 0.01f, 100.0f);

    if (m_pObj != nullptr)
    {
        m_Position = m_pObj->GetPosition() + m_PosOffset;
        m_LookAtPosition = m_pObj->GetPosition();
    }
    
}

void Camera::SetObjectToFollow(GameObject * obj, vec3 posOffset)
{
    m_PosOffset= posOffset;
    m_pObj = obj;
}

//void Camera::SetCameraAttri(vec3 eye,vec3 at)
//{
//    m_ViewMat.CreateLookAtView(eye, vec3(0, 1, 0), m_pObjToLook->GetPosition());
//}


