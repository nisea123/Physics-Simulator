#pragma once

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
Vec2f abs(Vec2f v);
Vec2f logf(Vec2f v);

float Length(Vec2f v);
Vec2f Normalize(Vec2f v);
float Dot(Vec2f a, Vec2f b);