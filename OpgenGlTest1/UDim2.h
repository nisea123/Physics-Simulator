#pragma once

#include "Vec2f.h"

struct UDim2
{
	Vec2f Scale = { 0.0f, 0.0f };
	Vec2f Offset = { 0.0f, 0.0f };

	UDim2() = default;
	UDim2(float scaleX, float scaleY, float offsetX, float offsetY) : Scale(scaleX, scaleY), Offset(offsetX, offsetY) {}
	UDim2(Vec2f scale, Vec2f offset) : Scale(scale), Offset(offset) {}
	Vec2f ToAbsolute(Vec2f& siz) const;
	Vec2f ToAbsolute() const;
	Vec2f ToAbsolutePosition(Vec2f& siz,Vec2f& pos) const;

};

