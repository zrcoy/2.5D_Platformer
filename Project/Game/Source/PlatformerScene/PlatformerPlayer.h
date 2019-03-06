#pragma once

class GameObject;
class Mesh;
class PlayerController;

class PlatformerPlayer : public GameObject
{
    const float DOUBLEJUMPDELAY = 0.5f;
    const int Total_GROUND_JUMP_TIMES = 2;
    const int Total_WALL_JUMP_TIMES = 1;
protected:
    PlayerController * m_pPlayerController;

    bool m_FacingRight = true;
    int m_RemainingJumpTimes = 0;
    float m_MultipleJumpTimer = 0;

    bool m_CanJump;


public:
    PlatformerPlayer(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~PlatformerPlayer();

    virtual void Update(float deltatime) override;
    virtual void Draw(Camera* pCamera);

    void SetPlayerController(PlayerController* controller) { m_pPlayerController = controller; }


    virtual void OnEvent(Event* pEvent) override;

    virtual void BeginContact(b2Fixture* pOtherFixture, vec2 worldPosition, vec2 worldNormal);
    virtual void EndContact(b2Fixture* pOtherFixture);
};

