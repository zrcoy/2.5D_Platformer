#include "GamePCH.h"

#include "FloatingMineObject.h"
#include "FloatingPlayerObject.h"
#include "Game/Scene.h"

FloatingPlayerObject::FloatingPlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: FloatingObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_pController = nullptr;
}

FloatingPlayerObject::~FloatingPlayerObject()
{
}

void FloatingPlayerObject::SetController(PlayerController* pController)
{
    m_pController = pController;
}

void FloatingPlayerObject::Update(float deltatime)
{
    FloatingObject::Update( deltatime );

    int numattached = 0;

    // Check if we're colliding with any mines.
    for( int i=0; i<20; i++ )
    {
        std::string minename = "Mine" + std::to_string( i );
        FloatingMineObject* pMine = dynamic_cast<FloatingMineObject*>( m_pScene->GetGameObjectByName( minename.c_str() ) );
        assert( pMine != 0 );

        if( pMine != 0 )
        {
            // Check if we're touching the mine.
            bool touching = false;

            //TODO_Floating: Check if we're touching mine.  Assume the player and the mine each have a radius of 1.
            float rangeSq = 2*2;
            vec3 pos = this->GetPosition();
            vec3 minePos = pMine->GetPosition();
            // distance square between player and the mine
            MyVector3 dis = MyVector3(pos.x - minePos.x, 0, pos.z - minePos.z);
            float dist=dis.LengthSq();
            touching = (dist <= rangeSq) ? touching = true : touching = false;
            


            if( touching )
            {
                pMine->m_AttachedToPlayer = true;
            }

            // Count the number of mines attached to us.
            if (pMine->m_AttachedToPlayer) 
            {
                numattached++;
                // make sure mine's position is as the same flat surface as the player's
                pMine->SetPosition(vec3(pMine->GetPosition().x, m_Position.y, pMine->GetPosition().z));
            }
                //numattached += 2;
        }
    }

    // Make all attached mines circle around us.
    int count = 0;
    for( int i=0; i<20; i++ )
    {
        std::string minename = "Mine" + std::to_string( i );
        FloatingMineObject* pMine = dynamic_cast<FloatingMineObject*>( m_pScene->GetGameObjectByName( minename.c_str() ) );
        assert( pMine != 0 );

        if( pMine != 0 && pMine->m_AttachedToPlayer )
        {
            //TODO_Floating: Position the mine so it's circling us.
            //circleing range assumed 3
            float r = 3;
            vec3 pos = this->GetPosition();
            vec3 minePos = pMine->GetPosition();
            //float deltaZ = minePos.z - pos.z;
            //float deltaX = minePos.x - pos.x;
            //float radian = atan2(deltaZ, deltaX); // atan2 return radian
            //
            ////angle = angle / 180.0f*PI;
            //float x = r * cos(radian);
            //float z = r * sin(radian);
            //vec3 newPos = vec3(x, this->GetPosition().y, z);
            //pMine->SetPosition(newPos);

            //radian += 0.05*deltatime;    // 1s increase 0.5 radian
            //if (radian >= (2 * PI))
            //{
            //    radian = 0;
            //}
            float angle = pMine->GetAngleRotating();

            angle += 60.0f*deltatime; // 1s increase how many degrees

            pMine->SetAngleRotating(angle);

            float offsetX = r * cos(angle / 180.0f*PI);
            float offsetZ = r * sin(angle / 180.0f*PI);
            pMine->SetPosition(vec3(pos.x + offsetX, minePos.y, pos.z + offsetZ));

            count++;
        }
    }

    // Move faster depending how many mines we have.
    float speed = 1.0f + numattached;

    vec3 dir(0,0,0);

    if( m_pController->IsHeld_Up() )
        dir.z += 1;
    if( m_pController->IsHeld_Down() )
        dir.z -= 1;
    if( m_pController->IsHeld_Left() )
        dir.x -= 1;
    if( m_pController->IsHeld_Right() )
        dir.x += 1;

    //TODO_Floating: Make sure direction vector isn't longer than 1.

    if (dir.Length() > 1)
    {
        if (dir.x > 1)dir.x = 1;
        if (dir.x < -1)dir.x = -1;
        if (dir.z > 1)dir.z = 1;
        if (dir.z < -1)dir.z = -1;
        OutputMessage("Player moving too fast (%f, %f, %f)\n", dir.x, dir.y, dir.z);
    }
        

    m_Position += dir * speed * deltatime;
}


