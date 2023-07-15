#ifndef VECTOR2_H
#define VECTOR2_H
#include <cmath>
#include <Engine/Core/Config.h>
template <typename T>
class Vector2
{
public:
	Vector2() :
		x(0),
		y(0)
	{
	}
	FORCEINLINE Vector2(T X, T Y) :
		x(X),
		y(Y)
	{
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
	T Distance(const Vector2& v) const
	{
		Vector2 v0(v.x - x, v.y - y);
		return v0.Length();
	}
	T Dot(const Vector2& v1, const Vector2& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y);
	}
	Vector2 Normalized() const
	{
		Vector2 V(*this);
		V.Normalize();
		return V;
	}
	T Length() const
	{
		return sqrt(x * x + y * y);
	}
	T x, y;
};
/// -vector
template <typename U>
INLINE Vector2<U> operator -(const Vector2<U>& right)
{
	return Vector2<U>(-right.x, -right.y);
}


/// vector1 += vector2
template <typename U>
INLINE Vector2<U>& operator +=(Vector2<U>& left, const Vector2<U>& right)
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

/// vector1 -= vector2
template <typename U>
INLINE Vector2<U>& operator -=(Vector2<U>& left, const Vector2<U>& right)
{
	left.x -= right.x;
	left.y -= right.y;

	return left;
}

///vector *= number
template <typename U>
INLINE Vector2<U>& operator *=(Vector2<U>& left, U right)


{
	left.x *= right;
	left.y *= right;

	return left;
}




template <typename U>
INLINE Vector2<U> operator +(const Vector2<U>& left, const Vector2<U>& right)
{
	return Vector2<U>(left.x + right.x, left.y + right.y);
}

template <typename U>
INLINE Vector2<U> operator -(const Vector2<U>& left, const Vector2<U>& right)
{
	return Vector2<U>(left.x - right.x, left.y - right.y);
}

template <typename U>
INLINE Vector2<U> operator *(const Vector2<U>& left, const Vector2<U>& right)
{
	return Vector2<U>(left.x * right.x, left.y * right.y);
}

template <typename U>
INLINE Vector2<U> operator *(const Vector2<U>& left, U right)
{
	return Vector2<U>(left.x * right, left.y * right);
}

template <typename U>
INLINE Vector2<U> operator *(U left, const Vector2<U>& right)
{
	return Vector2<U>(right.x * left, right.y * left);
}

template <typename U>
INLINE Vector2<U> operator /(const Vector2<U>& left, U right)
{
	return Vector2<U>(left.x / right, left.y / right);
}

template <typename U>
INLINE Vector2<U>& operator /=(Vector2<U>& left, U right)
{
	left.x /= right;
	left.y /= right;

	return left;
}

template <typename U>
INLINE Vector2<U> operator /(const Vector2<U>& left, const Vector2<U>& right)
{
	return Vector2<U>(left.x / right.x, left.y / right.y);
}

template <typename U>
INLINE bool operator ==(const Vector2<U>& left, const Vector2<U>& right)
{
	return (left.x == right.x) && (left.y == right.y);
}

template <typename U>
INLINE bool operator !=(const Vector2<U>& left, const Vector2<U>& right)
{
	return !(left == right);
}

template <typename U>
INLINE bool operator >(const Vector2<U>& left, const Vector2<U>& right)
{
	return (left.Length() > right.Length());
}

template <typename U>
INLINE bool operator <(const Vector2<U>& left, const Vector2<U>& right)
{
	return !(left > right);
}

typedef Vector2<S32>    Vector2i;
typedef Vector2<U32>    Vector2u;
typedef Vector2<F32>    Vector2f;
typedef Vector2<F64>    Vector2d;


#endif // VECTOR2_H