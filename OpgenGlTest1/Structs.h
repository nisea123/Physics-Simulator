#pragma once

#include "Math.h"
#include "UDim2.h"

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