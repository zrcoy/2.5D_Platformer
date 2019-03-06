#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Ground.h"
#include "Mesh/Material.h"


Ground::Ground(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    // Set the Ground's initial position.
    //m_Position.Set(2.0f, 0.0f, 0);
}

Ground::~Ground()
{
}

void Ground::Update(float deltatime)
{
    GameObject::Update(deltatime);

    if (m_pBody != nullptr)
    {
       /* b2Vec2 physicsPos = m_pBody->GetPosition();
        float32 physicsAngle = m_pBody->GetAngle();*/
     /*   ImGui::Text("Ground's Y : %f", physicsPos.y);
        ImGui::Text("Ground's X : %f", physicsPos.x);*/

        // make the cube's graphic follow the physics body
        //if (m_Position.y > 1.0f)
       /* {
            m_Position.y = physicsPos.y;
            m_Position.x = physicsPos.x;
            m_Angle = -physicsAngle / PI * 180.0f;
        }*/


       /* ImGui::Text("");
        ImGui::Text("Ground's graphics Y : %f", m_Position.y);
        ImGui::Text("Ground's graphics X : %f", m_Position.x);
        ImGui::Text("Ground angle:  %f", physicsAngle);
        ImGui::Text("Local pivot:  %f, %f", m_pBody->GetLocalCenter().x, m_pBody->GetLocalCenter().y);*/
    }





   // m_Angle += 1;
}


void Ground::Draw(Camera* pCamera)
{
    //ImGui::Begin("Graphic Scene");
    //static float scale = 1.0f;
    //static vec3 rotate = vec3(0, 0, 0);
    //ImGui::SliderFloat("Scale", &scale, 1.0f, 5.0f);
    //ImGui::SliderFloat("Rotate_x", &rotate.x, 0.0f, 360.0f);
    //ImGui::SliderFloat("Rotate_y", &rotate.y, 0.0f, 360.0f);
    //ImGui::SliderFloat("Rotate_z", &rotate.z, 0.0f, 360.0f);
    //ImGui::End();

    if (m_pMesh != nullptr)
    {
        MyMatrix worldMat;
        MyMatrix viewMat;
        MyMatrix projMat;
        m_Rotation = vec3(0, 0, m_Angle);
        //m_Scale = vec3(1, 50, 1);
        worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);
        //viewMat.SetIdentity();
       // projMat.SetIdentity();
        m_pMesh->SetupAttributes(m_pMaterial);
        m_pMesh->SetupUniforms(m_pMaterial, &worldMat/*, viewMat, projMat*/,pCamera);
        //m_pMesh->SetupTool();
        m_pMesh->Draw(m_pMaterial);
    }
   /* if (m_pMesh != nullptr)
    {
        m_pMesh->SetupAttributes(m_pShader);
        m_pMesh->SetupUniforms(m_pShader, m_Position, m_Angle, 1, camPos, projScale, m_pTexture);
        m_pMesh->Draw(m_pShader);
    }*/

}
