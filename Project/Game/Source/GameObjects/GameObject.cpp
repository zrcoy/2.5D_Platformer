#include "GamePCH.h"

#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "Game/Scene.h"
#include "Physics2D/PhysicsWorld.h"
#include "Mesh/Material.h"
#include "Game/ResourceManager.h"


//GameObject::GameObject(Game* pGame, Mesh* pMesh, ShaderProgram* pShader, Texture* pTexture, Scene* pScene)
//    : m_pGame(pGame)
//    , m_pShader(pShader)
//    , m_pMesh(pMesh)
//    , m_pTexture(pTexture)
//    , m_Position(0, 0, 0)
//    , m_Angle(0)
//    , m_Radius(0.5f)
//    , m_pScene(pScene)
//    , m_Rotation(0, 0, 0)
//    , m_Scale(1, 1, 1)
//{
//}

GameObject::GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : m_pScene(pScene)
    , m_Name (name)
    , m_Position(pos)
    , m_Rotation(rot)
    , m_Scale(scale)
    , m_pMesh(pMesh)
    , m_pMaterial(pMaterial)
    , m_InitialPosition(pos)
    , m_InitialRotation(rot)
{
    if(pMaterial!=nullptr)
    m_pShader = m_pMaterial->GetShader();

    m_pBody = nullptr;
}

GameObject::~GameObject()
{
    /*if (m_pBody != nullptr)
        m_pScene->GetWorld()->Getb2World()->DestroyBody(m_pBody);*/

}

void GameObject::Update(float deltatime)
{
    //sync position to the physics body each frame
    if (m_pBody)
    {
        b2Vec2 pos = m_pBody->GetPosition();
        float angle = m_pBody->GetAngle();

        m_Position.x = pos.x;
        m_Position.y = pos.y;
       // m_Angle = -angle / PI * 180.0f;
        m_Rotation.z = -angle * 180.0f / PI;

    }

}

void GameObject::Draw(Camera* pCamera)
{

    if (m_pMesh != nullptr)
    {
//        MyMatrix worldMat;
//        MyMatrix viewMat;
//        MyMatrix projMat;
//        //m_Rotation = rotate;
//        //m_Scale = vec3(scale, scale, scale);
//        worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);
//        viewMat.SetIdentity();
//        projMat.SetIdentity();
//        m_pMesh->SetupAttributes(m_pShader);
//        vec3 rippleOrigins[3] = { vec3(0, 0, 0) , vec3(40, 0, -40),vec3(40, 0, 25) };
//        float rippleRange[3] = {50.0f,50.0f,15.0f};
//        //rippleOrigins[0] = vec3(0, 0, 0);
//        //rippleOrigins[1] = vec3(-20, 0, 0);
//        //rippleOrigins[2] = vec3(20, 0, 0);
//        /*rippleRange[0] = 20.0f;
//        rippleRange[0] = 30.0f;
//        rippleRange[0] = 40.0f;*/
//
//        vec3 rippleOrigins1 = vec3(40.0f, 0, -40.0f);
//        vec3 rippleOrigins2 = vec3(0, 0, 0);
//        float rippleRange1 = 20.0f;
//        float rippleRange2 = 50.0f;
//        //m_pMesh->SetupUniforms(m_pShader, worldMat, m_pMaterial->GetTexture(),pCamera, rippleOrigins1, rippleOrigins2,rippleRange1, rippleRange2);
//        m_pMesh->SetupUniforms(m_pShader, worldMat, m_pMaterial->GetTexture(), pCamera, rippleOrigins, rippleRange);
//
////        SetUniform1f( m_pShader->GetProgram(), "u_Time", 5 )
//        
//        //m_pMesh->SetupTool();
//        m_pMesh->Draw(m_pShader);

        m_pMesh->SetupAttributes(m_pMaterial);

        // Create world matrix.
        MyMatrix worldMat;
        worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);

        m_pMesh->SetupUniforms(m_pMaterial, &worldMat, pCamera);
        m_pMesh->Draw(m_pMaterial);
    }
}

void GameObject::CreateBody(bool isStatic)
{

    b2BodyDef bodyDef;
    bodyDef.position.Set(m_Position.x, m_Position.y);
    bodyDef.angle = -m_Rotation.z * PI / 180.0f;
    if (isStatic)
        bodyDef.type = b2_staticBody;
    else
        bodyDef.type = b2_dynamicBody;
    bodyDef.active = true;
    bodyDef.userData = this;

    m_pBody = m_pScene->GetWorld()->Getb2World()->CreateBody(&bodyDef);
}

void GameObject::CreatBox(float width, float height, float32 density, bool isSensor, float32 friction, float32 restitution)
{
    b2PolygonShape boxShape;
    boxShape.SetAsBox(width/2.0f, height/2.0f);
    m_Scale = vec3(width, height, m_Scale.z);

    createFixture(&boxShape, density, isSensor, friction, restitution);
}

void GameObject::CreateCircle(float radius, float32 density, bool isSensor , float32 friction, float32 restitution )
{
    b2CircleShape shape;
    shape.m_p = b2Vec2(0, 0);
    shape.m_radius = radius;

    createFixture(&shape, density, isSensor,friction,restitution);
}


void GameObject::createFixture(b2Shape* shape, float32 density, bool isSensor, float32 friction, float32 restitution)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = density;
    fixtureDef.isSensor = isSensor;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.userData = this;
    
    m_pBody->CreateFixture(&fixtureDef);
}

void GameObject::BeginContact(b2Fixture* otherFixture, vec2 collidePos, vec2 collideNormal)                                        
{
    // do some thing while contacting

}

void GameObject::EndContact(b2Fixture* pOtherFixture)
{
    //OutputMessage( "Normal: %s, %0.2f, %0.2f\n", m_Name.c_str(), worldNormal.x, worldNormal.y );
}


void GameObject::SyncPhysicsBodyToGameObject()
{
    m_pBody->SetTransform(b2Vec2(m_Position.x, m_Position.y), m_Rotation.z * PI / 180.0f);
}


bool GameObject::RemoveFromScene()
{
    return m_pScene->RemoveGameObject(this);
}

void GameObject::Reset()
{
    m_Position = m_InitialPosition;
    m_Rotation = m_InitialRotation;

    if (m_pBody)
    {
        m_pBody->SetLinearVelocity(b2Vec2(0, 0));
        m_pBody->SetAngularVelocity(0);
        m_pBody->SetTransform(b2Vec2(m_InitialPosition.x, m_InitialPosition.y), m_InitialRotation.z * PI / 180);
        m_pBody->SetAwake(true);
    }
}