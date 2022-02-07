#pragma once
#include <cmath>
#define PI 3.1415926f
#define NULL 0

inline float sqr(float n)
{
	return n * n;
}

class Vector
{
public:

	float x, y, z;

	Vector()
		: x(0.0f),
		y(0.0f),
		z(0.0f)
	{
	}

	Vector(const Vector& v)
		: x(v.x),
		y(v.y),
		z(v.z)
	{
	}

	Vector(float x, float y, float z)
		: x(x),
		y(y),
		z(z)
	{
	}


	Vector(float f)
		: x(f),
		y(f),
		z(f)
	{
	}

	virtual ~Vector()
	{
	}

	float length2()
	{
		return sqr(x) + sqr(y) + sqr(z);
	}

	float length()
	{
		return std::sqrt(length2());
	}

	void Clear()
	{
		x = y = z = 0;
	}

	void negative()
	{
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
	}

	float normalize()
	{
		float l = length();

		*this /= l;

		return l;
	}

	Vector normalized()
	{
		Vector v(*this);
		v.normalize();
		return v;
	}

	Vector& operator =(const Vector& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}
	Vector& operator +=(const Vector& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector& operator -=(const Vector& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vector& operator *=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	Vector& operator /=(float f)
	{
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}
	Vector operator -() const
	{
		return Vector(-x, -y, -z);
	}

	bool operator==(const Vector& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const Vector& other) const
	{
		return !(*this == other);
	}
};

inline float dot(Vector v1, Vector v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector cross(Vector v1, Vector v2)
{
	return Vector(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

inline Vector operator +(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}

inline Vector operator -(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z);
}

inline Vector operator *(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z);
}

inline Vector operator *(const Vector& v, float f)
{
	return Vector(v.x * f,
		v.y * f,
		v.z * f);
}

inline Vector operator *(float f, const Vector& v)
{
	return Vector(f * v.x,
		f * v.y,
		f * v.z);
}

inline Vector operator /(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z);
}

inline Vector operator /(const Vector& v, float f)
{
	return Vector(v.x / f,
		v.y / f,
		v.z / f);
}

inline Vector operator /(float f, const Vector& v)
{
	return Vector(f / v.x,
		f / v.y,
		f / v.z);
}

typedef Vector Point;

