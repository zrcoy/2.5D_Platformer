#include "GamePCH.h"
#include <vector>
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"

using namespace std;

void Mesh::CreateBox(vec2 size, vec2 pivot)
{
    

        VertexFormat vertexAttributes[] =
        {
            VertexFormat(vec2(-size.x / 2, -size.y / 2) - pivot, MyColor(255, 255, 255, 255), vec2(0.0f, 0.0f)),
            VertexFormat(vec2(-size.x / 2,  size.y / 2) - pivot, MyColor(255, 255, 255, 255), vec2(0.0f, 1.0f)),
            VertexFormat(vec2(size.x / 2,  size.y / 2) - pivot, MyColor(255, 255, 255, 255), vec2(1.0f, 1.0f)),
            VertexFormat(vec2(size.x / 2, -size.y / 2) - pivot, MyColor(255, 255, 255, 255), vec2(1.0f, 0.0f)),
        };
        unsigned int indices[6] = { 0,1,2, 0,2,3 };

        Init(vertexAttributes, 4, indices, 6, GL_TRIANGLES, GL_STATIC_DRAW);
       

   

};


void Mesh::CreateCube(vec3 size, vec3 pivot)
{


    float side = 1.0f / 6.0f;
    VertexFormat vertexAttributes[] =
    {

        //first surface
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(0.0f, 0.0f)),//0
        VertexFormat(vec3(size.x / 2,  -size.y / 2, -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(side, 0)),//1
        VertexFormat(vec3(size.x / 2,  size.y / 2,  -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(side, 1.0f)),//2
        VertexFormat(vec3(-size.x / 2, size.y / 2,  -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(0, 1.0f)),//3

        //VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) - pivot, MyColor(255,255,255,255), vec2(0.0f, 0.0f)),//4
        //VertexFormat(vec3(size.x / 2,  -size.y / 2, size.z / 2) - pivot, MyColor(255,255,255,255), vec2(1.0f, 0.0f)),//5
        //VertexFormat(vec3(size.x / 2,  size.y / 2,  size.z / 2) - pivot, MyColor(255,255,255,255), vec2(1.0f, 1.0f)),//6
        //VertexFormat(vec3(-size.x / 2, size.y / 2,  size.z / 2) - pivot, MyColor(255,255,255,255), vec2(0.0f, 1.0f)),//7

        // second surface
        VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(side, 0.0f)),//1  //4
        VertexFormat(vec3(size.x / 2,  -size.y / 2, size.z / 2) - pivot, MyColor(255,255,255,255), vec2(2 * side, 0.0f)),//5  //5 
        VertexFormat(vec3(size.x / 2,  size.y / 2,  size.z / 2) - pivot, MyColor(255,255,255,255), vec2(2 * side, 1.0f)),//6  //6
        VertexFormat(vec3(size.x / 2,  size.y / 2,  -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(side, 1.0f)),//2  //7

        //third surface
        VertexFormat(vec3(size.x / 2,  -size.y / 2, size.z / 2) - pivot, MyColor(255,255,255,255), vec2(5 * side, 0.0f)),//5  //8
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) - pivot, MyColor(255,255,255,255), vec2(1.0f, 0.0f)),//4  //9
        VertexFormat(vec3(-size.x / 2, size.y / 2,  size.z / 2) - pivot, MyColor(255,255,255,255), vec2(1.0f, 1.0f)),//7  10
        VertexFormat(vec3(size.x / 2,  size.y / 2,  size.z / 2) - pivot, MyColor(255,255,255,255), vec2(5 * side, 1.0f)),//6  11

        // Fourth surface
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) - pivot, MyColor(255,255,255,255), vec2(4 * side, 0.0f)),//4  12
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(5 * side, 0.0f)),//0  13
        VertexFormat(vec3(-size.x / 2, size.y / 2,  -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(5 * side, 1.0f)),//3  14
        VertexFormat(vec3(-size.x / 2, size.y / 2,  size.z / 2) - pivot, MyColor(255,255,255,255), vec2(4 * side, 1.0f)),//7  15

        // Fifth surface
        VertexFormat(vec3(-size.x / 2, size.y / 2,  -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(2 * side, 0.0f)),//3  16
        VertexFormat(vec3(size.x / 2,  size.y / 2,  -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(3 * side, 0.0f)),//2  17
        VertexFormat(vec3(size.x / 2,  size.y / 2,  size.z / 2) - pivot, MyColor(255,255,255,255), vec2(3 * side, 1.0f)),//6  18
        VertexFormat(vec3(-size.x / 2, size.y / 2,  size.z / 2) - pivot, MyColor(255,255,255,255), vec2(2 * side, 1.0f)),//7  19

        // Sixth surface
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) - pivot, MyColor(255,255,255,255), vec2(3 * side, 0.0f)),//4  20
        VertexFormat(vec3(size.x / 2,  -size.y / 2, size.z / 2) - pivot, MyColor(255,255,255,255), vec2(4 * side, 0.0f)),//5  21
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(3 * side, 1.0f)),//0  22
        VertexFormat(vec3(size.x / 2,  -size.y / 2, -size.z / 2) - pivot, MyColor(255,255,255,255), vec2(4 * side, 1.0f)),//1  23

    };


    unsigned int indices[6 * 2 * 3] =
    {
        0,3,1,
        1,3,2,

        4,7,5,
        5,7,6,

        8,10,9,
        8,11,10,

        12,14,13,
        12,15,14,

        16,19,17,
        17,19,18,

        20,23,21,
        20,22,23
    };




    Init(vertexAttributes, 24, indices, 6 * 2 * 3, GL_TRIANGLES, GL_STATIC_DRAW);
}

