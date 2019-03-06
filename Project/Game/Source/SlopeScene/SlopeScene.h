#pragma once


#include "Game/Scene.h"

class SlopeScene : public Scene
{
public:

protected:

public:
    SlopeScene(Game* pGame, ResourceManager* pResources);
    virtual ~SlopeScene();

    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();
};


