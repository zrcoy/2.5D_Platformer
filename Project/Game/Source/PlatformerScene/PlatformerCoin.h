#pragma once

#include "Game/MyPool.h"
#include "GameObjects/GameObject.h"

class PlatformerCoin : public GameObject
{
protected:
    MyPool<GameObject*>* m_pPoolThisObjectCameFrom;

public:
    PlatformerCoin(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~PlatformerCoin();

    virtual void Reset() override;
    virtual bool RemoveFromScene() override;

    virtual void Update(float deltatime) override;

    void SetPool(MyPool<GameObject*>* pPool);

    virtual void BeginContact(b2Fixture* pOtherFixture, vec2 worldPosition, vec2 worldNormal);
    virtual void EndContact(b2Fixture* pOtherFixture);
};



