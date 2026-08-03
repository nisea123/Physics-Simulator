#include "UDim2.h"

Vec2f UDim2::ToAbsolute(Vec2f& siz) const {
	return Scale * siz + Offset;
}

Vec2f UDim2::ToAbsolute() const {
	return Offset;
}

Vec2f UDim2::ToAbsolutePosition(Vec2f& siz, Vec2f& pos) const {
	return siz * Scale + pos + Offset;
}