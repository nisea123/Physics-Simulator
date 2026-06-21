#include "Structs.h"
#include <cmath>

Vec2f operator+(Vec2f a, Vec2f b)
{
    return { a.x + b.x, a.y + b.y };
}

Vec2f operator-(Vec2f a, Vec2f b)
{
    return { a.x - b.x, a.y - b.y };
}

Vec2f operator*(Vec2f v, float s)
{
    return { v.x * s, v.y * s };
}

float Length(Vec2f v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Vec2f Normalize(Vec2f v)
{
    float len = Length(v);
    if (len == 0.0f)
        return { 0.0f, 0.0f };

    return { v.x / len, v.y / len };
}

float Dot(Vec2f a, Vec2f b) {
    return a.x * b.x + a.y + b.y;
}