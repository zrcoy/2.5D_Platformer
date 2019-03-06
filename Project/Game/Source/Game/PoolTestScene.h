#ifndef __PoolTestScene_H__
#define __PoolTestScene_H__

#include "Game/Scene.h"

class PoolTestScene : public Scene
{
protected:

public:
    PoolTestScene(Game* pGame, ResourceManager* pResources);
    virtual ~PoolTestScene();

    virtual void LoadContent();

    virtual void Update(float deltaTime);

    void CreateCustomObject(char* material, bool isPosRandom, bool isDynamic, vec2 position, float radian, float boxWidth, float boxHeight);

    float GetRadianFromAngle(float angle) { return angle / 180.0f*PI; }
};

#endif //__PoolTestScene_H__
