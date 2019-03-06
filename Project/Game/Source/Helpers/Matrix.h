#ifndef __Matrix_H__
#define __Matrix_H__

class Matrix
{
public:
    // 1st digit is the column.
    // 2nd digit is the row.
    float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;

public:
    Matrix() {}

    void Print(char* label)
    {
        printf( "%s: \n", label );
        printf( "(%0.2f, %0.2f, %0.2f, %0.2f)\n", m11, m21, m31, m41 );
        printf( "(%0.2f, %0.2f, %0.2f, %0.2f)\n", m12, m22, m32, m42 );
        printf( "(%0.2f, %0.2f, %0.2f, %0.2f)\n", m13, m23, m33, m43 );
        printf( "(%0.2f, %0.2f, %0.2f, %0.2f)\n", m14, m24, m34, m44 );
    }

    // Overwrites the entire matrix with an indentity matrix.
    void CreateIdentityMatrix()
    {
        // TODO:
        m11 = m22 = m33 = m44 = 1;
        m21 = m31 = m41 = m12 = m32 = m42 = m13 = m23 = m43 = m14 = m24 = m34 = 0;
    }

    // Create a scale/translation matrix with the value passed in.
    // Other than scale/translation, the rest of the matrix should be identity.
    void CreateScaleAndTranslation(Vector3 scale, Vector3 translation)
    {
        // TODO:
        m11 *= scale.x;
        m22 *= scale.y;
        m33 *= scale.z;
        m41 += translation.x;
        m42 += translation.y;
        m43 += translation.z;
    }

    // Multiply a vec3 by this 4x4 matrix.
    // Assume the "w" value of the 'o' vector is a 1.
    Vector3 operator *(const Vector3 o)
    {
        // TODO:
        float x = m11 * o.x + m21 * o.y + m31 * o.z + m41;
        float y = m12 * o.x + m22 * o.y + m32 * o.z + m42;
        float z = m13 * o.x + m23 * o.y + m33 * o.z + m43;
        return Vector3(x, y, z);
    }
};

#endif //__Matrix_H__
