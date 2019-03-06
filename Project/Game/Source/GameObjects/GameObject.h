#ifndef __GameObject_H__
#define __GameObject_H__

class Game;
class Mesh;
class Scene;
class Texture;
class Material;
class Camera;

class GameObject
{
protected:
    Game* m_pGame;

    Mesh* m_pMesh;
    ShaderProgram* m_pShader;
    Texture* m_pTexture;

    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_Scale;

    float m_Angle;

    float m_Radius;

    MyMatrix m_Mat;

    Scene* m_pScene;

    Material* m_pMaterial;

    b2Body* m_pBody;

    std::string m_Name;

    vec3 m_InitialPosition;
    vec3 m_InitialRotation;
public:
    //GameObject(Game* pGame, Mesh* pMesh, ShaderProgram* pShader, Texture* pTexture, Scene* pScene);

    // Update GameObject class
    GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);

    

    virtual ~GameObject();

    virtual void OnEvent(Event* pEvent) {}
    virtual void Update(float deltatime);
    virtual void Draw(Camera* pCamera);

    // Getters.
    vec3 GetPosition() { return m_Position; }
    float GetAngle() { return m_Angle; }
    float GetRadius() { return m_Radius; }
    Scene* GetScene(){return m_pScene;}

    // Setters.
    void SetShader(ShaderProgram* pShader) { m_pShader = pShader; }
    void SetMesh(Mesh* pMesh) { m_pMesh = pMesh; }
    void SetPosition(vec3 pos) { m_Position = pos; }
    void SetAngle(float angle) { m_Angle = angle; }
    void SetRadius(float radius) { m_Radius = radius; }
    void SetScene(Scene* pScene) { m_pScene = pScene; }


    void CreateBody(bool isStatic);

    void CreateCircle(float radius, float32 density = 1.0f, bool isSensor = false, float32 friction = 0.2f, float32 restitution = 0.0f);

    void CreatBox(float width, float height, float32 density=1.0f, bool isSensor=false, float32 friction=0.2f, float32 restitution=0.0f);
    void createFixture(b2Shape* shape, float32 density, bool isSensor, float32 friction, float32 restitution);
    b2Body* GetBody() { return m_pBody; }

    virtual void BeginContact(b2Fixture* otherFixture, vec2 collidePos, vec2 collideNormal);
    virtual void EndContact(b2Fixture* pOtherFixture);


    std::string GetName() { return m_Name; }

    void SyncPhysicsBodyToGameObject();

    virtual void Reset();
    virtual bool RemoveFromScene();
};

#endif //__GameObject_H__
