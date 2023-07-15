#pragma once
#include <Engine/Math/Vector3.h>
#include <Engine/Math/Vector4.h>


class FMatrix3;
class FMatrix4
{
public:
    FMatrix4();
    FMatrix4(F32 x);
    FMatrix4(const FMatrix4& x);
    FMatrix4(const FMatrix3& x);

    FMatrix4(   const Vector4f &column1,
                const Vector4f &column2,
                const Vector4f &column3,
                const Vector4f &column4);

    FMatrix4(   F32 m00, F32 m01, F32 m02, F32 m03,
                F32 m10, F32 m11, F32 m12, F32 m13,
                F32 m20, F32 m21, F32 m22, F32 m23,
                F32 m30, F32 m31, F32 m32, F32 m33);

    ~FMatrix4();
    Vector4f& operator[](const S32& i);
    const Vector4f& operator[](S32 i) const;

	FMatrix4& operator=(FMatrix4 const& m);

    static const FMatrix4 Zero;
    static const FMatrix4 Identity;

private:
    Vector4f Column[4];
};
bool operator == (const FMatrix4& m1, const FMatrix4& m2);

bool operator != (const FMatrix4& m1, const FMatrix4& m2);

FMatrix4 operator * (const FMatrix4& m1, const F32 &x);
FMatrix4 operator * (const F32 &x, const FMatrix4& m1);
FMatrix4 operator * (const FMatrix4& m1, const FMatrix4 &m2);

Vector3f operator * (const FMatrix4& Matrix, const Vector3f& Vector);