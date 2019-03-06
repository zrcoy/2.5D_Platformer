#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Mesh/Material.h"

Player::Player(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
    , m_pPlayerController(nullptr)
    , m_Speed(PLAYER_SPEED)
{
    // Set the Player's initial position.
    //m_Position.Set(-5.0f, 20.0f, 0);
}

Player::~Player()
{

}

void Player::Update(float deltatime)
{
    GameObject::Update(deltatime);

    //if (m_pBody != nullptr)
    //{
    //    b2Vec2 physicsPos = m_pBody->GetPosition();
    //    float32 physicsAngle = m_pBody->GetAngle();
    //    ImGui::Text("Player's physics Y : %f", physicsPos.y);
    //    ImGui::Text("Player's physics X : %f", physicsPos.x);

    //    // make the cube's graphic follow the physics body
    //    //if (m_Position.y > 1.0f)
    //   /* {
    //        m_Position.y = physicsPos.y;
    //        m_Position.x = physicsPos.x;
    //        m_Angle = -physicsAngle / PI * 180.0f;
    //    }*/
    //     ImGui::Text("");
    //     ImGui::Text("Player's graphics Y : %f", m_Position.y);
    //     ImGui::Text("Player's graphics X : %f", m_Position.x);
    //}

    

    //GameObject::Update( deltatime );

    vec2 dir(0, 0);

    if (m_pPlayerController)
    {
        if (m_pPlayerController->IsHeld_Up())
        {
            dir.y = 1;
        }

        if (m_pPlayerController->IsHeld_Down())
        {
            dir.y = -1;
        }

        if (m_pPlayerController->IsHeld_Left())
        {
            dir.x = -1;

        }

        if (m_pPlayerController->IsHeld_Right())
        {
            dir.x = 1;
        }
    }
    float force = 10.0f;
    m_pBody->ApplyForce(b2Vec2(force*dir.x, force*dir.y), m_pBody->GetWorldCenter(), true);
    // m_Position += dir * m_Speed * deltatime;

     // why I can not do this
     //m_pBody->SetTransform(b2Vec2(m_Position.x, m_Position.y), m_Angle);

     //m_Angle += 1;
}


void Player::Draw(Camera* pCamera)
{
    GameObject::Draw(pCamera);

    //ImGui::Begin("Second Scene");
    //static float scale = 4.0f;
    //static vec3 rotate = vec3(0, 0, 0);
    //ImGui::SliderFloat("Scale", &scale, 1.0f, 5.0f);
    //ImGui::SliderFloat("Rotate_x", &rotate.x, 0.0f, 360.0f);
    //ImGui::SliderFloat("Rotate_y", &rotate.y, 0.0f, 360.0f);
    //ImGui::SliderFloat("Rotate_z", &rotate.z, 0.0f, 360.0f);
    //ImGui::End();

    //if (m_pMesh != nullptr)
    //{
    //    MyMatrix worldMat;
    //    MyMatrix viewMat;
    //    MyMatrix projMat;
    //    //m_Rotation = rotate;
    //    m_Rotation = vec3(0, 0, m_Angle);
    //    //m_Scale = vec3(scale, scale, scale);
    //    //m_Scale = vec3(1, 1, 1);
    //    worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);
    //    //viewMat.SetIdentity();
    //    //projMat.SetIdentity();
    //    m_pMesh->SetupAttributes(m_pMaterial);
    //    m_pMesh->SetupUniforms(m_pMaterial, &worldMat/*, viewMat, projMat*/, pCamera);
    //    //m_pMesh->SetupTool();
    //    m_pMesh->Draw(m_pMaterial);
    //}

}
