#ifndef __Game_H__
#define __Game_H__

class Texture;
class Mesh;
class GameObject;
class Player;
class PlayerController;
class ResourceManager;
class Scene;
class GraphicScene;
class ImGuiManager;
class PhysicsScene;
class Material;
class Camera;
class PoolTestScene;
class SlopeScene;

class Game : public GameCore
{
protected:
    ImGuiManager * m_pImGuiManager;

    

    //Texture* m_pMegaTexture;
    //Texture* m_pDiceTexture;
    //Texture* m_pGrassTexture;
    //Texture* m_pWaterTexture;

    //Mesh* m_pMeshBox;
    //Mesh* m_pMeshCube;
    //Mesh* m_pMeshPlane;

    PlayerController* m_pControllers[4];

    Player* m_pPlayer;

    ResourceManager* m_pResourceManager;

    
    Scene* m_pGraphicScene;
    Scene* m_pSecondScene;
    Scene* m_pActiveScene;
    Scene* m_pPoolTestScene;
    Scene* m_pFloatingScene;
    Scene* m_pSlopeScene;
    Scene* m_pPlatformerScene;

    //Material* m_pMegamanMaterial;
    //Material* m_pGrassMaterial;
    //Material* m_pDiceMaterial;
    //Material* m_pWaterMaterial;

    //Camera* m_pCamera;

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height) override;
    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltatime) override;
    virtual void Draw() override;

    PlayerController* GetController(int index) { return m_pControllers[index]; }
    //Camera* GetCamera() { return m_pCamera; }
};

#endif //__Game_H__