void Mesh::SetupTool()
{
    // combo list that show the selection we can use to draw
    static const char * tool[]{ "GL_POINTS","GL_LINES",
        "GL_LINE_LOOP", "GL_LINE_STRIP",
        "GL_TRIANGLES","GL_TRIANGLE_STRIP",
        "GL_TRIANGLE_FAN "
    };
    //static int currentTool = 2;


    {
        ImGui::Begin("Graphic Scene");

        ImGui::Combo("Tool", (int*)&m_PrimitiveType, tool, IM_ARRAYSIZE(tool));

        ImGui::End();
    }


    /* switch (currentTool)
     {
     case(0):
         m_PrimitiveType = GL_POINTS;
         break;
     case(1):
         m_PrimitiveType = GL_LINES;
         break;
     case(2):
         m_PrimitiveType = GL_LINE_LOOP;
         break;
     case(3):
         m_PrimitiveType = GL_LINE_STRIP;
         break;
     case(4):
         m_PrimitiveType = GL_TRIANGLES;
         break;
     case(5):
         m_PrimitiveType = GL_TRIANGLE_STRIP;
         break;
     case(6):
         m_PrimitiveType = GL_TRIANGLE_FAN;
         break;
     default:
         break;
     }*/


     // m_Tool = currentTool;



}

void Mesh::CreatePlane(vec2 worldSize, ivec2 vertexCount, vec2 pivotPoint)
{
    //// worldSize = vec2(30, 15);
    // //vertexCount = ivec2(4, 4);

    //vec3 pivot = vec3(worldSize.x / 2.0f,0,worldSize.y/2.0f);

    //assert(vertexCount.x > 1);
    //assert(vertexCount.y > 1);
    //int totalVertexCount = vertexCount.x*vertexCount.y;
    //VertexFormat* vertexAttributes = new VertexFormat[totalVertexCount];

    //float stepX = worldSize.x / (vertexCount.x - 1);
    //float stepY = worldSize.y / (vertexCount.y - 1);

    //float repeat = 2.0f;// texture repeat how many times on one axis
    //float uvstepX = repeat / (vertexCount.x - 1);
    //float uvstepY = repeat / (vertexCount.y - 1);

    //// plot all the points 
    //for (int y = 0; y < vertexCount.y; y++)
    //{
    //    for (int x = 0; x < vertexCount.x; x++)
    //    {
    //        vertexAttributes[vertexCount.x*y + x].m_Pos = vec3(x*stepX, 0, y*stepY) - pivot; // set the pivot point to center
    //        //vertexAttributes[vertexCount.x*y + x].m_Pos = vec3(x*stepX, y*stepY,0 ) /*- pivot*/;
    //        vertexAttributes[vertexCount.x*y + x].m_UV = vec2(x*uvstepX, y*uvstepY);
    //    }
    //}

    //// plot all the indices
    //// how many box
    //int boxNum = (vertexCount.x - 1)*(vertexCount.y - 1);
    //int boxNum_X = vertexCount.x - 1;
    //int boxNum_Y = vertexCount.y - 1;
    //int indicesNum = 6 * boxNum;
    //int boxIndex = 0;
    //stepX = 1;
    //stepY = vertexCount.x;
    //unsigned int* indices = new unsigned int[indicesNum];
    //for (int y = 0; y < boxNum_Y; y++)
    //{
    //    for (int x = 0; x < boxNum_X; x++)
    //    {

    //        indices[0 + 6 * boxIndex] = y * stepY + x + 0;
    //        indices[1 + 6 * boxIndex] = y * stepY + x + stepY;
    //        indices[2 + 6 * boxIndex] = y * stepY + x + stepY + stepX;
    //        indices[3 + 6 * boxIndex] = y * stepY + x + 0;
    //        indices[4 + 6 * boxIndex] = y * stepY + x + stepY + stepX;
    //        indices[5 + 6 * boxIndex] = y * stepY + x + stepX;

    //        boxIndex++;
    //    }

    //}

    //Init(vertexAttributes, totalVertexCount, indices, indicesNum, GL_TRIANGLES, GL_STATIC_DRAW);

    //delete[] vertexAttributes;
    //delete[] indices;

    int numVerts = vertexCount.x * vertexCount.y;
    int numIndices = (vertexCount.x - 1) * (vertexCount.y - 1) * 6;

    VertexFormat* verts = new VertexFormat[numVerts];
    unsigned int* indices = new unsigned int[numIndices];

    float stepX = worldSize.x / (vertexCount.y - 1);
    float stepY = worldSize.y / (vertexCount.y - 1);

    float uvStepX = 5.0f / (vertexCount.y - 1);
    float uvStepY = 5.0f / (vertexCount.y - 1);

    for (int y = 0; y < vertexCount.y; y++)
    {
        for (int x = 0; x < vertexCount.x; x++)
        {
            verts[y * vertexCount.x + x].m_Pos.Set(x * stepX - pivotPoint.x, 0, y * stepY - pivotPoint.y);
            verts[y * vertexCount.x + x].m_UV.Set(x * uvStepX, y * uvStepY);;
        }
    }

    for (int y = 0; y < vertexCount.y - 1; y++)
    {
        for (int x = 0; x < vertexCount.x - 1; x++)
        {
            int bottomLeftIndex = y * vertexCount.x + x;
            int elementIndex = (y * (vertexCount.x - 1) + x) * 6;

            indices[elementIndex + 0] = bottomLeftIndex + 0;
            indices[elementIndex + 1] = bottomLeftIndex + vertexCount.x;
            indices[elementIndex + 2] = bottomLeftIndex + vertexCount.x + 1;

            indices[elementIndex + 3] = bottomLeftIndex + 0;
            indices[elementIndex + 4] = bottomLeftIndex + vertexCount.x + 1;
            indices[elementIndex + 5] = bottomLeftIndex + 1;
        }
    }

    Init(verts, numVerts, indices, numIndices, GL_TRIANGLES, GL_STATIC_DRAW);

    delete[] verts;
    delete[] indices;
}

