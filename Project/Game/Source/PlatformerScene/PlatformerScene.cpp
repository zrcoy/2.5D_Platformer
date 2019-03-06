#include "GamePCH.h"
#include "Game/Scene.h"
#include "PlatformerScene.h"
#include "GameObjects/GameObject.h"
#include "PlatformerPlayer.h"
#include "Game/ResourceManager.h"
#include "Game/Game.h"
#include "PlatformerGround.h"
#include "Physics2D/PhysicsWorld.h"
#include "GameObjects/Camera.h"
#include "PlatformerScene/PlatformerCoin.h"

PlatformerScene::PlatformerScene(Game* pGame, ResourceManager* pResources)
    :Scene(pGame, pResources)
    ,m_pCoinPool()
    ,m_pPlatformerPlayer(nullptr)
{
   
    
}

PlatformerScene::~PlatformerScene()
{
  

}


void PlatformerScene::LoadContent()
{
    // the physics world
    m_pWorld = new PhysicsWorld();
    m_pWorld->Init(b2Vec2(0, -10));


    // Add player
    float playersize = 1.0f;
    m_pPlatformerPlayer = new PlatformerPlayer(this, "PlatformerPlayer", vec3(0), vec3(0), vec3(playersize), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Megaman"));
    m_pPlatformerPlayer->SetPlayerController(m_pGame->GetController(0));
    m_pPlatformerPlayer->CreateBody(false);
    m_pPlatformerPlayer->CreatBox(playersize,playersize);
    m_pPlatformerPlayer->GetBody()->SetActive(true);
    AddGameObject(m_pPlatformerPlayer);

    // Add one ground for testing
    float groundWidth = 50.0f;
    float groundHeight = 1.0f;
    GameObject* pGround = new PlatformerGround(this, "Ground", vec3(0, -4, 0), vec3(0), vec3(groundWidth, groundHeight, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Grass"));
    pGround->CreateBody(true);
    pGround->CreatBox(groundWidth, groundHeight,10.0f);
    AddGameObject(pGround);

    // Add one wall for testing
    float wallWidth = 1.0f;
    float wallHeight = 5.0f;
    GameObject* pWall = new PlatformerGround(this, "Wall", vec3(2, 2, 0), vec3(0), vec3(wallWidth, wallHeight, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Grass"));
    pWall->CreateBody(true);
    pWall->CreatBox(wallWidth, wallHeight, 10.0f);
    AddGameObject(pWall);


    // Add camera following player

    // Create camera
    vec3 camPos = vec3(0, 0, -50);
    vec3 camRot = vec3(0, 0, 0);
    vec3 camScale = vec3(1, 1, 1);
    m_pCamera = new Camera(this, "Camera", camPos, camRot, camScale/*, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Dice"), m_pPlayer*/);
    m_pCamera->SetObjectToFollow(m_pPlatformerPlayer,vec3(0,2,-20));
    AddGameObject(m_pCamera);


    // Create some coins in a pool
    int coinNum = TOTAL_COIN_NUM;
    for (int i = 0; i < coinNum; i++)
    {
        //vec3
    }

}

void PlatformerScene::OnEvent(Event* pEvent)
{
    
        Scene::OnEvent(pEvent);
        // Send the event to Scene objects in the list.

        
    

}

void PlatformerScene::Update(float deltatime)
{
    Scene::Update(deltatime);

    

}

void PlatformerScene::Draw()
{

    Scene::Draw();





}

