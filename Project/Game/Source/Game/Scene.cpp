#include "GamePCH.h"

#include "Game/Game.h"
#include "ResourceManager.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "Physics2D/PhysicsWorld.h"
#include "GameObjects/Camera.h"
#include "Physics2D/Box2DDebugDraw.h"
#include "../Framework/Libraries/cJSON/cJSON.h"
#include "Game/cJSONHelpers.h"

Scene::Scene(Game* pGame, ResourceManager* pResources)
{
    m_pGame = pGame;
    m_pResources = pResources;
    m_pWorld = nullptr;
    m_Wireframe = false;
    m_pPlayer = nullptr;
    m_pPlane = nullptr;
    m_pCamera = nullptr;
}

Scene::~Scene()
{
    for (auto pObject : m_vGameObjects)
    {
        delete pObject;
    }
    delete m_pWorld;

}

void Scene::LoadFromSceneFile(const char* filename)
{

    char* contents = LoadCompleteFile(filename, nullptr);

    cJSON* jRoot = cJSON_Parse(contents);

    cJSON* jGameObjectArray = cJSON_GetObjectItem(jRoot, "GameObjects");

    int numGameObjects = cJSON_GetArraySize(jGameObjectArray);

    //char* name = new char[20];

    for (int i = 0; i < numGameObjects; i++)
    {
        cJSON* jGameObject = cJSON_GetArrayItem(jGameObjectArray, i);

        vec3 pos(0, 0, 0);
        cJSONExt_GetFloatArray(jGameObject, "Pos", &pos.x, 3);

        char* name = new char[20];
        cJSONExt_GetString(jGameObject, "Name", name, 20);

        vec3 rot(0, 0, 0);
        cJSONExt_GetFloatArray(jGameObject, "Rot", &rot.x, 3);

        vec3 scale(0, 0, 0);
        cJSONExt_GetFloatArray(jGameObject, "Scale", &scale.x, 3);

        // second loop for material?
        // get component array from gameObject array
        cJSON* jComponentArray = cJSON_GetObjectItem(jGameObject, "Components");

        int numComponents = cJSON_GetArraySize(jComponentArray);

        char* material = new char[20];

        //inside the components
        // check if it's components
        if (numComponents > 0)
        {
            // some variables for create physics body
            int density = 0;
            int restitution = 0;
            bool isSensor = 0;
            bool isStatic = 0;
            float friction = 0;
            char* primitive = new char[10];
            for (int i = 0; i < numComponents; i++)
            {
                // each component content
                cJSON* jComponent = cJSON_GetArrayItem(jComponentArray, i);

                /*char* texture = new char[50];
                cJSONExt_GetString(jComponent, "Texture", texture, 50);

                char* shader = new char[20];
                cJSONExt_GetString(jComponent, "Shader", shader, 20);*/

                cJSONExt_GetString(jComponent, "Material", material, 20);



                /*static int density = 0;
                static int restitution = 0;
                static bool isSensor=0;
                static bool isStatic = 0;
                static float friction = 0;*/

                //if there's megaman and ground material in this component element
                if (strcmp(material, "Megaman") == 0 || strcmp(material, "Ground") == 0)
                {
                    //material = "";
                    //only add game object when "Megaman" or "Ground" appears
                    //if this is a player ball object
                    if (strcmp(name, "Ball") == 0)
                    {
                        Player* pPlayer = new Player(this, name, pos, rot, scale, m_pResources->GetMesh("Box"), m_pResources->GetMaterial(material));
                        AddGameObject(pPlayer);
                        pPlayer->SetPlayerController(m_pGame->GetController(0));
                        cJSONExt_GetBool(jComponent, "Static", &isStatic);
                        pPlayer->CreateBody(isStatic);
                        pPlayer->CreateCircle(scale.x, density, isSensor, friction, restitution);
                        int bp = 1;
                    }
                    // Other game object other than cameras and player in this case
                    else
                    {
                        GameObject* pObj = new GameObject(this, name, pos, rot, scale, m_pResources->GetMesh("Box"), m_pResources->GetMaterial(material));
                        AddGameObject(pObj);
                        cJSONExt_GetBool(jComponent, "Static", &isStatic);
                        pObj->CreateBody(isStatic);
                        if (strcmp(primitive, "Box") == 0)
                        {
                            pObj->CreatBox(scale.x, scale.y, density, isSensor, friction, restitution);
                        }
                        // if this is circle fixture
                        else if (strcmp(primitive, "Circle") == 0)
                        {
                            pObj->CreateCircle(scale.x, density, isSensor, friction, restitution);

                        }
                    }
                }

                // in this case there're physics properties in this component
                else
                {

                    cJSONExt_GetInt(jComponent, "Density", &density);
                    int bp = 1;


                    cJSONExt_GetBool(jComponent, "IsSensor", &isSensor);
                    cJSONExt_GetBool(jComponent, "Static", &isStatic);

                    cJSONExt_GetString(jComponent, "PrimitiveType", primitive, 10);
                    bp = 1;


                    cJSONExt_GetFloat(jComponent, "Friction", &friction);


                    cJSONExt_GetInt(jComponent, "Restitution", &restitution);
                }


            }
            delete[] primitive;
        }
        // if there's no components in this object, which in this case is the main camera and hud camera
        else if (numComponents == 0)
        {
            AddGameObject(new Camera(this, name, pos, rot, scale));
        }


        delete[] material;
        delete[] name;



    }

    cJSON_Delete(jRoot);


    delete[] contents;
}

void Scene::LoadContent()
{

}

void Scene::OnEvent(Event* pEvent)
{
    // nothing
}

void Scene::Update(float deltatime)
{

    if (m_pWorld != nullptr)
    {

        m_pWorld->Update(deltatime);
    }

    for (auto pObject : m_vGameObjects)
    {
        pObject->Update(deltatime);
    }

}

void Scene::Draw()
{
    for (auto pObject : m_vGameObjects)
    {
        pObject->Draw(m_pCamera);
    }


    //Reset the draw mode at the end of the scene's draw method:
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (m_pWorld)
        m_pWorld->Draw(m_pCamera, m_pResources->GetMaterial("DebugDraw"));

}

GameObject* Scene::GetGameObjectByName(std::string name)
{
    for (auto obj : m_vGameObjects)
    {
        if (obj->GetName() == name)
        {
            return obj;
        }
    }
    return nullptr;
}

void Scene::AddGameObject(GameObject* pObject)
{
    m_vGameObjects.push_back(pObject);
}

bool Scene::RemoveGameObject(GameObject* pObject)
{
    auto iteratorForObject = std::find(m_vGameObjects.begin(), m_vGameObjects.end(), pObject);

    if (iteratorForObject != m_vGameObjects.end())
    {
        m_vGameObjects.erase(iteratorForObject);
        return true;
    }

    return false;
}
