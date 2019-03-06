#ifndef __FloatingMineObject_H__
#define __FloatingMineObject_H__

#include "FloatingObject.h"

class FloatingMineObject : public FloatingObject
{
private:
    //use for keep tracking each mine's angle towards player
    float m_angleRotateAroundPlayer;

public:
    bool m_AttachedToPlayer;

public:
    FloatingMineObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~FloatingMineObject();

    virtual void Update(float deltatime);
    void SetAngleRotating(float f) { m_angleRotateAroundPlayer = f; }
    float GetAngleRotating() { return m_angleRotateAroundPlayer; }
};

#endif //__FloatingMineObject_H__
