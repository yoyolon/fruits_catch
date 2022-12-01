#pragma once

#include <cmath>
#include <limits>

// 算術ライブラリ
namespace Math {
	constexpr float Pi = 3.1415926535f;
	constexpr float InvPi = 1 / Pi;
	constexpr float Infty = std::numeric_limits<float>::infinity();
	constexpr float NegInfty = -Infty;

	inline float Deg2Rad(float degree) {
		return degree * Pi / 180.0f;
	}
	inline float Rad2Deg(float radiance) {
		return radiance * 180.0f / Pi;
	}
	inline float NearZero(float v, float epsilon = 0.0001f) {
		return (std::abs(v) <= epsilon) ? true : false;
	}

	template <typename T>
	T Min(const T& a, const T& b) {
		return (a < b) ? a : b;
	}
	template <typename T>
	T Max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}
	template <typename T>
	T Clamp(const T& v, const T& lower, const T& upper) {
		return Min(upper, Max(lower, v));
	}
}

// *** 2Dベクトル ***
class Vec2 {
public:
	float x, y;
	Vec2() : x(0.0f), y(0.0f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}

	// セッタ
	void Set(float _x, float _y) {
		x = _x;
		y = _y;
	}

	// 演算子多重定義
	Vec2& operator+=(const Vec2& a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
	Vec2& operator*=(float t) {
		x *= t;
		y *= t;
		return *this;
	}
	friend inline Vec2 operator+(const Vec2& a, const Vec2& b) {
		return Vec2(a.x + b.x, a.y + b.y);
	}
	friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
		return Vec2(a.x - b.x, a.y - b.y);
	}
	friend inline Vec2 operator*(const Vec2& a, const Vec2& b) {
		return Vec2(a.x * b.x, a.y * b.y);
	}
	friend inline Vec2 operator*(float t, const Vec2& a) {
		return Vec2(t * a.x, t * a.y);
	}
	friend inline Vec2 operator*(const Vec2& a, float t) {
		return Vec2(t * a.x, t * a.y);
	}

	// ノルム
	float Length2() const { return (x*x + y*y); }
	float Length() const { return std::sqrt(Length2()); }
	// 正規化
	void Normalize() {
		float invlen = 1 / Length();
		x *= invlen;
		y *= invlen;
	}
	// 単位ベクトル
	static Vec2 Unit_vector(const Vec2& a) {
		Vec2 ret = a;
		ret.Normalize();
		return ret;
	}
	// 内積
	static float Dot(const Vec2& a, const Vec2& b) {
		return a.x*b.x + a.y*b.y;
	}
	// 線形補間
	static Vec2 Lerp(const Vec2& a, const Vec2& b, float t) {
		return Vec2((1 - t)*a + t*b);
	}
	// 正反射方向
	static Vec2 Reflect(const Vec2& v, const Vec2& n) {
		return v - 2.0f * Vec2::Dot(v, n) * n;
	}
	// 行列変換 TODO: 実装
	static Vec2 Transform(const Vec2& v, const class Mat3& m, float w=1.0);

	// 定数
	static const Vec2 Zero;
};

// *** 3Dベクトル ***
class Vec3 {
public:
	float x, y, z;
	Vec3() : x(0.0f), y(0.0f), z(0.0) {}
	Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	// セッタ
	void Set(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	// 演算子多重定義
	Vec3& operator+=(const Vec3& a) {
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}
	Vec3& operator-=(const Vec3& a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}
	Vec3& operator*=(float t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}
	friend inline Vec3 operator+(const Vec3& a, const Vec3& b) {
		return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend inline Vec3 operator-(const Vec3& a, const Vec3& b) {
		return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	friend inline Vec3 operator*(const Vec3& a, const Vec3& b) {
		return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
	}
	friend inline Vec3 operator*(float t, const Vec3& a) {
		return Vec3(t * a.x, t * a.y, t * a.z);
	}
	friend inline Vec3 operator*(const Vec3& a, float t) {
		return Vec3(t * a.x, t * a.y, t * a.z);
	}

	// ノルム
	float Length2() const { return (x*x + y*y + z*z); }
	float Length() const { return std::sqrt(Length2()); }
	// 正規化
	void Normalize() {
		float invlen = 1 / Length();
		x *= invlen;
		y *= invlen;
		z *= invlen;
	}
	// 単位ベクトル
	static Vec3 Unit_vector(const Vec3& a) {
		Vec3 ret = a;
		ret.Normalize();
		return ret;
	}
	// 内積
	static float Dot(const Vec3& a, const Vec3& b) {
		return a.x*b.x + a.y*b.y * a.z*b.z;
	}
	// 外積
	static Vec3 Cross(const Vec3& a, const Vec3& b) {
		return Vec3(a.y*b.z - a.z*b.y,
					a.z*b.x - a.x*b.z,
					a.x*b.y - a.y*b.z);
	}
	// 線形補間
	static Vec3 Lerp(const Vec3& a, const Vec3& b, float t) {
		return Vec3((1 - t)*a + t*b);
	}
	// 正反射方向
	static Vec3 Reflect(const Vec3& v, const Vec3& n) {
		return v - 2.0f * Vec3::Dot(v, n) * n;
	}
	// 行列変換 TODO: 実装
	static Vec3 Transform(const Vec3& v, const class Mat3& m, float w=1.0);

	// 定数
	static const Vec3 Zero;
};
