#include "GamePCH.h"

#include "PhysicsWorld.h"
#include "Box2DContactListener.h"
#include "Physics2D/Box2DDebugDraw.h"
#include "GameObjects/Camera.h"
#include "Mesh/Material.h"

PhysicsWorld::PhysicsWorld()
{
    m_pWorld = nullptr;
    m_pDebugDraw = nullptr;
    m_TotalTime = 0;
}

PhysicsWorld::~PhysicsWorld()
{
    delete m_pContactListener;
    delete m_pWorld;
    delete m_pDebugDraw;
}

void PhysicsWorld::Update(float delta)
{
     m_TotalTime = 0;
     m_TotalTime += delta;

    float timeStep = 1 / 60.0f;
    int velocityIterations = 3;
    int positionIteration = 8;
    
    while (m_TotalTime >= timeStep)
    {

        m_pWorld->Step(timeStep, velocityIterations, positionIteration);
        m_TotalTime -= timeStep;
    }

    m_pWorld->ClearForces();
}

void PhysicsWorld::Draw(Camera* pCamera, Material* pMaterial)
{
    m_pDebugDraw->SetCamera(pCamera);
    m_pDebugDraw->SetMaterial(pMaterial);

    uint32 flags = b2Draw::e_shapeBit;
    m_pDebugDraw->SetFlags(flags);

    m_pWorld->DrawDebugData();
}

void PhysicsWorld::Init(b2Vec2 gravity)
{
    m_pWorld = new b2World(gravity);

    m_pContactListener = new Box2DContactListener();
    m_pWorld->SetContactListener(m_pContactListener);

    m_pDebugDraw = new Box2DDebugDraw();
    m_pWorld->SetDebugDraw(m_pDebugDraw);

    b2BodyDef bodyDef;
    m_pWorldBody = m_pWorld->CreateBody(&bodyDef);
}