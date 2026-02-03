#pragma once
#include <raylib.h>

bool operator==(const Vector2& v1, const Vector2& v2);

Vector2 operator*(const Vector2& v, float f);

Vector2& operator*=(Vector2& v, float f);

Vector2 operator/(const Vector2& v, float f);

Vector2& operator/=(Vector2& v, float f);

Vector2 operator-(const Vector2& v1, const Vector2& v2);

Vector2& operator-=(Vector2& v1, const Vector2& v2);

Vector2& operator+=(Vector2& v1, const Vector2& v2);