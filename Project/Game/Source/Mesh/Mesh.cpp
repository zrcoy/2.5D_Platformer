#include "GamePCH.h"

#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"

#include "Material.h"

Mesh::Mesh()
{
    m_VBO = 0;
    m_IBO = 0;

    //GLuint * pVBO = &m_VBO;
    //pVBO[2] = 7;
    //m_Values[4] = 1;


    m_NumVerts = 0;
    m_NumIndices = 0;

    m_PrimitiveType = -1;

    //m_Tool = GL_TRIANGLES;
}

Mesh::~Mesh()
{
    glDeleteBuffers( 1, &m_VBO );
    glDeleteBuffers( 1, &m_IBO );
}

void Mesh::Init(VertexFormat* verts, int numVerts, unsigned int* indices, int numIndices, GLenum primitiveType, GLenum usage)
{
    m_NumVerts = numVerts;
    m_NumIndices = numIndices;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*numVerts, verts, usage );

    // Generate and fill buffer with our indices.
    if( m_IBO == 0 )
        glGenBuffers( 1, &m_IBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numIndices, indices, usage );

    CheckForGLErrors();
}

void Mesh::Init(const void* verts, int numVerts, GLenum primitiveType, GLenum usage)
{
    m_NumVerts = numVerts;
    m_NumIndices = 0;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat) * numVerts, verts, usage );

    CheckForGLErrors();
}

void SetUniform1f(GLuint shader, const char* uniformName, float value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform1f( loc, value );
    }
}

void SetUniform2f(GLuint shader, const char* uniformName, vec2 value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform2f( loc, value.x, value.y );
    }
}

void SetUniform3f(GLuint shader, const char* uniformName, vec3 value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform3f( loc, value.x, value.y, value.z );
    }
}


void SetUniformWorldMatrix(GLuint shader, const char* uniformName, MyMatrix mat)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        /*float matrix[16]
        {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
        };*/


        glUniformMatrix4fv(loc, 1, false, &mat.m11);
        /*glUniform3f(loc, value.x, value.y, value.z);
        glUniform3fv(loc, 1, &value.x);*/  //above two are the same
    }
}

void SetUniformViewMatrix(GLuint shader, const char* uniformName, MyMatrix view)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    
    //view.SetIdentity();
    //view.Rotate(90, 0, 0, 1);
    //view.Translate(5, 5, 0);
    //view.Inverse();
    
    glUniformMatrix4fv(loc, 1, false, &view.m11);
}

void SetUniformProjMatrix(GLuint shader, const char* uniformName, MyMatrix proj)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    
    glUniformMatrix4fv(loc, 1, false, &proj.m11);
}

void SetUniform1i(GLuint shader, const char* uniformName, int value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform1i(loc, value);
    }
}



void Mesh::SetupAttributes(Material* pMaterial)
{
    assert(m_VBO != 0);
    assert(pMaterial != nullptr);
    assert(pMaterial->GetShader() != nullptr);
    assert(pMaterial->GetShader()->GetProgram() != 0);
    CheckForGLErrors();

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Bind buffer and set up attributes.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    GLint loc = glGetAttribLocation( shader, "a_Position" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Pos) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_Color" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Color) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_UV" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_UV) );
        glEnableVertexAttribArray( loc );
    }
    
}

