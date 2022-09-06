#ifndef VECTOR3_H
#define VECTOR3_H
#include <cmath>
#include <Engine/Core/Config.h>
namespace MeteorEngine
{
    template <typename T>
    class Vector3
    {
    public:
        Vector3():
            x(0),
            y(0),
            z(0)
        {
        }
        Vector3(T X, T Y, T Z):
            x(X),
            y(Y),
            z(Z)
        {
        }
        template <typename U>
        explicit Vector3(const Vector3<U>& v):
            x(static_cast<T>(v.x)),
            y(static_cast<T>(v.y)),
            z(static_cast<T>(v.z))
        {
        }
        void Clamp(const Vector3& min, const Vector3& max)
        {
            if(min > max) return;

            if (x < min.x) x = min.x;
            if (x > max.x) x = max.x;

            if (y < min.y) y = min.y;
            if (y > max.y) y = max.y;

            if (z < min.z) z = min.z;
            if (z > max.z) z = max.z;
        }

        void Clamp(const Vector3& v, const Vector3& min, const Vector3& max, Vector3* dst)
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
        }

        T Distance(const Vector3& v) const
        {
            Vector3 v0(v.x - x, v.y - y, v.y - z);
            return v0.Length();
        }
        T Dot(const Vector3& v1, const Vector3& v2)
        {
            return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
        }
        void Scale(T scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
        }
        void Normalize()
        {
            T n = 1.0 / Length();

            x *= n;
            y *= n;
            z *= n;
        }
        Vector3 GetNormalized() const
        {
            Vector3 v(*this);
            v.Normalize();
            return v;
        }
        T Length() const
        {
            return sqrt(x * x + y * y + z * z);
        }
        T& operator [](const int& i)
        {
            if(i == 0) return x;
            if(i == 1) return y;
            else return z;
        }
        const T& operator [](const int& i) const
        {
            if(i == 0) return x;
            if(i == 1) return y;
            else return z;
        }

		template <typename U>
		Vector3<U>& operator=(const Vector3<U> & m)
		{
			x = m.x;
			y = m.y;
			z = m.z;
			return *this;
		}
        T x, y, z;
    };

    template <typename U>
    Vector3<U> operator -(const Vector3<U>& right)
    {
        return Vector3<U>(-right.x, -right.y, -right.z);
    }

    template <typename U>
    Vector3<U>& operator +=(Vector3<U>& left, const Vector3<U>& right)
    {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;

        return left;
    }

    template <typename U>
    Vector3<U>& operator -=(Vector3<U>& left, const Vector3<U>& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= right.z;

        return left;
    }

    template <typename U>
    Vector3<U>& operator *=(Vector3<U>& left, U right)

    {
        left.x *= right;
        left.y *= right;
        left.z *= right;

        return left;
    }

    template <typename U>
    Vector3<U>& operator /=(Vector3<U>& left, U right)
    {
        left.x /= right;
        left.y /= right;
        left.z /= right;

        return left;
    }

    template <typename U>
    Vector3<U> operator +(const Vector3<U>& left, const Vector3<U>& right)
    {
        return Vector3<U>(left.x + right.x, left.y + right.y, left.z + right.z);
    }

    template <typename U>
    Vector3<U> operator -(const Vector3<U>& left, const Vector3<U>& right)
    {
        return Vector3<U>(left.x - right.x, left.y - right.y, left.z - right.z);
    }
    template <typename U>
    Vector3<U> operator *(const Vector3<U>& left, const Vector3<U>& right)
    {
        return Vector3<U>(left.x * right.x, left.y * right.y, left.z * right.z);
    }
    template <typename U>
    Vector3<U> operator /(const Vector3<U>& left, const Vector3<U>& right)
    {
        return Vector3<U>(left.x / right.x, left.y / right.y, left.z / right.z);
    }


    template <typename U>
    Vector3<U> operator *(const Vector3<U>& left, U right)
    {
        return Vector3<U>(left.x * right, left.y * right, left.z * right);
    }

    template <typename U>
    Vector3<U> operator *(U left, const Vector3<U>& right)
    {
        return Vector3<U>(right.x * left, right.y * left, right.z * left);
    }

    template <typename U>
    Vector3<U> operator /(const Vector3<U>& left, U right)
    {
        return Vector3<U>(left.x / right, left.y / right, left.z / right);
    }



    template <typename U>
    bool operator ==(const Vector3<U>& left, const Vector3<U>& right)
    {
        return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
    }

    template <typename U>
    bool operator !=(const Vector3<U>& left, const Vector3<U>& right)
    {
        return !(left == right);
    }

    template <typename U>
    bool operator >(const Vector3<U>& left, const Vector3<U>& right)
    {
        return (left.length() > right.length());
    }

    template <typename U>
    bool operator <(const Vector3<U>& left, const Vector3<U>& right)
    {
        return !(left > right);
    }

    typedef Vector3<s32>    Vector3i;
    typedef Vector3<u32>    Vector3u;
    typedef Vector3<f32>    Vector3f;
    typedef Vector3<f64>    Vector3d;
}

#endif // VECTOR3_H
