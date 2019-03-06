#pragma once

class b2World;
class Box2DDebugDraw;
class Camera;
class Material;

class PhysicsWorld
{
protected:
    b2World * m_pWorld;
    b2ContactListener* m_pContactListener;
    Box2DDebugDraw* m_pDebugDraw;

    b2Body * m_pWorldBody;
    float m_TotalTime;
public:
    PhysicsWorld();
    ~PhysicsWorld();

    void Update(float delta);
    void Draw(Camera* pCamera,Material* pMaterial);

    void Init(b2Vec2 gravity);
    b2World* Getb2World() { return m_pWorld; }


    b2Body* GetWorldBody() { return m_pWorldBody; }
};

