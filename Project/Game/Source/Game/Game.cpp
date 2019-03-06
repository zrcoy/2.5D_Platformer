#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "ImGuiManager.h"
#include "Box2D/Box2D.h"
#include "Game/GraphicScene.h"
#include "Physics2D/PhysicsWorld.h"
#include "Game/PhysicsScene.h"
#include "Mesh/Material.h"
#include "GameObjects/Camera.h"
#include "Game/PoolTestScene.h"
#include "SceneFloating/FloatingScene.h"
#include "SlopeScene/SlopeScene.h"
#include "PlatformerScene/PlatformerScene.h"
#include "GameEventTypes.h"
#include "RemoveFromSceneEvent.h"


Game::Game(Framework* pFramework)
    : GameCore(pFramework, new EventManager())
{
    //b2World world(b2Vec2(0, 0));

    m_pImGuiManager = nullptr;

    //m_pMegaTexture = nullptr;
    //m_pDiceTexture = nullptr;
    //m_pGrassTexture = nullptr;
    //m_pWaterTexture = nullptr;
    //m_pMeshBox = nullptr;
    //m_pMeshCube = nullptr;
    //m_pMeshPlane = nullptr;
    //m_pMegamanMaterial = nullptr;
    //m_pGrassMaterial = nullptr;
    //m_pDiceMaterial = nullptr;
    //m_pWaterMaterial = nullptr;
    //m_pCamera = nullptr;

    m_pResourceManager = nullptr;
    m_pGraphicScene = nullptr;
    m_pSecondScene = nullptr;
    m_pSlopeScene = nullptr;
    m_pPoolTestScene = nullptr;
    m_pActiveScene = nullptr;
    m_pFloatingScene = nullptr;
    m_pPlatformerScene = nullptr;


    for (int i = 0; i < 4; i++)
    {
        m_pControllers[i] = nullptr;
    }

    //m_pPlayer = nullptr;
}

Game::~Game()
{
    //delete m_pPlayer;

   // delete m_pCamera;

    for (int i = 0; i < 4; i++)
    {
        delete m_pControllers[i];
    }
    delete m_pResourceManager;
    // delete m_pActiveScene;
    delete m_pGraphicScene;
    delete m_pSecondScene;
    delete m_pPoolTestScene;
    delete m_pFloatingScene;
    delete m_pSlopeScene;
    delete m_pPlatformerScene;
    delete m_pImGuiManager;
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    // Set OpenGL to draw to the entire window.
    glViewport(0, 0, width, height);
}

