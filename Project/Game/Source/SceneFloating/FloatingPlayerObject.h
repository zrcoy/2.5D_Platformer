#ifndef __FloatingPlayerObject_H__
#define __FloatingPlayerObject_H__

#include "FloatingObject.h"
#include "GameObjects/PlayerController.h"

class FloatingPlayerObject : public FloatingObject
{
protected:
    PlayerController* m_pController;

public:
    FloatingPlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~FloatingPlayerObject();

    void SetController(PlayerController* pController);

    virtual void Update(float deltatime);

    //void BeginContact(b2Fixture* pOtherFixture, vec2 worldPosition, vec2 worldNormal);
};

#endif //__FloatingPlayerObject_H__
