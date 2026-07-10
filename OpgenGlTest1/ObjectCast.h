#pragma once

#include "Object.h"

template<typename T>
T* As(Object* o)
{
	if (!o) return nullptr;
	
	return (o->ShapeType == T::Type)
		? static_cast<T*>(o)
		: nullptr;
}