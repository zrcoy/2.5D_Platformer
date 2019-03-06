#include "GamePCH.h"

#include "SlopeScene.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "Physics2D/PhysicsWorld.h"

SlopeScene::SlopeScene(Game* pGame, ResourceManager* pResources)
    : Scene(pGame, pResources)
{
}

SlopeScene::~SlopeScene()
{
}

void SlopeScene::LoadContent()
{

    m_pWorld = new PhysicsWorld();
    m_pWorld->Init(b2Vec2(0, -10));

    Scene::LoadContent();

    Scene::LoadFromSceneFile("Data/Scenes/Slopes.box2dscene");
    m_pCamera = (Camera*)this->GetGameObjectByName("Main Camera");


    int bp = 1;
}

void SlopeScene::Update(float deltatime)
{
    Scene::Update(deltatime);

}

void SlopeScene::Draw()
{
    Scene::Draw();
}


