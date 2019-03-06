#ifndef __Mesh_H__
#define __Mesh_H__

class Texture;
class Camera;
class Material;

void SetUniform1f(GLuint shader, const char* uniformName, float value);

struct VertexFormat
{
    vec3 m_Pos;
    MyColor m_Color;
    vec2 m_UV;

    VertexFormat() {}
    VertexFormat(vec3 pos, MyColor color, vec2 uv)
    {
        m_Pos = pos;
        m_Color = color;
        m_UV = uv;
    }
};

class Mesh
{
protected:
    //float m_Values[2];

    GLuint m_VBO;
    GLuint m_IBO;

    unsigned int m_NumVerts;
    unsigned int m_NumIndices;

    GLenum m_PrimitiveType;

    bool m_FrontFace;
public:
    Mesh();
    virtual ~Mesh();

    void Init(VertexFormat* verts, int numVerts, unsigned int* indices, int numIndices, GLenum primitiveType, GLenum usage);
    void Init(const void* verts, int numVerts, GLenum primitiveType, GLenum usage);

    void SetupAttributes(Material* pMaterial);
    static void SetupUniforms(Material* pMaterial, MyMatrix* worldMat, Camera* pCamera, int frontFace=1);


    //static void SetupUniforms(ShaderProgram* pShader, MyMatrix worldMat/*, MyMatrix viewMat*//*, MyMatrix projMat*/, Texture* pTexture, Camera* pCamera, vec3 RippleOrigin[], float RippleRange[]);
    //static void SetupUniforms(ShaderProgram* pShader, MyMatrix worldMat/*, MyMatrix viewMat*//*, MyMatrix projMat*/, Texture* pTexture, Camera* pCamera, vec3 RippleOrigin1, vec3 RippleOrigin2, float RippleRange1, float RippleRange2);
    void Draw(Material* pMaterial);

    // The following functions are defined in MeshShapes.cpp:
    void CreateBox(vec2 size, vec2 pivot);
    void CreateCube(vec3 size, vec3 pivot);
    void CreatePlane(vec2 worldSize, ivec2 vertexCount, vec2 pivotPoint);
    void CreateObj(const char* objfilename);

    void SetFlipUV(bool frontFace) { m_FrontFace = frontFace; }

    void SetupTool();
    GLenum tool() { return m_PrimitiveType; }
};

#endif //__Mesh_H__
