#include "GamePCH.h"
#include "Game/Scene.h"
#include "Game/PhysicsScene.h"
#include "Game/Game.h"
#include "ResourceManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Ground.h"
#include "Physics2D/PhysicsWorld.h"
#include "Game/MyPool.h"
#include "GameObjects/Camera.h"
#include "Physics2D/RayCastResultCallback.h"


PhysicsScene::PhysicsScene(Game* pGame, ResourceManager* pResources)
    :Scene(pGame, pResources)
{
    m_pCubePool = nullptr;
    m_Wireframe = false;
}

PhysicsScene::~PhysicsScene()
{
    delete m_pCubePool;

}


void PhysicsScene::LoadContent()
{
    //create pool
   /* m_pCubePool = new MyPool<GameObject*>;
    for (int i = 0; i < 100; i++)
    {
        GameObject* pObj = new GameObject(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Dice"), this);
        m_pCubePool->AddObjectToPool(pObj);
    }*/



    m_pWorld = new PhysicsWorld();
    m_pWorld->Init(b2Vec2(0, -10));  

    // create gameobject and push them to the vector
    //m_pPlayer = new Player(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Megaman"), this);
    vec3 playerInitPos = vec3(-5.0f, 20.0f, 0);
    vec3 generalInitRot = vec3(0, 0, 0);
    vec3 generalInitScale = vec3(1, 1, 1);
    m_pPlayer = new Player(this, "Player", playerInitPos, generalInitRot, generalInitScale, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Megaman"));
    
    b2Vec2 pos = b2Vec2(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y);
    m_pPlayer->CreateBody(true);
    //m_pPlayer->CreatBox(2.0f, 2.0f, 10.0f);
    m_pPlayer->CreatBox(generalInitScale.x, generalInitScale.y,10.0f);
    // m_pPlayer->GetBody()->SetTransform(b2Vec2(10.0f, 20.0f), 0);

    m_pPlayer->SetPlayerController(m_pGame->GetController(0));
    m_vGameObjects.push_back(m_pPlayer);
   

    // Bottom ground
    //{
    //    float radian = 0 / 180.0f*PI;
    //    m_pGround = new Ground(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Grass"), this);
    //    m_pGround->SetAngle(radian);
    //    m_pGround->CreateBody(false, b2Vec2(0, 0), radian);

    //    //m_pGround->GetBody()->SetTransform(b2Vec2(0.0f, 0.0f), angle);
    //    m_pGround->CreatBox(40.0f, 1.0f);

    //    m_vGameObjects.push_back(m_pGround);
    //}
    //CreateCustomObject("Grass", false, false, vec2(0, 0), GetRadianFromAngle(0), 40.0f, 1.0f);

    CreateCustomObject("Grass", false, false, vec2(0, 0), GetRadianFromAngle(0), 40.0f, 1.0f,"Ground");

    b2RevoluteJointDef jointDef;
    jointDef.Initialize(m_pGround->GetBody(), m_pWorld->GetWorldBody(), b2Vec2(0, -5));
    
    jointDef.enableMotor=true;
    jointDef.motorSpeed = 100.0f;
    jointDef.maxMotorTorque = 100.0f;
    m_pWorld->Getb2World()->CreateJoint(&jointDef);


    // Right ground
    //{
    //    float radian = 45.0f / 180.0f*PI;
    //    m_pGround = new Ground(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Grass"), this);
    //    m_pGround->SetAngle(radian);
    //    m_pGround->CreateBody(false, b2Vec2(20, 8), radian);

    //    //m_pGround->GetBody()->SetTransform(b2Vec2(0.0f, 0.0f), angle);
    //    m_pGround->CreatBox(20.0f, 1.0f);

    //    m_vGameObjects.push_back(m_pGround);
    //}
    //CreateCustomObject("Grass", false, false, vec2(30, 15), GetRadianFromAngle(45), 40.0f, 1.0f);



    // Left ground
    //{
    //    float radian = 135.0f / 180.0f*PI;
    //    m_pGround = new Ground(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Grass"), this);
    //    m_pGround->SetAngle(radian);
    //    m_pGround->CreateBody(false, b2Vec2(-20, 8), radian);

    //    //m_pGround->GetBody()->SetTransform(b2Vec2(0.0f, 0.0f), angle);
    //    m_pGround->CreatBox(20.0f, 1.0f);

    //    m_vGameObjects.push_back(m_pGround);
    //}
   // CreateCustomObject("Grass", false, false, vec2(-30, 15), GetRadianFromAngle(135), 40.0f, 1.0f);


    // some dice cube objects in the pit
    //for (int i = 0; i = 3; i++)
    /*{
        m_pGround = new Ground(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Dice"), this);
        int randx = rand() % 20 + 1 - 20;
        int randy = rand() % 20 + 10;
        m_pGround->SetPosition(vec2(float(randx), float(randy)));
        b2Vec2 pos = b2Vec2(m_pGround->GetPosition().x, m_pGround->GetPosition().y);
        m_pGround->CreateBody(true, pos, 0);
        m_pGround->CreatBox(1.0f, 1.0f);
        m_vGameObjects.push_back(m_pGround);
    }*/
    int num_Dice=0;
    for(int i=0;i<num_Dice;i++)
    CreateCustomObject("Dice", true, true, vec2(0, 0), 0, 1.0f, 1.0f,"Dice");





    // Create camera
    vec3 camPos = vec3(0, 0, -50);
    vec3 camRot = vec3(0, 0, 0);
    vec3 camScale = vec3(1, 1, 1);
    m_pCamera = new Camera(this, "Camera", camPos, camRot, camScale/*, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Dice"), m_pPlayer*/);
    m_pCamera->SetLookAtPosition(m_pPlayer->GetPosition());
    m_vGameObjects.push_back(m_pCamera);


    
    
  
}

void PhysicsScene::OnEvent(Event* pEvent)
{
    // nothing

}

void PhysicsScene::Update(float deltatime)
{
    Scene::Update(deltatime);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //loop through vector and call update on each object
  /*  for (auto pObject : m_vGameObjects)
    {
        pObject->Update(deltatime);
    }*/

    //ray cast report
    RayCastResultCallback raycastresult;
    b2Vec2 p1 = m_pPlayer->GetBody()->GetPosition();
    b2Vec2 p2 = b2Vec2(p1.x, p1.y-2.0f);
    m_pWorld->Getb2World()->RayCast(&raycastresult, p1, p2);
    if (raycastresult.m_Hit == true)
    {
        //ImGui::Text()
        
        if (((GameObject*)(raycastresult.m_pBody->GetUserData()))->GetName() == "Ground")
        {
            int bp = 1;
        }
    }

}

void PhysicsScene::Draw()
{

    Scene::Draw();
   


   

}

void PhysicsScene::CreateCustomObject(char* material, bool isPosRandom,bool isDynamic,vec2 position,float radian,float boxWidth,float boxHeight,std::string name)
{
    //m_pGround = new Ground(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture(texture), this);
    vec3 generalInitRot = vec3(0, 0, 0);
    vec3 generalInitScale = vec3(1, 1, 1);
    
    if (isPosRandom)
    {
        int randx = rand() % 40 + 1 - 20;
        int randy = rand() % 20 + 10;

       // m_pGround->SetPosition(vec2(float(randx), float(randy)));
        vec3 pos = vec3(vec2(float(randx), float(randy)));
        m_pGround = new Ground(this, name, pos, generalInitRot, generalInitScale, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial(material));
    }
    else
    {
        //m_pGround->SetPosition(position);
        m_pGround = new Ground(this, name, position, generalInitRot, generalInitScale, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial(material));
    }
    b2Vec2 pos = b2Vec2(m_pGround->GetPosition().x, m_pGround->GetPosition().y);
    m_pGround->CreateBody(isDynamic);
    m_pGround->CreatBox(boxWidth, boxHeight);
    m_vGameObjects.push_back(m_pGround);
}