void Mesh::SetupUniforms(Material* pMaterial, MyMatrix* worldMat, Camera* pCamera, int facingright/*, vec3* RippleOrigin, float* RippleRange*/)
{
    assert(pMaterial != nullptr);
    assert(pMaterial->GetShader() != nullptr);
    assert(pMaterial->GetShader()->GetProgram() != 0);
    CheckForGLErrors();

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Set up shader.
    glUseProgram( shader );

    // Set up uniforms.
    /*SetUniform2f( shader, "u_ObjectScale", objectScale );
    SetUniform1f( shader, "u_ObjectAngleRadians", objectAngle / 180.0f * PI );
    SetUniform2f( shader, "u_ObjectPosition", objectPos );*/
    //SetUniform2f( shader, "u_CameraTranslation", cameraPos * -1 );
    //SetUniform2f( shader, "u_ProjectionScale", projectionScale );
    SetUniformWorldMatrix(shader, "u_WorldMatrix", *worldMat);
    SetUniformViewMatrix(shader, "u_ViewMatrix", pCamera->GetViewMat());
    SetUniformProjMatrix(shader, "u_ProjectionMatrix", pCamera->GetProjMat());


    SetUniform1f(shader, "u_Time", GetSystemTimeSinceGameStart());

    SetUniform1i(shader, "u_FacingRight", facingright);

    /*if (RippleOrigin != nullptr && RippleRange!=nullptr)
    {

        SetUniform3f(shader, "u_Origin[0]", RippleOrigin[0]);
        SetUniform3f(shader, "u_Origin[1]", RippleOrigin[1]);
        SetUniform3f(shader, "u_Origin[2]", RippleOrigin[2]);

        SetUniform1f(shader, "u_RangeOfRipple[0]", RippleRange[0]);
        SetUniform1f(shader, "u_RangeOfRipple[1]", RippleRange[1]);
        SetUniform1f(shader, "u_RangeOfRipple[2]", RippleRange[2]);
    }*/

    
   

    //{
    //    GLint loc = glGetUniformLocation(shader, "u_ViewMatrix");
    //    mat4 view;
    //    //view.SetIdentity();
    //    //view.Rotate(90, 0, 0, 1);
    //    //view.Translate(5, 5, 0);
    //    //view.Inverse();
    //    view.CreateLookAtView(vec3(5, 5, -5), vec3(0, 1, 0), vec3(5, 5, 0));
    //    glUniformMatrix4fv(loc, 1, false, &view.m11);
    //}

   /* {
        GLint loc = glGetUniformLocation(shader, "u_ProjectionMatrix");
        mat4 proj;
        proj.CreateOrtho(-5, 5, -5, 5, 0, 5);
        proj.CreatePerspectiveVFoV(45, 600.0f / 600.0f, 0.01f, 100.0f);
        glUniformMatrix4fv(loc, 1, false, &proj.m11);
    }*/

    //SetUniformMat(shader, "u_ViewMatrix", viewMat);
    //SetUniformMat(shader, "u_WorldMatrix", worldMat);

   

    // Setup our texture.
    Texture* pTexture = pMaterial->GetTexture();
    if( pTexture != nullptr )
    {
        int textureUnitNumber = 0;
        glActiveTexture( GL_TEXTURE0 + textureUnitNumber);
        glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );
        SetUniform1i(shader, "u_TextureSampler", textureUnitNumber);
    }

    CheckForGLErrors();
}

//void Mesh::SetupUniforms(ShaderProgram * pShader, MyMatrix worldMat, Texture * pTexture, Camera * pCamera, vec3 RippleOrigin1, vec3 RippleOrigin2, float RippleRange1, float RippleRange2)
//{
//    assert(pShader != nullptr);
//    assert(pShader->GetProgram() != 0);
//    CheckForGLErrors();
//
//    GLuint shader = pShader->GetProgram();
//
//    // Set up shader.
//    glUseProgram(shader);
//
//    // Set up uniforms.
//    /*SetUniform2f( shader, "u_ObjectScale", objectScale );
//    SetUniform1f( shader, "u_ObjectAngleRadians", objectAngle / 180.0f * PI );
//    SetUniform2f( shader, "u_ObjectPosition", objectPos );*/
//    //SetUniform2f( shader, "u_CameraTranslation", cameraPos * -1 );
//    //SetUniform2f( shader, "u_ProjectionScale", projectionScale );
//    SetUniformWorldMatrix(shader, "u_WorldMatrix", worldMat);
//    SetUniformViewMatrix(shader, "u_ViewMatrix", pCamera->GetViewMat());
//    SetUniformProjMatrix(shader, "u_ProjectionMatrix", pCamera->GetProjMat());
//
//    SetUniform1f(shader, "u_Time", GetSystemTimeSinceGameStart());
//
//
//    SetUniform3f(shader, "u_Origin[0]", RippleOrigin1);
//    SetUniform3f(shader, "u_Origin[1]", RippleOrigin2);
//
//
//
//    SetUniform1f(shader, "u_RangeOfRipple[0]", RippleRange1);
//    SetUniform1f(shader, "u_RangeOfRipple[1]", RippleRange2);
//
//
//
//
//
//    // Setup our texture.
//    if (pTexture != nullptr)
//    {
//        int textureUnitNumber = 0;
//        glActiveTexture(GL_TEXTURE0 + textureUnitNumber);
//        glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureID());
//        SetUniform1i(shader, "u_TextureSampler", textureUnitNumber);
//    }
//
//    CheckForGLErrors();
//}

void Mesh::Draw(Material* pMaterial)
{
    assert(m_PrimitiveType != -1);
    assert(m_NumVerts != 0);
    assert(pMaterial != nullptr);
    assert(pMaterial->GetShader() != nullptr);
    assert(pMaterial->GetShader()->GetProgram() != 0);
    CheckForGLErrors();

    // Draw.
    if( m_NumIndices > 0 )
    {
        glDrawElements( m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
    }

    // Disable the attribute arrays used.
    {
        GLuint shader = pMaterial->GetShader()->GetProgram();

        GLint aPos = glGetAttribLocation( shader, "a_Position" );
        GLint aColor = glGetAttribLocation( shader, "a_Color" );
        GLint aUV = glGetAttribLocation( shader, "a_UV" );

        glDisableVertexAttribArray( aPos );

        if( aColor != -1 )
            glDisableVertexAttribArray( aColor );

        if( aUV != -1 )
            glDisableVertexAttribArray( aUV );
    }

    CheckForGLErrors();
}
