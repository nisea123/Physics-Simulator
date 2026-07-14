#pragma once

#include <vector>
#include <memory>

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
	std::unique_ptr<Object> Visual;
	GizmoHandleType Type;
	Vec2f Axis;

	Angle GizmoStartAngle = Angle::Radians(0);
	Vec2f MouseStartPosition = Vec2f(0, 0);

	GizmoHandle(std::unique_ptr<Object> obj, GizmoHandleType t, Vec2f ax) : Visual(std::move(obj)), Type(t), Axis(ax) {};
};

class Gizmo
{
public:

	std::vector<GizmoHandle> handles;
	Object* target;

	float lengthScale = .8f;
	float lineThickness = .1f;
	float trimScale = .4f;

	float radiusMulti = .2f;
	float arcThickness = 0.2f;

	float scaleMulti = .3f;

	float handleScale = 0.f;

	float minimumObjSize = 40.f;

	Gizmo() {
		Init();
	}

	void Show();
	void Hide();
	

private:
	void Init();
};