#ifndef __Vector1_H__
#define __Vector1_H__
#include <math.h>

class MyVector3
{
public:
    float x,y,z;

public:
    MyVector3() {}
    MyVector3(float nx, float ny, float nz)
    {
        x = nx; y = ny; z = nz;
    }

    void Print(char* label)
    {
        printf( "%s: (%0.2f, %0.2f, %0.2f)\n", label, x, y, z );
    }

    void PrintLength()
    {
        printf( "Length: (%0.2f, %0.2f, %0.2f) = %0.2f\n", x, y, z, this->Length() );
    }

    void PrintDistanceTo(MyVector3 point)
    {
        printf( "Distance Between (%0.2f, %0.2f, %0.2f) and (%0.2f, %0.2f, %0.2f) = %0.2f\n", x, y, z, point.x, point.y, point.z, this->DistanceTo( point ) );
    }

    void PrintDot(MyVector3 vec2)
    {
        printf( "(%0.1f, %0.1f, %0.1f)", x, y, z );
        printf( " dot " );
        printf( "(%0.1f, %0.1f, %0.1f)", vec2.x, vec2.y, vec2.z );
        printf( " = %0.1f\n", this->Dot( vec2 ) );
    }

    void Print(MyVector3 vec1, char* label, MyVector3 vec2)
    {
        printf( "(%0.1f, %0.1f, %0.1f)", vec1.x, vec1.y, vec1.z );
        printf( " %s ", label );
        printf( "(%0.1f, %0.1f, %0.1f)", vec2.x, vec2.y, vec2.z );
        printf( " = (%0.1f, %0.1f, %0.1f)\n", x, y, z );
    }

    MyVector3 operator +(const MyVector3& o)
    {
        return MyVector3(this->x + o.x, this->y + o.y, this->z + o.z);
    }
    
    MyVector3 operator -(const MyVector3& o)
    {
        // TODO:
        return MyVector3(this->x - o.x, this->y - o.y, this->z - o.z);
    }

    float Length()
    {
        // TODO:
        return (float)sqrt(x*x+y*y+z*z);
    }

    float LengthSq()
    {
        return (x*x + y * y + z * z);
    }

    float DistanceTo(MyVector3 point)
    {
        // TODO:
        float xs = (point.x - this->x) * (point.x - this->x);
        float ys = (point.y - this->y) * (point.y - this->y);
        float zs = (point.z - this->z) * (point.z - this->z);
        return (float)sqrt(xs+ys+zs);
    }

    float DistanceSq(MyVector3 point)
    {
        // TODO:
        float xs = (point.x - this->x) * (point.x - this->x);
        float ys = (point.y - this->y) * (point.y - this->y);
        float zs = (point.z - this->z) * (point.z - this->z);
        return (xs + ys + zs);
    }

    void Normalize()
    {
        // TODO:
        float m = Length();
        x /= m;
        y /= m;
        z /= m;
    }

    float Dot(const MyVector3 &o)
    {
        // TODO:
        return (x * o.x + y * o.y + z * o.z);
        
    }

    MyVector3 Cross(const MyVector3& o)
    {
        // TODO:
        float x1 = x;
        float y1 = y;
        float z1 = z;
        float x2 = o.x;
        float y2 = o.y;
        float z2 = o.z;
        float x = y1 * z2 - z1 * y2;
        float y = z1 * x2 - x1 * z2;
        float z = x1 * y2 - y1 * x2;
        return MyVector3(x, y, z);
    }
};

#endif //__Vector_H1__
