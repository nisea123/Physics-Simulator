#pragma once

struct Vec2f
{
	float x = 0.0f;
	float y = 0.0f;

    Vec2f operator-(const Vec2f& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vec2f operator+(const Vec2f& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vec2f operator*(float s) const
    {
        return { x * s, y * s };
    }

    Vec2f operator/(float s) const
    {
        return { x / s, y / s };
    }
};

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