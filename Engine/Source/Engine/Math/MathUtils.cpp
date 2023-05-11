#include <Engine/Math/MathUtils.h>
#include <algorithm>


namespace GeometricEngine
{
	Matrix4f Inverse(const Matrix4f& m)
	{
		F32 Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		F32 Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		F32 Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		F32 Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		F32 Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		F32 Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		F32 Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		F32 Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		F32 Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		F32 Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		F32 Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		F32 Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		F32 Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		F32 Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		F32 Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		F32 Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		F32 Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		F32 Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		Vector4f Fac0(Coef00, Coef00, Coef02, Coef03);
		Vector4f Fac1(Coef04, Coef04, Coef06, Coef07);
		Vector4f Fac2(Coef08, Coef08, Coef10, Coef11);
		Vector4f Fac3(Coef12, Coef12, Coef14, Coef15);
		Vector4f Fac4(Coef16, Coef16, Coef18, Coef19);
		Vector4f Fac5(Coef20, Coef20, Coef22, Coef23);

		Vector4f Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		Vector4f Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		Vector4f Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		Vector4f Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		Vector4f Inv0 = (Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		Vector4f Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		Vector4f Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		Vector4f Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		Vector4f SignA(1, -1, 1, -1);
		Vector4f SignB(-1, 1, -1, 1);
		Matrix4f mInverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		Vector4f Row0(mInverse[0][0], mInverse[1][0], mInverse[2][0], mInverse[3][0]);

		Vector4f Dot0(m[0] * Row0);
		F32 Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		F32 OneOverDeterminant = static_cast<F32>(1) / Dot1;

		return mInverse * OneOverDeterminant;
	}
	Matrix4f Rotate(const Matrix4f & m, F32 angle, const Vector3f & v)
	{
		F32 const a = angle;
		F32 const c = cos(a);
		F32 const s = sin(a);

		Vector3f axis(v.GetNormalized());
		Vector3f temp((F32(1) - c) * axis);

		Matrix4f Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		Matrix4f Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}
	Matrix4f Translate(const Matrix4f & m, const Vector3f & v)
	{
		Matrix4f Result(m);
		Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return Result;
	}
	Matrix4f Scale(const Matrix4f & m, const Vector3f & v)
	{
		Matrix4f Result;
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];
		return Result;
	}

	Matrix4f Ortho(F32 left, F32 right, F32 bottom, F32 top)
	{
		Matrix4f Result(1.f);
		Result[0][0] = 2.f / (right - left);
		Result[1][1] = 2.f / (top - bottom);
		Result[2][2] = 1.f;
		Result[3][0] = (right + left) / (left - right);
		Result[3][1] = (top + bottom) / (bottom - top);
		return Result;
	}
	Matrix4f Perspective(F32 FOV, F32 AspectRatio, F32 zNear, F32 zFar)
	{
		F32 Height = 1.0f / tanf(FOV * 0.5f);
		F32 Width = Height / AspectRatio;
		F32 fRange = zFar / (zNear - zFar);
		F32 lRange = fRange * zNear;
		return Matrix4f(Vector4f(Width, 0.0f,  0.0f,   0.0f),
						Vector4f(0.0f, Height, 0.0f,   0.0f),
						Vector4f(0.0f,   0.0f,  fRange, -1.0f),
						Vector4f(0.0f,   0.0f,  lRange, 0.0f));
	}
	Matrix4f Perspective(F32 FOV, F32 Width, F32 Height, F32 zNear, F32 zFar)
	{
		F32 const rad = FOV;
		F32 const h = cos(rad / 2) / sin(rad / 2);
		F32 const w = h * Height / Width;

		Matrix4f Result(0.0f);
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = zFar / (zFar - zNear);
		Result[2][3] = 1.0f;
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}
	bool DecomposeTransform(const Matrix4f& transform, Vector3f& position, Vector3f& rotation, Vector3f& scale)
	{
		Matrix4f LocalMatrix(transform);
		position = Vector3f(LocalMatrix[3].x, LocalMatrix[3].y, LocalMatrix[3].z);

		LocalMatrix[3] = Vector4f(0, 0, 0, LocalMatrix[3].w);

		Vector3f Row[3];

		for (U32 i = 0; i < 3; i++)
			for (U32 j = 0; j < 3; j++)
				Row[i][j] = LocalMatrix[i][j];


		rotation.y = asin(-Row[0][2]);
		if (cos(rotation.y) != 0) {
			rotation.x = atan2(Row[1][2], Row[2][2]);
			rotation.z = atan2(Row[0][1], Row[0][0]);
		}
		else {
			rotation.x = atan2(-Row[2][0], Row[1][1]);
			rotation.z = 0;
		}


		scale.x = Row[0].Length();
		Matrix4f ScaleX = Scale(Matrix4f::Identity, Row[0]);
		Row[0] = Vector3f(ScaleX[0].x, ScaleX[0].y, ScaleX[0].z);

		scale.y = Row[1].Length();

		Matrix4f ScaleY = Scale(Matrix4f::Identity, Row[1]);
		Row[1] = Vector3f(ScaleY[1].x, ScaleY[1].y, ScaleY[1].z);

		scale.z = Row[2].Length();
		Matrix4f ScaleZ = Scale(Matrix4f::Identity, Row[2]);
		Row[2] = Vector3f(ScaleZ[2].x, ScaleZ[2].y, ScaleZ[2].z);

		return true;
	}

