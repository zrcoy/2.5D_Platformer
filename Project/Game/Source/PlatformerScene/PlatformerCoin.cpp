#include "GamePCH.h"



#include "Game/Game.h"
#include "Game/MyPool.h"
#include "Game/Scene.h"
#include "GameObjects/GameObject.h"
#include "PlatformerCoin.h"
#include "Mesh/Mesh.h"
#include "Mesh/Material.h"
#include "Game/RemoveFromSceneEvent.h"

PlatformerCoin::PlatformerCoin(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_pPoolThisObjectCameFrom = 0;
}

PlatformerCoin::~PlatformerCoin()
{
}

void PlatformerCoin::Reset()
{
    assert(m_pScene != 0);

    RemoveFromSceneEvent* pEvent = new RemoveFromSceneEvent(this);
    m_pScene->GetGame()->GetEventManager()->QueueEvent(pEvent);
}

bool PlatformerCoin::RemoveFromScene()
{
    if (GameObject::RemoveFromScene())
    {
        b2Body* pBody = GetBody();
        pBody->SetActive(false);
        pBody->SetLinearVelocity(b2Vec2(0, 0));
        pBody->SetAngularVelocity(0);
        pBody->SetTransform(b2Vec2(-10000, -10000), 0);

        if (m_pPoolThisObjectCameFrom)
        {
            m_pPoolThisObjectCameFrom->AddObjectToPool(this);
        }

        return true;
    }

    return false;
}

void PlatformerCoin::Update(float deltatime)
{
    GameObject::Update(deltatime);
}

void PlatformerCoin::SetPool(MyPool<GameObject*>* pPool)
{
    m_pPoolThisObjectCameFrom = pPool;
}

void PlatformerCoin::BeginContact(b2Fixture* pOtherFixture, vec2 worldPosition, vec2 worldNormal)
{
    GameObject::BeginContact(pOtherFixture, worldPosition, worldNormal);
}

void PlatformerCoin::EndContact(b2Fixture* pOtherFixture)
{
    GameObject::EndContact(pOtherFixture);
}
