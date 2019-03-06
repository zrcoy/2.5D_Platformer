#include "GamePCH.h"

#include "FloatingScene.h"
#include "FloatingMineObject.h"
#include "FloatingPlayerObject.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "Physics2D/PhysicsWorld.h"

FloatingScene::FloatingScene(Game* pGame, ResourceManager* pResources)
    : Scene(pGame, pResources)
{
}

FloatingScene::~FloatingScene()
{
}

void FloatingScene::LoadContent()
{


    Scene::LoadContent();

    m_pWorld = new PhysicsWorld();
    m_pWorld->Init(b2Vec2(0, -10));

    // Load shaders specific to this game.  Will assert if name is already in use.
    {
        m_pResources->AddShader("FloatingWater", new ShaderProgram("Data/SceneFloating/Water.vert", "Data/SceneFloating/Water.frag"));
        m_pResources->AddShader("FloatingMeteor", new ShaderProgram("Data/SceneFloating/Water.vert", "Data/SceneFloating/Meteor.frag"));

    }

    // Create meshes specific to this game.  Will assert if name is already in use.
    {
        m_pResources->AddMesh("FloatingSprite", new Mesh())->CreateBox(vec2(1, 1), vec2(0, 0));
        m_pResources->AddMesh("FloatingWater", new Mesh())->CreatePlane(vec2(300, 300), ivec2(300, 300), vec2(150, 150));
    }

    // Load textures specific to this game.  Will assert if name is already in use.
    {
        m_pResources->AddTexture("FloatingWater", new Texture("Data/SceneFloating/Water.png"));
        m_pResources->AddTexture("FloatingMeteor", new Texture("Data/SceneFloating/Meteor.png"));
        // m_pResources->AddTexture("FloatingMegaman", new Texture("Data/Textures/Megaman.png"));

    }

    // Create materials specific to this game.  Will assert if name is already in use.
    {
        m_pResources->AddMaterial("FloatingWater", new Material(m_pResources->GetShader("FloatingWater"), m_pResources->GetTexture("FloatingWater")));
        //m_pResources->AddMaterial("FloatingMeteor", new Material(m_pResources->GetShader("FloatingMeteor"), m_pResources->GetTexture("FloatingMeteor")));
        m_pResources->AddMaterial("FloatingMeteor", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("FloatingMeteor")));

        //m_pResources->AddMaterial("FloatingMegaman", new Material(m_pResources->GetShader("FloatingMeteor"), m_pResources->GetTexture("FloatingMegaman")));

    }

    // Create some game objects.
    {
        // Camera.
       /* Camera* pCamera = new Camera(this, "Camera", vec3(0, 10, -20), vec3(0, 0, 0), vec3(1, 1, 1));
        AddGameObject(pCamera);
        m_pCamera = pCamera;*/

        // Water
        GameObject* pObject = new GameObject(this, "Water", vec3(0), vec3(0), vec3(1), m_pResources->GetMesh("FloatingWater"), m_pResources->GetMaterial("FloatingWater"));
        AddGameObject(pObject);

        // Player
        FloatingPlayerObject* pPlayer = new FloatingPlayerObject(this, "Player", vec3(0, 0, 0), vec3(0, 0, 0), vec3(1), m_pResources->GetMesh("FloatingSprite"), m_pResources->GetMaterial("Megaman"));
        AddGameObject(pPlayer);
        pPlayer->SetController(m_pGame->GetController(0));

        // Mines
        for (int i = 0; i < 20; i++)
        {
            std::string minename = "Mine" + std::to_string(i);
            vec3 pos((float)sin((float)i)*10.0f, 0.0f, 3.0f + i * 3.0f);    // x range from -10 to 10, y is 0, z (i*3)
            GameObject* pObject = new FloatingMineObject(this, minename, pos, vec3(0, 0, 0), vec3(1), m_pResources->GetMesh("FloatingSprite"), m_pResources->GetMaterial("FloatingMeteor"));

            AddGameObject(pObject);
        }

        // TODO_Floating: Create a new camera class that will follow the player with an offset and look at the player.
        // Set the camera to follow the player.
        //((WhateverYouCallYourNewCameraObjectOtherThanThis*)m_pGameObjects["Camera"])->SetObjectToFollow( m_pGameObjects["Player"], vec3( 0, 5, -10 );
        Camera* pCamFollow = new Camera(this, "Camera", vec3(0, 10, -20), vec3(0, 0, 0), vec3(1, 1, 1));
        pCamFollow->SetLookAtPosition(pPlayer->GetPosition());
        pCamFollow->SetObjectToFollow(pPlayer, vec3(0, 5, -10));
        m_pCamera = pCamFollow;
        AddGameObject(pCamFollow);
    }
}

void FloatingScene::Update(float deltatime)
{
    Scene::Update(deltatime);
    
}

void FloatingScene::Draw()
{
    Scene::Draw();
}


