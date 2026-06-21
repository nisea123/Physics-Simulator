#include "ObjectData.h"

ArrowDesc toArrowDesc(const Arrow* object, float newThickness) {
	ArrowDesc desc;

	desc.Start = object->Start;
	desc.End = object->End;

	desc.ArrowHeight = object->ArrowHeight;
	desc.ArrowWidth = object->ArrowWidth;
	desc.Thickness = newThickness;
	desc.Color = object->Color;

	return desc;
}