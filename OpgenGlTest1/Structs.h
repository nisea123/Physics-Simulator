#pragma once

#include "Math.h"

struct Vec2f
{
	float x = 0.0f;
	float y = 0.0f;

	Vec2f() = default;

	Vec2f(float value) : x(value), y(value) {}

	Vec2f(float x, float y) : x(x), y(y) {}
};

Vec2f operator+(Vec2f a, Vec2f b);
Vec2f operator-(Vec2f a, Vec2f b);
Vec2f operator*(Vec2f v, float s);
Vec2f operator*(Vec2f a, Vec2f b);
Vec2f operator/(Vec2f a, Vec2f b);
Vec2f& operator+=(Vec2f& a, const Vec2f& b);
Vec2f& operator-=(Vec2f& a, const Vec2f& b);
Vec2f operator-(const Vec2f& v);

float Length(Vec2f v);
Vec2f Normalize(Vec2f v);
float Dot(Vec2f a, Vec2f b);

struct Vec2i {
	int x = 0;
	int y = 0;
};

struct Color
{
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;
};

struct Angle {

public:

	float radians;

	static constexpr Angle Degrees(float deg)
	{
		return Angle{Math::ToRadians(deg)};
	}

	static constexpr Angle Radians(float rad) {
		return { rad };
	}	

	float constexpr AsRadians() const
	{
		return radians;
	}

	float constexpr AsDegrees() const
	{
		return Math::ToDegrees(radians);
	}

	Angle operator-() const {
		return { -radians };
	}
};