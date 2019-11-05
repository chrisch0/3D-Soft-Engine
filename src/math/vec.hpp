#pragma once
#include <initializer_list>
#include <cmath>

template <typename T>
class Vec2
{
public:
	T x, y;
	Vec2() : x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	~Vec2() {}

	Vec2<T>& operator=(const Vec2<T>& rhs)
	{
		x = rhs.s; y = rhs.y;
		return *this;
	}

	Vec2<T>& operator=(const std::initializer_list<T>& il)
	{
		assert(il.size() >= 2);
		x = il[0]; y = il[1];
		return *this;
	}

	Vec2<T> operator+(const Vec2<T>& rhs) const
	{
		return Vec2<T>(x + rhs.x, y + rhs.y);
	}

	Vec2<T>& operator+=(const Vec2<T>& rhs)
	{
		x += rhs.x; y += rhs.y;
		return *this;
	}

	Vec2<T> operator-(const Vec2<T>& rhs) const 
	{
		return Vec2<T>(x - rhs.x, y - rhs.y);
	}

	Vec2<T> operator*(const T& s) const
	{
		return Vec2<T>(x * s, y * s);
	}

	double LengthSquared() const { return x * x + y * y; }
	double Length() const { return std::sqrt(x * x + y * y); }
};

using Vec2d = Vec2<double>;

template <typename T>
class Vec4
{
public:
	T x, y, z, w;
	Vec4() : x(0), y(0), z(0), w(0) {}
	Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
	~Vec4() {};

	Vec4<T>& operator=(const Vec4<T>& rhs)
	{
		x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
		return *this;
	}

	Vec4<T>& operator=(const std::initializer_list<T>& il)
	{
		assert(il.size() >= 4);
		x = il[0]; y = il[1]; z = il[2]; w = il[3];
		return *this;
	}

	Vec4<T> operator+(const Vec4<T>& rhs) const
	{
		return Vec4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	Vec4<T>& operator+=(const Vec4<T>& rhs)
	{
		x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
		return *this;
	}

	Vec4<T> operator*(const T& s) const
	{
		return Vec4<T>(x * s, y * s, z * s, w * s);
	}

	Vec4<T>& operator*=(const T& s)
	{
		x *= s; y *= s; z *= s; w *= s;
		return *this;
	}
private:
	
};

using Color_255 = Vec4<unsigned char>;

template <typename T>
inline Vec2<T> operator*(const T& s, const Vec2<T>& rhs)
{
	return rhs * s;
}