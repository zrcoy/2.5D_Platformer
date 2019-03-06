#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "PlatformerPlayer.h"
#include "GameObjects/PlayerController.h"
#include "Mesh/Material.h"
#include "PlatformerGround.h"

PlatformerPlayer::PlatformerPlayer(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
    , m_pPlayerController(nullptr)
    , m_CanJump(false)
    , m_RemainingJumpTimes(0)
    
{

   

}

PlatformerPlayer::~PlatformerPlayer()
{

}

void PlatformerPlayer::Update(float deltatime)
{
    GameObject::Update(deltatime);

    vec3 dir(0, 0, 0);

    if (m_pPlayerController)
    {
    

        if (m_pPlayerController->IsHeld_Left())
        {
            dir.x = -1;
            //m_Rotation.y = 180;
            m_FacingRight = false;
        }

        if (m_pPlayerController->IsHeld_Right())
        {
            dir.x = 1;
            //m_Rotation.y = 0;
            m_FacingRight = true;
        }
    }
    float force = 10.0f;
    m_pBody->ApplyForce(b2Vec2(force*dir.x, force*dir.y), m_pBody->GetWorldCenter(), true);
    
    


    float impulse = m_pBody->GetMass() * 5;
    // when press 'z'
    if (m_CanJump && m_pPlayerController->IsHeld_Jump())
    {
   
       
        if (m_RemainingJumpTimes > 0)
        {
            m_pBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_pBody->GetWorldCenter(), true);
            if (m_RemainingJumpTimes % 2 == 0)
            {
               
                m_pBody->ApplyAngularImpulse(-5.0f, true);
            }
            else if (m_RemainingJumpTimes % 2 == 1)
            {
                
                m_pBody->ApplyAngularImpulse(5.0f, true);

            }
         
            m_CanJump = false;
            // timer start working
            m_MultipleJumpTimer = DOUBLEJUMPDELAY;

            m_RemainingJumpTimes--;
           
        }
    }
     

    if (m_MultipleJumpTimer != 0) 
    {
        m_MultipleJumpTimer -= deltatime;
        if (m_MultipleJumpTimer <= 0) {
            // after this timer, player can do more jump
            m_CanJump = true;
            m_MultipleJumpTimer = 0;
        }
    }

    
}
    




void PlatformerPlayer::Draw(Camera* pCamera)
{
    // want both side when drawing player in order to show player sprite during rotation
    //glDisable(GL_CULL_FACE);

    //GameObject::Draw(pCamera);
    //glEnable(GL_CULL_FACE);

    if (m_pMesh != nullptr)
    {
 

        m_pMesh->SetupAttributes(m_pMaterial);

        // Create world matrix.
        MyMatrix worldMat;
        worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);
        m_pMesh->SetupUniforms(m_pMaterial, &worldMat, pCamera, m_FacingRight);
        m_pMesh->Draw(m_pMaterial);
    }
}

void PlatformerPlayer::OnEvent(Event * pEvent)
{
   
}

void PlatformerPlayer::BeginContact(b2Fixture * pOtherFixture, vec2 worldPosition, vec2 worldNormal)
{
    GameObject::BeginContact(pOtherFixture, worldPosition, worldNormal);


    auto other = (GameObject*)(pOtherFixture->GetUserData());
    if (other->GetName().compare(0, 6, "Ground")==0)
    {
        m_CanJump = true;
       
        // Reset remaining jump times
        m_RemainingJumpTimes = Total_GROUND_JUMP_TIMES;
    }

    else if (other->GetName().compare(0, 4, "Wall") == 0)
    {
        m_CanJump = true;
        m_RemainingJumpTimes = Total_WALL_JUMP_TIMES;
    }

}

void PlatformerPlayer::EndContact(b2Fixture * pOtherFixture)
{
    GameObject::EndContact(pOtherFixture);
}


