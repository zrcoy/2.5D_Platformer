#include "GamePCH.h"

#include "PoolTestScene.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Ground.h"
#include "Physics2D/PhysicsWorld.h"

PoolTestScene::PoolTestScene(Game* pGame, ResourceManager* pResources)
: Scene( pGame, pResources )
{
}

PoolTestScene::~PoolTestScene()
{
}

void PoolTestScene::LoadContent()
{
    m_pWorld = new PhysicsWorld();
    m_pWorld->Init(b2Vec2(0, -10));

    // Create our GameObjects.

    vec3 playerInitPos = vec3(-5.0f, 20.0f, 0);
    vec3 generalInitRot = vec3(0, 0, 0);
    vec3 generalInitScale = vec3(1, 1, 1);
    m_pPlayer = new Player(this, "Player", playerInitPos, generalInitRot, generalInitScale, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Megaman"));
    m_pPlayer->SetPlayerController( m_pGame->GetController( 0 ) );// Assign our controllers.
    b2Vec2 pos = b2Vec2(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y);
    m_pPlayer->CreateBody(true);
    m_pPlayer->CreatBox(2.0f, 2.0f, 10.0f);
    m_vGameObjects.push_back(m_pPlayer);


    // Create camera
    vec3 camPos = vec3(0, 0, -10.0f);
    vec3 camRot = vec3(0, 0, 0);
    vec3 camScale = vec3(1, 1, 1);
    m_pCamera = new Camera(this, "Camera", camPos, camRot, camScale/*, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Dice"), m_pPlayer*/);
    m_pCamera->SetLookAtPosition(m_pPlayer->GetPosition());
    m_vGameObjects.push_back(m_pCamera);


    CreateCustomObject("Grass", false, false, vec2(0, 0), GetRadianFromAngle(0), 40.0f, 1.0f);
}


void PoolTestScene::CreateCustomObject(char* material, bool isPosRandom, bool isDynamic, vec2 position, float radian, float boxWidth, float boxHeight)
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
        m_pGround = new Ground(this, "CustomObject", pos, generalInitRot, generalInitScale, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial(material));
    }
    else
    {
        //m_pGround->SetPosition(position);
        m_pGround = new Ground(this, "CustomObject", position, generalInitRot, generalInitScale, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial(material));
    }
    b2Vec2 pos = b2Vec2(m_pGround->GetPosition().x, m_pGround->GetPosition().y);
    m_pGround->CreateBody(isDynamic);
    m_pGround->CreatBox(boxWidth, boxHeight);
    m_vGameObjects.push_back(m_pGround);
}

void PoolTestScene::Update(float deltaTime)
{
    //m_pCamera->SetPosition(vec3(m_pPlayer->GetPosition().x))
}