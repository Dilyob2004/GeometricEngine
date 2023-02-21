#ifndef VECTOR4_H
#define VECTOR4_H
#include <cmath>
#include <Engine/Core/Config.h>
namespace GeometricEngine
{
    template <typename T>
    class Vector4
    {
    public:
        Vector4():
            x(0), y(0),
            z(0), w(0)
        {
        }
        Vector4(T X, T Y, T Z, T W):
            x(X), y(Y),
            z(Z), w(W)
        {
        }
        template <typename U>
        explicit Vector4(const Vector4<U>& v):
            x(static_cast<T>(v.x)),
            y(static_cast<T>(v.y)),
            z(static_cast<T>(v.z)),
            w(static_cast<T>(v.w))
        {
        }
        void Clamp(const Vector4& min, const Vector4& max)
        {
            if(min > max) return;

            if (x < min.x) x = min.x;
            if (x > max.x) x = max.x;

            if (y < min.y) y = min.y;
            if (y > max.y) y = max.y;

            if (z < min.z) z = min.z;
            if (z > max.z) z = max.z;

            if (w < min.w) w = min.w;
            if (w > max.w) w = max.w;
        }

        void Clamp(const Vector4& v, const Vector4& min, const Vector4& max, Vector4* dst)
        {
            if(min > max || !dst) return;

            dst->x = v.x;
            if (dst->x < min.x) dst->x = min.x;
            if (dst->x > max.x) dst->x = max.x;

            dst->y = v.y;
            if (dst->y < min.y) dst->y = min.y;
            if (dst->y > max.y) dst->y = max.y;


            dst->z = v.z;
            if (dst->z < min.z) dst->z = min.z;
            if (dst->z > max.z) dst->z = max.z;

            dst->w = v.w;
            if (dst->w < min.w) dst->w = min.w;
            if (dst->w > max.w) dst->w = max.w;
        }

        T Distance(const Vector4& v) const
        {
            Vector4 v0(v.x - x, v.y - y, v.y - z, v.w - w);
            return v0.Length();
        }
        T Dot(const Vector4& v1, const Vector4& v2)
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
        Vector4 GetNormalized() const
        {
            Vector4 v(*this);
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
    Vector4<U> operator -(const Vector4<U>& right)
    {
        return Vector4<U>(-right.x, -right.y, -right.z -right.w);
    }

    template <typename U>
    Vector4<U>& operator +=(Vector4<U>& left, const Vector4<U>& right)
    {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;
        left.w += right.w;

        return left;
    }


    template <typename U>
    Vector4<U>& operator -=(Vector4<U>& left, const Vector4<U>& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= right.z;
        left.w -= right.w;

        return left;
    }

    template <typename U>
    Vector4<U>& operator *=(Vector4<U>& left, U right)

    {
        left.x *= right;
        left.y *= right;
        left.z *= right;
        left.w *= right;

        return left;
    }

    template <typename U>
    Vector4<U>& operator /=(Vector4<U>& left, U right)
    {
        left.x /= right;
        left.y /= right;
        left.z /= right;
        left.w /= right;

        return left;
    }

    template <typename U>
    Vector4<U> operator +(const Vector4<U>& left, const Vector4<U>& right)
    {
        return Vector4<U>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
    }

    template <typename U>
    Vector4<U> operator -(const Vector4<U>& left, const Vector4<U>& right)
    {
        return Vector4<U>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
    }
    template <typename U>
    Vector4<U> operator *(const Vector4<U>& left, const Vector4<U>& right)
    {
        return Vector4<U>(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
    }

    template <typename U>
    Vector4<U> operator *(const Vector4<U>& left, U right)
    {
        return Vector4<U>(left.x * right, left.y * right, left.z * right, left.w * right);
    }

    template <typename U>
    Vector4<U> operator *(U left, const Vector4<U>& right)
    {
        return Vector4<U>(right.x * left, right.y * left, right.z * left, right.w * left);
    }


    template <typename U>
    Vector4<U> operator /(const Vector4<U>& left, U right)
    {
        return Vector4<U>(left.x / right, left.y / right, left.z / right, left.w / right);
    }

    template <typename U>
    Vector4<U> operator /(const Vector4<U>& left, const Vector4<U>& right)
    {
        return Vector4<U>(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
    }

    template <typename U>
    bool operator ==(const Vector4<U>& left, const Vector4<U>& right)
    {
        return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
    }

    template <typename U>
    bool operator !=(const Vector4<U>& left, const Vector4<U>& right)
    {
        return !(left == right);
    }

    template <typename U>
    bool operator >(const Vector4<U>& left, const Vector4<U>& right)
    {
        return (left.length() > right.length());
    }

    /// vector1 < Vector4
    template <typename U>
    bool operator <(const Vector4<U>& left, const Vector4<U>& right)
    {
        return !(left > right);
    }

    typedef Vector4<S32>    Vector4i;
    typedef Vector4<U32>    Vector4u;
    typedef Vector4<F32>    Vector4f;
    typedef Vector4<F64>    Vector4d;
}


#endif // VECTOR4_H
