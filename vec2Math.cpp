#include "vec2Math.h"

bool operator==(const Vector2& v1, const Vector2& v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y);
}

Vector2 operator*(const Vector2& v, float f)
{
	return { v.x * f, v.y * f };
}

Vector2& operator*=(Vector2& v, float f)
{
	v.x *= f;
	v.y *= f;
	return v;
}

Vector2 operator/(const Vector2& v, float f)
{
	return { v.x / f, v.y / f };
}

Vector2& operator/=(Vector2& v, float f)
{
	v.x /= f;
	v.y /= f;
	return v;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	return { v1.x - v2.x, v1.y - v2.y };
}

Vector2& operator-=(Vector2& v1, const Vector2& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Vector2& operator+=(Vector2& v1, const Vector2& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}