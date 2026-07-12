#include <iostream>

#include "Gizmo.h"
#include "Object.h"
#include "Transform.h"

#include <algorithm>

void Gizmo::Init() {
	// Adding move arrows
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(-1, 0)); // Left Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(0, 1)); // Up Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(1, 0)); // Right Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(0, -1)); // Down Arrow

	handles.emplace_back(std::make_unique<Arc>(), GizmoHandleType::Rotate, Vec2f(1.5, 1.5));

	std::cout << "Gizmo initialized" << std::endl;
}

void Gizmo::Show() {
	if (Rectangle* rect = dynamic_cast<Rectangle*>(target)) {
		Vec2f pos = rect->Transform.Position;
		Vec2f size = rect->Size;
		Vec2f middle = size * .5f;
		Transform transform = rect->Transform;
			for (GizmoHandle& handle : handles) {
				if (Arrow* arr = dynamic_cast<Arrow*>(handle.Visual.get())) {
					Vec2f axis = handle.Axis;
					Vec2f newStart = Vec2f((middle.x + trim) * axis.x, (middle.y + trim) * axis.y);
					Vec2f newEnd = newStart + Vec2f(length * axis.x, length * axis.y);
					arr->Start = transform.RotatePoint(newStart,transform.Rotation) + pos;
					arr->End = transform.RotatePoint(newEnd,transform.Rotation) + pos;
					arr->Thickness = thickness;
					arr->Visible = true;
				 }
				if (Arc* arc = dynamic_cast<Arc*>(handle.Visual.get())) {
					Vec2f axis = handle.Axis;
					Vec2f arcPos = Vec2f(middle.x * axis.x, middle.y * axis.y);
					arc->Transform.Position = pos + arcPos;
					arc->Radius = std::max(size.x, size.y) * arcMulti;
					arcRadius = arc->Radius;
					arc->Thickness = arc->Radius * arcThickness;
					arc->Visible = true;
				}
			}
	}

}

void Gizmo::Hide() {
	for (GizmoHandle& handle : handles) {
		Object* o = handle.Visual.get();
		o->Visible = false;
	}
}