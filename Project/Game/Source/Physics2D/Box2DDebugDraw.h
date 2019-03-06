#pragma once

class b2Draw;
struct b2Color;
class Camera;
class Material;

class Box2DDebugDraw : public b2Draw
{
protected:
    Camera * m_pCamera;
    Material* m_pMaterial;
public:
    Box2DDebugDraw();
    virtual ~Box2DDebugDraw();

    /// Draw a closed polygon provided in CCW order.
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

    /// Draw a solid closed polygon provided in CCW order.
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

    /// Draw a circle.
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

    /// Draw a solid circle.
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

    /// Draw a line segment.
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

    /// Draw a transform. Choose your own length scale.
    /// @param xf a transform.
    virtual void DrawTransform(const b2Transform& xf);

    /// Draw a point.
    virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)  {};


    void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

    void SetMaterial(Material* pMaterial) { m_pMaterial = pMaterial; }
};