void Mesh::CreateObj(const char* objfilename)
{
    long length = 0;
    char* buffer = LoadCompleteFile(objfilename, &length);
    if (buffer == 0 || length == 0)
    {
        delete[] buffer;
        return;
    }
    char* next_token = 0;
    char* line = strtok_s(buffer, "\n", &next_token);

    /*int pos_index = 0;
    int uv_index = 0;*/
    int point_num = 0;   // how many points at all

    int triangle_num = 0;
    vector<vec3> pos_vector;
    vector<vec2> uv_vector;
    vector<unsigned int> indices_vector;
    vector<VertexFormat> VF_vector;


    while (line)
    {
        OutputMessage("%s\n", line);

        
        // store info in this line
        // fill the line start with v
        if (line[0] == 'v' && line[1] == ' ')
        {
            vec3 pos;
            sscanf_s(line, "v %f %f %f", &pos.x, &pos.y, &pos.z );
            pos_vector.push_back(pos);
            point_num++;   // how many 
        }
        // fill the line start with vt
        if (line[0] == 'v' && line[1] == 't')
        {
            vec2 uv;
            sscanf_s(line, "vt %f %f", &uv.x, &uv.y);
            uv_vector.push_back(uv);
        }

   
        // fill info for one triangle
        if (line[0] == 'f')
        {
            //VertexFormat vf= VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) - pivot, MyColor(255, 255, 255, 255), vec2(0.0f, 0.0f))
           
            int posIndex1;
            int uvIndex1;
            int posIndex2;
            int uvIndex2;
            int posIndex3;
            int uvIndex3;
            sscanf_s(line, "f %d/%d/%*d %d/%d/%*d %d/%d/%*d", &posIndex1, &uvIndex1, &posIndex2, &uvIndex2, &posIndex3, &uvIndex3);
  
            VertexFormat vf1 = VertexFormat(pos_vector[posIndex1 - 1], MyColor(255, 255, 255, 255), uv_vector[uvIndex1 - 1]);
            VertexFormat vf2 = VertexFormat(pos_vector[posIndex2 - 1], MyColor(255, 255, 255, 255), uv_vector[uvIndex2 - 1]);
            VertexFormat vf3 = VertexFormat(pos_vector[posIndex3 - 1], MyColor(255, 255, 255, 255), uv_vector[uvIndex3 - 1]);
            VF_vector.push_back(vf1);
            VF_vector.push_back(vf2);
            VF_vector.push_back(vf3);
 
        }
        

        line = strtok_s(0, "\n", &next_token);

        
    }

    Init(&VF_vector[0], VF_vector.size(), nullptr, 0, GL_TRIANGLES, GL_STATIC_DRAW);
    

    delete[] buffer;
}