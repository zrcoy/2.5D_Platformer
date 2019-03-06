#pragma once

class b2ContactListener;
class GameObject;

class Box2DContactListener :public b2ContactListener
{
protected:
    //GameObject * pObjA;
    //GameObject* pObjB;
public:

    Box2DContactListener();
    ~Box2DContactListener();

    virtual void BeginContact(b2Contact* contact) override;
};
