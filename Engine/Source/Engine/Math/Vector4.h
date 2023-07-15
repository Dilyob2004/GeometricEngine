#ifndef TVector4_H
#define TVector4_H
#include <cmath>
#include <Engine/Core/Config.h>

template <typename T>
class TVector4
{
public:
    TVector4():
        x(0), y(0),
        z(0), w(0)
    {
    }
	FORCEINLINE TVector4(T X, T Y, T Z, T W):
        x(X), y(Y),
        z(Z), w(W)
    {
    }
    T Distance(const TVector4& v) const
    {
        TVector4 v0(v.x - x, v.y - y, v.y - z, v.w - w);
        return v0.Length();
    }
    T Dot(const TVector4& v1, const TVector4& v2)
    {
        return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
    }
    void Scale(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
    }
    void Normalize()
    {
        T n = static_cast<T>(1) / Length();

        x *= n;
        y *= n;
        z *= n;
        w *= n;
    }
    TVector4 GetNormalized() const
    {
        TVector4 v(*this);
        v.Normalize();
        return v;
    }
    T Length() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }
    T& operator [](const int& i)
    {
        if(i == 0) return x;
        if(i == 1) return y;
        if(i == 2) return z;
        else return w;
    }
    const T& operator [](const int& i) const
    {
        if(i == 0) return x;
        if(i == 1) return y;
        if(i == 2) return z;
        else return w;
    }
    T x, y, z, w;
};

template <typename U>
TVector4<U> operator -(const TVector4<U>& right)
{
    return TVector4<U>(-right.x, -right.y, -right.z -right.w);
}

template <typename U>
TVector4<U>& operator +=(TVector4<U>& left, const TVector4<U>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    left.w += right.w;

    return left;
}


template <typename U>
TVector4<U>& operator -=(TVector4<U>& left, const TVector4<U>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    left.w -= right.w;

    return left;
}

template <typename U>
TVector4<U>& operator *=(TVector4<U>& left, U right)

{
    left.x *= right;
    left.y *= right;
    left.z *= right;
    left.w *= right;

    return left;
}

template <typename U>
TVector4<U>& operator /=(TVector4<U>& left, U right)
{
    left.x /= right;
    left.y /= right;
    left.z /= right;
    left.w /= right;

    return left;
}

template <typename U>
TVector4<U> operator +(const TVector4<U>& left, const TVector4<U>& right)
{
    return TVector4<U>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

template <typename U>
TVector4<U> operator -(const TVector4<U>& left, const TVector4<U>& right)
{
    return TVector4<U>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}
template <typename U>
TVector4<U> operator *(const TVector4<U>& left, const TVector4<U>& right)
{
    return TVector4<U>(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}

template <typename U>
TVector4<U> operator *(const TVector4<U>& left, U right)
{
    return TVector4<U>(left.x * right, left.y * right, left.z * right, left.w * right);
}

template <typename U>
TVector4<U> operator *(U left, const TVector4<U>& right)
{
    return TVector4<U>(right.x * left, right.y * left, right.z * left, right.w * left);
}


template <typename U>
TVector4<U> operator /(const TVector4<U>& left, U right)
{
    return TVector4<U>(left.x / right, left.y / right, left.z / right, left.w / right);
}

template <typename U>
TVector4<U> operator /(const TVector4<U>& left, const TVector4<U>& right)
{
    return TVector4<U>(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
}

template <typename U>
bool operator ==(const TVector4<U>& left, const TVector4<U>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
}

template <typename U>
bool operator !=(const TVector4<U>& left, const TVector4<U>& right)
{
    return !(left == right);
}

template <typename U>
bool operator >(const TVector4<U>& left, const TVector4<U>& right)
{
    return (left.length() > right.length());
}

/// vector1 < TVector4
template <typename U>
bool operator <(const TVector4<U>& left, const TVector4<U>& right)
{
    return !(left > right);
}

typedef TVector4<S32>    Vector4i;
typedef TVector4<U32>    Vector4u;
typedef TVector4<F32>    Vector4f;
typedef TVector4<F64>    Vector4d;
#endif // TVector4_H
