#pragma once

namespace Math
{
	constexpr float PI = 3.1415926535f;
	
	constexpr float ToRadians(float degrees)
	{
		return degrees * PI / 180.0f;
	}

	constexpr float ToDegrees(float radians)
	{
		return radians * 180.0f / PI;
	}
}