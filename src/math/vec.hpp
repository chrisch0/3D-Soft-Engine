#pragma once

template <typename T>
class Vec4
{
public:
	T x, y, z, a;
	Vec4(T x, T y, T z, T a) : x(x), y(y), z(z), a(a) {};
	~Vec4() {};
private:
	
};

using Color = Vec4<unsigned char>;