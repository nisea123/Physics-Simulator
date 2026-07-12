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

	Vec2f ObjectStartPosition;
	Vec2f MouseStartPosition;

	GizmoHandle(std::unique_ptr<Object> obj, GizmoHandleType t, Vec2f ax) : Visual(std::move(obj)), Type(t), Axis(ax) {};
};

class Gizmo
{
public:

	std::vector<GizmoHandle> handles;
	Object* target;
	float length = 100;
	float thickness = 7;
	float trim = 10;

	Gizmo() {
		Init();
	}

	void Show();
	void Hide();
	

private:
	void Init();
};