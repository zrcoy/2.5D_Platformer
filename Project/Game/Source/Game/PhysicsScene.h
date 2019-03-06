#pragma once

class Scene;
class Game;
class GameObject;
class ResourceManager;

//template <class GameObjects*> class MyPool;

#include "Game/MyPool.h"

class PhysicsScene : public Scene
{
protected:
    MyPool<GameObject*>* m_pCubePool;

public:
    PhysicsScene(Game* pGame, ResourceManager* pResources);
    virtual ~PhysicsScene();

    virtual void LoadContent();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();

    void CreateCustomObject(char* material, bool isPosRandom, bool isDynamic, vec2 position, float radian, float boxWidth, float boxHeight,std::string name);

    float GetRadianFromAngle(float angle) { return angle / 180.0f*PI; }
};