void Game::LoadContent()
{
#if WIN32
    // Turn on V-Sync.
    wglSwapInterval(1);
#endif

    // Turn on depth buffer testing.
    //glEnable(GL_DEPTH_TEST);
    glPointSize(10);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glDepthFunc(GL_LEQUAL);

    // Turn on alpha blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_pResourceManager = new ResourceManager();

    // Create our shaders.
    ShaderProgram* pShader = new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag");
    ShaderProgram* pShader_Texture = new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag");
    ShaderProgram* p2DShader = new ShaderProgram("Data/Shaders/2DTexture.vert", "Data/Shaders/2DTexture.frag");
    ShaderProgram* pWaterShader = new ShaderProgram("Data/Shaders/Water_Prof.vert", "Data/Shaders/Water_Prof.frag");
    ShaderProgram* pDebugDrawShader = new ShaderProgram("Data/Shaders/DebugDraw.vert", "Data/Shaders/DebugDraw.frag");

    // Load some textures.
    Texture* pMegaTexture = new Texture("Data/Textures/Megaman.png");
    Texture* pDiceTexture = new Texture("Data/Textures/Dice.png");
    Texture* pGrassTexture = new Texture("Data/Textures/Grass.png");
    Texture* pWaterTexture = new Texture("Data/Textures/Water.png");

    // Create our meshes.
    Mesh* pMeshBox = new Mesh();
    pMeshBox->CreateBox(vec2(1, 1), vec2(0, 0));

    Mesh* pMeshCube = new Mesh();
    pMeshCube->CreateCube(vec3(1, 1, 1), vec3(0, 0, 0));

    Mesh* pMeshPlane = new Mesh();
    pMeshPlane->CreatePlane(vec2(30, 15), ivec2(4, 4),vec2(15,(15.0f/2.0f)));

    Mesh* pMeshCubeObj = new Mesh();
    pMeshCubeObj->CreateObj("Data/Textures/cube.obj");


    m_pResourceManager->AddMesh("Box", pMeshBox);

    m_pResourceManager->AddMesh("Cube", pMeshCube);

    m_pResourceManager->AddMesh("Plane", pMeshPlane);

    m_pResourceManager->AddMesh("CubeObj", pMeshCubeObj);

    m_pResourceManager->AddTexture("Megaman", pMegaTexture);

    m_pResourceManager->AddTexture("Dice", pDiceTexture);

    m_pResourceManager->AddTexture("Grass", pGrassTexture);

    m_pResourceManager->AddTexture("Water", pWaterTexture);

    m_pResourceManager->AddShader("Texture", pShader);

    m_pResourceManager->AddShader("Shader_Texture", pShader_Texture);

    m_pResourceManager->AddShader("2DTextureShader", p2DShader);

    m_pResourceManager->AddShader("WaterShader", pWaterShader);

    m_pResourceManager->AddShader("DebugDrawShader", pDebugDrawShader);

    // have to add material after adding shader and texture
    Material* pMegamanMaterial = new Material(pShader, pMegaTexture);
    Material* pGrassMaterial = new Material(pShader, pGrassTexture);
    Material* pGroundMaterial = new Material(pShader, pGrassTexture);
    Material* pNullMaterial = new Material(pShader, nullptr);
    Material* pDiceMaterial = new Material(pShader, pDiceTexture);
    Material* pWaterMaterial = new Material(pWaterShader, pWaterTexture);
    Material* pDebugDrawMaterial = new Material(pDebugDrawShader, pWaterTexture);

    m_pResourceManager->AddMaterial("Megaman", pMegamanMaterial);

    m_pResourceManager->AddMaterial("Grass", pGrassMaterial);

    m_pResourceManager->AddMaterial("Ground", pGroundMaterial);

    m_pResourceManager->AddMaterial("", pNullMaterial);

    m_pResourceManager->AddMaterial("Dice", pDiceMaterial);

    m_pResourceManager->AddMaterial("Water", pWaterMaterial);

    m_pResourceManager->AddMaterial("DebugDraw", pDebugDrawMaterial);

    // Create our controllers.
    for (int i = 0; i < 4; i++)
    {
        m_pControllers[i] = new PlayerController();
    }

    // Default scene with nothing loaded right now
//    m_pActiveScene = new Scene(this, m_pResourceManager);

    // Load game objects from the graphic scene
    m_pGraphicScene = new GraphicScene(this, m_pResourceManager);
    m_pGraphicScene->LoadContent();

    // Load stuff from the second scene
    m_pSecondScene = new PhysicsScene(this, m_pResourceManager);
    m_pSecondScene->LoadContent();

    m_pPoolTestScene = new PoolTestScene(this, m_pResourceManager);
    m_pPoolTestScene->LoadContent();

    // Scene floating
    m_pFloatingScene = new FloatingScene(this, m_pResourceManager);
    m_pFloatingScene->LoadContent();

    m_pSlopeScene = new SlopeScene(this, m_pResourceManager);
    m_pSlopeScene->LoadContent();

    m_pPlatformerScene = new PlatformerScene(this, m_pResourceManager);
    m_pPlatformerScene->LoadContent();

    // Create ImGuiManager object
    m_pImGuiManager = new ImGuiManager();
    m_pImGuiManager->Init();

    // Populate our scene.
    //m_pPlayer = new Player(this, m_pMeshCube, m_pShader, m_pTexture);
    //m_pPlayer->SetPlayerController(m_pControllers[0]);

    CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
    m_pImGuiManager->OnEvent(pEvent);

    m_pControllers[0]->OnEvent(pEvent);

    if (pEvent->GetEventType() == GameEventType_RemoveFromScene)
    {
        RemoveFromSceneEvent* pRemoveFromSceneEvent = (RemoveFromSceneEvent*)pEvent;

        GameObject* pGameObject = pRemoveFromSceneEvent->GetGameObject();


        pGameObject->RemoveFromScene();


    }

    if (m_pActiveScene != nullptr)
        m_pActiveScene->OnEvent(pEvent);

#if WIN32
    // Enable/Disable V-Sync with F1 and F2.
    if (pEvent->GetEventType() == EventType_Input)
    {
        InputEvent* pInput = (InputEvent*)pEvent;

        // Enable V-Sync.
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F1)
            wglSwapInterval(1);

        // Disable V-Sync.
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F2)
            wglSwapInterval(0);

        // num1 for graphic scene, 0x31 is 1
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && (pInput->GetID() == VK_NUMPAD1 || pInput->GetID() == '1'))
        {
            m_pActiveScene = m_pFloatingScene;
        }

        // num2 for ball pit
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && (pInput->GetID() == VK_NUMPAD2 || pInput->GetID() == '2'))
        {
            m_pActiveScene = m_pSecondScene;
        }

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && (pInput->GetID() == VK_NUMPAD3 || pInput->GetID() == '3'))
        {
            m_pActiveScene = m_pSlopeScene;
        }

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && (pInput->GetID() == VK_NUMPAD4 || pInput->GetID() == '4'))
        {
            m_pActiveScene = m_pGraphicScene;
        }

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && (pInput->GetID() == VK_NUMPAD5 || pInput->GetID() == '5'))
        {
            m_pActiveScene = m_pPlatformerScene;
        }

    }
