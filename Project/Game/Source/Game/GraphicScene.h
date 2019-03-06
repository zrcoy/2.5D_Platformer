#pragma once

class Scene;
class Game;
class GameObject;
class ResourceManager;

//template <class GameObjects*> class MyPool;

#include "Game/MyPool.h"

class GraphicScene : public Scene
{
protected:
    MyPool<GameObject*>* m_pCubePool;

public:
    GraphicScene(Game* pGame, ResourceManager* pResources);
    virtual ~GraphicScene();

    virtual void LoadContent();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();
};
