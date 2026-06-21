#pragma once

struct Vec2f
{
	float x = 0.0f;
	float y = 0.0f;

};


Vec2f operator+(Vec2f a, Vec2f b);
Vec2f operator-(Vec2f a, Vec2f b);
Vec2f operator*(Vec2f v, float s);
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