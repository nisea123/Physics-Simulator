#pragma once

#include <vector>

#include "Object.h"
#include "ShapeInstance.h"

enum class GizmoHandleType
{
	Move,
	Scale,
	Rotate
};

struct GizmoHandle
{
	Object* Visual;
	GizmoHandleType Type;
	Vec2f Axis;

	GizmoHandle(Object* vis, GizmoHandleType typ, Vec2f ax) : Visual(vis), Type(typ), Axis(ax) {};
};

class Gizmo
{
public:

	Gizmo() {
		Init();
	}

	std::vector<GizmoHandle> handles;

	void Show();
	void Hide();
	void Init();
};