#endif //WIN32
}

void Game::Update(float deltatime)
{
    /*float timeScale = 0.2f;
    deltatime *= timeScale;*/

    if (deltatime > 0.1f)
        deltatime = 0.1f;

    m_pImGuiManager->StartFrame((float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltatime);

    //   m_pPlayer->Update(deltatime);
    if (m_pActiveScene != nullptr)
    {
        //m_pActiveScene->GetWorld()->Update(deltatime);
        m_pActiveScene->Update(deltatime);
    }

    //m_pMeshCube->SetupTool();

}

void Game::Draw()
{
    //debug using imgui


    //ImGui::Begin("Scene Entry, Press '1' go to graphic scene");

    //static float blueness = 0.4f;
    //ImGui::SliderFloat("Blueness", &blueness, 0.0f, 1.0f);

    //static float redness = 0.8f;
    //ImGui::SliderFloat("Redness", &redness, 0.0f, 1.0f);

    //if (ImGui::Button("Max"))
    //{
    //    blueness = 1.0f;
    //    redness = 1.0f;
    //}
    //if (ImGui::Button("Reset"))
    //{
    //    blueness = 0.4f;
    //    redness = 0.8f;
    //}
    //ImGui::End();

    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor(0.4f, 0.0f, 0.4f, 0.0f); // (red, green, blue, alpha) - dark blue.
#if WIN32
    glClearDepth(1); // 1 is maximum depth.
#endif
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_pFramework->GetWindowHeight();

    // Draw our game objects.
    if (m_pActiveScene != nullptr)
    {
        /*  vec3 camPos = vec3(0, 0, 0);
          vec3 camRot = vec3(0, 0, 0);
          vec3 camScale = vec3(1, 1, 1);
          m_pCamera = new Camera(m_pActiveScene, "Camera", camPos, camRot, camScale, m_pResourceManager->GetMesh("Cube"), m_pResourceManager->GetMaterial("Dice"),m_pActiveScene->GetPlayer());*/
        m_pActiveScene->Draw();
    }



    m_pImGuiManager->EndFrame();

    //m_pPlayer->Draw(halfWorldSize, 1 / halfWorldSize);

    CheckForGLErrors();
}
