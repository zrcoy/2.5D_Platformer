#ifndef __Scene_H__
#define __Scene_H__

class Game;
class GameObject;
class ResourceManager;
class Player;
class Mesh;
class PhysicsWorld;
class Ground;
class Camera;


class Scene
{
protected:
    Game * m_pGame;
    ResourceManager* m_pResources;

    PhysicsWorld* m_pWorld;

    std::vector<GameObject*> m_vGameObjects;

    GameObject* m_pPlane;

    Player* m_pPlayer;

    Mesh* m_pMeshCube;

    bool m_Wireframe;

    Ground* m_pGround;

    Camera* m_pCamera;
public:
    Scene(Game* pGame, ResourceManager* pResources);
    virtual ~Scene();

    virtual void LoadContent();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();

    void AddGameObject(GameObject* pObject);
    bool RemoveGameObject(GameObject* pObject);

    Game* GetGame() { return m_pGame; }
    ResourceManager* GetResourceManager() { return m_pResources; }

    PhysicsWorld* GetWorld() { return m_pWorld; }

    Player* GetPlayer() { return m_pPlayer; }

    void LoadFromSceneFile(const char* filename);

    GameObject* GetGameObjectByName(std::string name);


};

#endif //__Scene_H__
