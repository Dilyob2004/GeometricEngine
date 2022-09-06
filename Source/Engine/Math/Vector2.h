#ifndef VECTOR2_H
#define VECTOR2_H
#include <cmath>
#include <Engine/Core/Config.h>
namespace MeteorEngine
{
    template <typename T>
    class METEOR_API Vector2
    {
    public:
		Vector2():
			x(0),
			y(0)
		{
		}
		Vector2(T X, T Y) :
			x(X),
			y(Y)
		{
		}
        template <typename U>
		explicit Vector2(const Vector2<U>& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.y))
		{
		}
		void Clamp(const Vector2<T>& min, const Vector2<T>& max)
		{
			if (min > max) return;

			if (x < min.x) x = min.x;
			if (x > max.x) x = max.x;

			if (y < min.y) y = min.y;
			if (y > max.y) y = max.y;
		}


		void Scale(T scalar)
		{
			x *= scalar;
			y *= scalar;
		}
		void Normalize()
		{
			T n = 1.0 / Length();

			x *= n;
			y *= n;
		}
		T Distance(const Vector2<T>& v) const
		{
			Vector2 v0(v.x - x, v.y - y);
			return v0.Length();
		}
		T Dot(const Vector2<T>& v1, const Vector2<T>& v2)
		{
			return (v1.x * v2.x + v1.y * v2.y);
		}
		Vector2<T> GetNormalized() const
		{
			Vector2<T> v(*this);
			v.Normalize();
			return v;
		}
		T Length() const
		{
			return sqrt(x * x + y * y);
		}
        T x, y;
    };
    /// -vector
    template <typename U>
    Vector2<U> operator -(const Vector2<U>& right)
    {
        return Vector2<U>(-right.x, -right.y);
    }


    /// vector1 += vector2
    template <typename U>
    Vector2<U>& operator +=(Vector2<U>& left, const Vector2<U>& right)
    {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    /// vector1 -= vector2
    template <typename U>
    Vector2<U>& operator -=(Vector2<U>& left, const Vector2<U>& right)
    {
        left.x -= right.x;
        left.y -= right.y;

        return left;
    }

    ///vector *= number
    template <typename U>
	Vector2<U>& operator *=(Vector2<U>& left, U right)


	{
		left.x *= right;
		left.y *= right;

		return left;
	}




	template <typename U>
	Vector2<U> operator +(const Vector2<U>& left, const Vector2<U>& right)
	{
		return Vector2<U>(left.x + right.x, left.y + right.y);
	}

	template <typename U>
	Vector2<U> operator -(const Vector2<U> & left, const Vector2<U> & right)
	{
		return Vector2<U>(left.x - right.x, left.y - right.y);
	}

	template <typename U>
	Vector2<U> operator *(const Vector2<U> & left, const Vector2<U> & right)
	{
		return Vector2<U>(left.x * right.x, left.y * right.y);
	}
	template <typename U>
	Vector2<U> operator *(const Vector2<U> & left, U right)
	{
		return Vector2<U>(left.x * right, left.y * right);
	}

	template <typename U>
	Vector2<U> operator *(U left, const Vector2<U> & right)
	{
		return Vector2<U>(right.x * left, right.y * left);
	}

	template <typename U>
	Vector2<U> operator /(const Vector2<U> & left, U right)
	{
		return Vector2<U>(left.x / right, left.y / right);
	}

	template <typename U>
	Vector2<U>& operator /=(Vector2<U> & left, U right)
	{
		left.x /= right;
		left.y /= right;

		return left;
	}

	template <typename U>
	Vector2<U> operator /(const Vector2<U> & left, const Vector2<U> & right)
	{
		return Vector2<U>(left.x / right.x, left.y / right.y);
	}

	template <typename U>
	bool operator ==(const Vector2<U> & left, const Vector2<U> & right)
	{
		return (left.x == right.x) && (left.y == right.y);
	}

	template <typename U>
	bool operator !=(const Vector2<U> & left, const Vector2<U> & right)
	{
		return !(left == right);
	}

	template <typename U>
	bool operator >(const Vector2<U> & left, const Vector2<U> & right)
	{
		return (left.length() > right.length());
	}

	template <typename U>
	bool operator <(const Vector2<U> & left, const Vector2<U> & right)
	{
		return !(left > right);
	}

    typedef Vector2<s32>    Vector2i;
    typedef Vector2<u32>    Vector2u;
    typedef Vector2<f32>    Vector2f;
    typedef Vector2<f64>    Vector2d;
}

#endif // VECTOR2_H
