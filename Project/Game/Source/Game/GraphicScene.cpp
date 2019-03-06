#include "GamePCH.h"
#include "Game/Scene.h"
#include "Game/GraphicScene.h"
#include "Game/Game.h"
#include "ResourceManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Ground.h"
#include "Physics2D/PhysicsWorld.h"
#include "Game/MyPool.h"
#include "GameObjects/Camera.h"


GraphicScene::GraphicScene(Game* pGame, ResourceManager* pResources)
    :Scene(pGame, pResources)
{
    m_pCubePool = nullptr;
    m_Wireframe = true;
}

GraphicScene::~GraphicScene()
{
    delete m_pCubePool;
  
}


void GraphicScene::LoadContent()
{
  

    //create pool
    /*m_pCubePool = new MyPool<GameObject*>;
    for (int i = 0; i < 100; i++)
    {
        GameObject* pObj = new GameObject(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Dice"), this);
        m_pCubePool->AddObjectToPool(pObj);
    }*/



    m_pWorld = new PhysicsWorld();
    m_pWorld->Init(b2Vec2(0, -5));


    

    // create gameobject and push them to the vector
 /*   m_pPlayer = new Player(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Dice"), this);
    m_pPlayer->CreateBody(true);
    m_pPlayer->CreatBox(1.0f, 1.0f);
    m_pPlayer->SetPlayerController(m_pGame->GetController(0));
    m_vGameObjects.push_back(m_pPlayer);*/

    // Create plane
    //m_pPlane = new GameObject(m_pGame, m_pResources->GetMesh("Plane"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Dice"), this);
    
    vec3 playerInitPos = vec3(0.0f, 0.0f, 0);
    vec3 generalInitRot = vec3(0, 0, 0);
    vec3 generalInitScale = vec3(1, 1, 1);

    m_pPlane = new GameObject(this, "Plane", playerInitPos, generalInitRot, generalInitScale, m_pResources->GetMesh("Plane"), m_pResources->GetMaterial("Water"));

    b2Vec2 pos = b2Vec2(m_pPlane->GetPosition().x, m_pPlane->GetPosition().y);
    m_pPlane->CreateBody(false);
    m_pPlane->SetPosition(vec3(0.0f, 0.0f,0.0f));
    m_vGameObjects.push_back(m_pPlane);

    // Create ground
  /*  m_pGround = new Ground(m_pGame, m_pResources->GetMesh("Cube"), m_pResources->GetShader("TextureShader"), m_pResources->GetTexture("Megaman"), this);
    m_pGround->CreateBody(false);
    m_pGround->CreatBox(50.0f, 4.0f);
    m_vGameObjects.push_back(m_pGround);*/
  

    // Create camera
    vec3 camPos = vec3(0, 50, -100.0f);
    vec3 camRot = vec3(0, 0, 0);
    vec3 camScale = vec3(1, 1, 1);
    m_pCamera = new Camera(this, "Camera", camPos, camRot, camScale/*, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Dice"), m_pPlane*/);
    m_pCamera->SetLookAtPosition(m_pPlane->GetPosition());
    AddGameObject(m_pCamera);
}

void GraphicScene::OnEvent(Event* pEvent)
{
    // nothing
    // Enable/Disable V-Sync with F1 and F2.
    if (pEvent->GetEventType() == EventType_Input)
    {
        InputEvent* pInput = (InputEvent*)pEvent;

        // Spawn a object
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 'N')
        {
            
            
            GameObject* pObj = m_pCubePool->GetObjectFromPool();
            if (pObj)
            {
                pObj->SetPosition(vec2(float(rand() % 10), float(rand() % 10)));
                m_vGameObjects.push_back(pObj);
            }
        }

        // Despawn a object
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 'K')
        {
            if (m_vGameObjects.size() > 1)
            {
                GameObject* pObj = m_vGameObjects.back();
                m_vGameObjects.pop_back(); // confusion
                m_pCubePool->AddObjectToPool(pObj);
            }
           
        }
    }
}

void GraphicScene::Update(float deltatime)
{
    //loop through vector and call update on each object
    //for (auto pObject : m_vGameObjects)
    //{
    //    pObject->Update(deltatime);
    //}
    Scene::Update(deltatime);
   
}

void GraphicScene::Draw()
{
    ImGui::Begin("Graphic Scene");
    ImGui::Checkbox("Wireframe", &m_Wireframe);
    if (m_Wireframe)
    {
        glPolygonMode(GL_FRONT, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT, GL_FILL);
    }
    ImGui::End();
    Scene::Draw();


    //vec2 halfWorldSize = vec2(5.0f, 5.0f);
    //loop through vector and call draw on each object

   /* for (auto pObject : m_vGameObjects)
    {
        pObject->Draw(m_pCamera);
    }*/
}