	Matrix3f toMatrix3(const Quaternion& q)
	{
		Matrix3f Result(F32(1));
		F32 qxx(q.x * q.x);
		F32 qyy(q.y * q.y);
		F32 qzz(q.z * q.z);
		F32 qxz(q.x * q.z);
		F32 qxy(q.x * q.y);
		F32 qyz(q.y * q.z);
		F32 qwx(q.w * q.x);
		F32 qwy(q.w * q.y);
		F32 qwz(q.w * q.z);

		Result[0][0] = F32(1) - F32(2) * (qyy + qzz);
		Result[0][1] = F32(2) * (qxy + qwz);
		Result[0][2] = F32(2) * (qxz - qwy);

		Result[1][0] = F32(2) * (qxy - qwz);
		Result[1][1] = F32(1) - F32(2) * (qxx + qzz);
		Result[1][2] = F32(2) * (qyz + qwx);

		Result[2][0] = F32(2) * (qxz + qwy);
		Result[2][1] = F32(2) * (qyz - qwx);
		Result[2][2] = F32(1) - F32(2) * (qxx + qyy);
		return Result;
	}

	Matrix4f toMatrix4(const Quaternion & q)
	{
		return Matrix4f(toMatrix3(q));
	}

	Vector3f Cross(Vector3f const& x, Vector3f const& y)
	{
		return Vector3f(
			x.y * y.z - y.y * x.z,
			x.z * y.x - y.z * x.x,
			x.x * y.y - y.x * x.y);
	}
	Quaternion Rotate(const Quaternion & q, const F32 & angle, const Vector3f & v)
	{
		Vector3f Tmp = v;

		F32 len = Tmp.Length();
		if (abs(len - static_cast<F32>(1)) > static_cast<F32>(0.001))
		{
			F32 oneOverLen = static_cast<F32>(1) / len;
			Tmp.x *= oneOverLen;
			Tmp.y *= oneOverLen;
			Tmp.z *= oneOverLen;
		}

		const F32  AngleRad(angle);
		const F32  Sin = sin(AngleRad * static_cast<F32>(0.5));

		return q * Quaternion(cos(AngleRad * static_cast<F32>(0.5)), Tmp.x * Sin, Tmp.y * Sin, Tmp.z * Sin);
	}
	Quaternion operator*(Quaternion const& q, Quaternion const& p)
	{
		return Quaternion(q) *= p;
	}
	Vector3f operator*(Quaternion const& q, Vector3f const& v)
	{
		Vector3f const QuatVector(q.x, q.y, q.z);
		Vector3f const uv(Cross(QuatVector, v));
		Vector3f const uuv(Cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * static_cast<F32>(2);
	}
	Vector3f Rotate(Quaternion const& q, Vector3f const& v)
	{
		return q * v;
	}

	float Dot(const Vector3f& v1, const Vector3f& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}
	Matrix4f LookAt(const Vector3f &EyePosition, const Vector3f &LookAtPosition, const Vector3f & UpVector)
	{
		Matrix4f Result(1.0f);
		const Vector3f ZAxis((EyePosition - LookAtPosition).GetNormalized());
		const Vector3f XAxis(Cross(UpVector, ZAxis).GetNormalized());
		const Vector3f YAxis(Cross(ZAxis, XAxis));

		Result[0][0] = XAxis.x;
		Result[1][0] = XAxis.y;
		Result[2][0] = XAxis.z;

		Result[0][1] = YAxis.x;
		Result[1][1] = YAxis.y;
		Result[2][1] = YAxis.z;

		Result[0][2] = ZAxis.x;
		Result[1][2] = ZAxis.y;
		Result[2][2] = ZAxis.z;

		Result[3][0] = Dot(XAxis, -EyePosition) == -0 ? 0 : Dot(XAxis, -EyePosition);
		Result[3][1] = Dot(YAxis, -EyePosition) == -0 ? 0 : Dot(YAxis, -EyePosition);
		Result[3][2] = Dot(ZAxis, -EyePosition) == -0 ? 0 : Dot(ZAxis, -EyePosition);
		return Result;
	}

	F32 Angle(const Vector3f& x, const Vector3f& y)
	{
		return acos(std::clamp(Dot(x, y), -1.0f, 1.0f));
	}
	Matrix4f Rotate(F32 angle, Vector3f const& v)
	{
		return Rotate(Matrix4f(static_cast<F32>(1)), angle, v);
	}


	 Vector3f Rotate(Vector3f const& x, F32 const& angle, Vector3f const& normal)
	{
		const F32 Cos = cos(angle * MATH_RADIANS);
		const F32 Sin = sin(angle * MATH_RADIANS);
		return x * Cos + ((x * normal) * (F32(1) - Cos)) * normal + Cross(x, normal) * Sin;
	}
}