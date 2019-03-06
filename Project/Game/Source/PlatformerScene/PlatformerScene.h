#pragma once

class Scene;
class Game;
class GameObject;
class ResourceManager;
class PlatformerPlayer;

//template <class GameObjects*> class MyPool;

#include "Game/MyPool.h"

class PlatformerScene : public Scene
{
    const int TOTAL_COIN_NUM=5;
protected:
    
    MyPool<GameObject*>* m_pCoinPool;
    PlatformerPlayer* m_pPlatformerPlayer;

public:
    PlatformerScene(Game* pGame, ResourceManager* pResources);
    virtual ~PlatformerScene();

    virtual void LoadContent();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();

    

    float GetRadianFromAngle(float angle) { return angle / 180.0f*PI; }
};
