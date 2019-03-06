#include "GamePCH.h"

#include "FloatingObject.h"
#include "Game/Scene.h"

FloatingObject::FloatingObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
}

FloatingObject::~FloatingObject()
{
}

void FloatingObject::Update(float deltatime)
{
    GameObject::Update( deltatime );

    //TODO_Floating: Make the objects float on the water.
    // idk: I make the objects float on the water by changing the shader, dk if that is ok

    // get water's y position if x is the same as this object's x, then give a bit high offset to this object's y
   /* GameObject* pWater = m_pScene->GetGameObjectByName("Water");

    b2Vec2 waterPos = pWater->GetBody()->GetPosition();
    b2Vec2 rightDir = b2Vec2(1, 0);*/
    //b2Vec2 Dir=this->GetBody()->GetPosition()-

    m_Position.y+= sin(m_Position.x / 5.0 + GetSystemTimeSinceGameStart()) * 0.0125f;
    m_Position.y -= sin(m_Position.z / 40.0 + GetSystemTimeSinceGameStart()) * 0.025f;

}
