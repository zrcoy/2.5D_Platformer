#include "GamePCH.h"

#include "Box2DDebugDraw.h"

#include "Mesh/Mesh.h"

#include "Mesh/Material.h"

#include "GameObjects/Camera.h"

Box2DDebugDraw::Box2DDebugDraw()
{

}

Box2DDebugDraw::~Box2DDebugDraw()
{

}

void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    int a = 1;

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLint loc = glGetAttribLocation(m_pMaterial->GetShader()->GetProgram(), "a_Position");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, vertices);
        glEnableVertexAttribArray(loc);
    }
    
    mat4 world;
    world.SetIdentity();

    Mesh::SetupUniforms(m_pMaterial,&world,m_pCamera);


    glDisable(GL_CULL_FACE);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    glEnable(GL_CULL_FACE);
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLint loc = glGetAttribLocation(m_pMaterial->GetShader()->GetProgram(), "a_Position");
    
    b2Vec2 vertices[20];
    int vertexCount = 20;
    float angle = 360 / 20.0f;
    for (int i = 0; i < vertexCount; i++)
    {
        vertices[i].x = radius * cos(angle*i) + center.x;
        vertices[i].y = radius * sin(angle*i) + center.y;

    }


    if (loc != -1)
    {
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, vertices);
        glEnableVertexAttribArray(loc);
    }

    mat4 world;
    world.SetIdentity();

    Mesh::SetupUniforms(m_pMaterial, &world, m_pCamera);


    glDisable(GL_CULL_FACE);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    glEnable(GL_CULL_FACE);
}

/// Draw a solid circle.
void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{

}



/// Draw a line segment.
void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}



/// Draw a transform. Choose your own length scale.
/// @param xf a transform.
void Box2DDebugDraw::DrawTransform(const b2Transform& xf)
{

}
